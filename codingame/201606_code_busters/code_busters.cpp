#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

#define IDLE 0
#define CARRYING 1
#define STUNNED 2
#define TRAPPING 3
#define X first
#define Y second


using P = pair<int,int>;
const int W = 16001;
const int H = 9001;
const int BR1 = 900;
const int BR2 = 1760;
const int VR = 2200;
const int VR_ROOT = VR * 0.7071 - 1;
P our_base;
P their_base;


const int cell_size = 800;


class Entity {
public:
    int id;
    P p;
    int state;
    int value;

    Entity(int in_id, int in_x, int in_y, int in_state, int in_value):
        id(in_id),
        p(P(in_x,in_y)),
        state(in_state),
        value(in_value)
        {
        };
};

class State {
public:
    bool ini_state = true;
    P next_goal;
};

class GhostInfo {
public:
    int hp;
    P p;
    // "unseen", "seen", "busted", "estimated", "lost"
    string state = "unseen";
};

int turn = 0;
int captured = 0;

int bustersPerPlayer; // the amount of busters you control
int ghostCount; // the amount of ghosts on the map
int myTeamId; // if this is 0, your base is on the top left of the map, if it is one, on the bottom right

vector<P> unvisited;
vector<int> stun_used_turn;
// map<int, P> seen_ghosts;
vector<GhostInfo> ghost_info;


vector<State> us_state;


void input(vector<Entity>& us, vector<Entity>& them, vector<Entity>& ghosts,
           const int myTeamId) {
    int entities; // the number of busters and ghosts visible to you
    cin >> entities; cin.ignore();
    for (int i = 0; i < entities; i++) {
        int entityId; // buster id or ghost id
        int x;
        int y; // position of this buster / ghost
        int entityType; // the team id if it is a buster, -1 if it is a ghost.
        int state; // For busters: 0=idle, 1=carrying a ghost.
        int value; // For busters: Ghost id being carried. For ghosts: number of busters attempting to trap this ghost.
        cin >> entityId >> x >> y >> entityType >> state >> value; cin.ignore();
        Entity e{ entityId, x, y, state, value };
        if (entityType == myTeamId) {
            us.push_back(e);
        }
        else if (entityType == -1) {
            ghosts.push_back(e);
        }
        else {
            them.push_back(e);
        }
    }
}

void print_buster(const Entity& b) {
    cerr << "  " << b.id << "(" << b.p.X << "," << b.p.Y << ") s:" << b.state;
    if (b.state == CARRYING) {
        cerr << "  carrying:" << b.value;
    }
    else if (b.state == TRAPPING) {
        cerr << "  trapping:" << b.value;
    }
    else if (b.state == STUNNED) {
        cerr << "  can_move_after:" << b.value;
    }
    else {
        cerr << "  v:" << b.value;
    }
    cerr << endl;
}

void print_input_data(vector<Entity>& us, vector<Entity>& them, vector<Entity>& ghosts) {
    cerr << "ghost num:" << SIZE(ghosts) << endl;
    for(auto& g: ghosts) {
        cerr << "  " << g.id << "(" << g.p.X << "," << g.p.Y << ") attaacked_by:" << g.value << endl;
    }
    cerr << endl;

    cerr << "us num:" << SIZE(us) << endl;
    for(auto& u: us) {
        print_buster(u);
    }
    cerr << endl;

    cerr << "them num:" << SIZE(them) << endl;
    for(auto& t: them) {
        print_buster(t);
    }
    cerr << endl;
}
           
void setup_next_goals() {
    vector<P> initial_goals;
    double rate1 = 0.7;
    double rate2 = 0.8;
    if (bustersPerPlayer % 2) {
        initial_goals = vector<P> {
        P{rate2*(W - VR_ROOT), VR_ROOT},  // top right
        P{rate1*(W - VR_ROOT), rate1*(H - VR_ROOT)}, // bottom right
        P{VR_ROOT, H - VR_ROOT}, // bottom left
        P{W - VR, H / 2},
        P{W / 2, H - VR},
        P{W * 3 / 4, H - VR},
        P{W / 4, H - VR}
        };
    }
    else {
        initial_goals = vector<P> {
        P{rate2 * (W - VR_ROOT), VR},     // top right
        P{VR_ROOT, H - VR},     // bottom left
        P{rate2*(W - VR), rate2*(H * 3 / 4)},
        P{rate2*(W * 3 / 4), rate2*(H - VR)}
        };
    }

    if (our_base.X == W) {
        for(auto& g: initial_goals) {
            g.X = W - g.X;
            g.Y = H - g.Y;
        }
    }

    REP(i, bustersPerPlayer) {
        us_state[i].next_goal = initial_goals[i];
    }
}           


ll pow2(ll x) {
    return x * x;
}

ll dist2(const P& p1, const P& p2) {
    return pow2(p1.X - p2.X)
        + pow2(p1.Y - p2.Y);
}

bool can_bust(const ll d2) {
    return (pow2(BR1) <= d2 && d2 <= pow2(BR2));
}

bool too_close(const ll d2) {
    return pow2(BR1) > d2;
}

void find_closest_ghost(const Entity& me, const vector<Entity>& ghosts,
                        int& g_idx, string& state)
{
    // state: "bustable, "too_close", "nearby", "no"

    state = "no";

    ll nearest = 1e15;
    REP(i, SIZE(ghosts)) {
        auto& g = ghosts[i];
        auto d2 = dist2(me.p, g.p);
        if (can_bust(d2)) {
            g_idx = i;
            state = "bustable";
            return;
        }
        if (d2 < nearest) {
            nearest = d2;
            g_idx = i;
        }
    }

    if (nearest > pow2(2000)) {
        state = "no";
    }
    else if (too_close(nearest)) {
        state = "too_close";
    }
    else {
        state = "nearby";
    }
}

bool near_our_base(const P& p) {
    auto d2 = dist2(p, our_base);
    return d2 <= pow2(1600);
}

bool stunnable(const Entity& me, const vector<Entity>& them,
               const vector<int>& stun_used_turn,
               const set<int>& stunned_them_idx,
               int& them_idx)
{
    int kept = -1;

    REP(i, SIZE(them)) {
        auto& him = them[i];

        // avoid to stun the same enemy
        if (stunned_them_idx.count(i)) continue;
        // avoid to stun the enemy already stunned
        if (him.state == STUNNED) continue;

        auto d2 = dist2(me.p, him.p);
        if (d2 <= pow2(1760)
            && stun_used_turn[me.id] + 20 <= turn
            ) {
            if (him.state == CARRYING || him.state == TRAPPING) {
                them_idx = i;
                return true;
            }
            // idle or moving buster has low priority
            else  {
                kept = i;
            }
        }
    }

    if (kept != -1) {
        them_idx = kept;
        return true;
    }
    else {
        return false;
    }
}

void update_unvisited(const vector<Entity>& us) {
    vector<P> new_unvisited;
    cerr << "before unvisited:" << SIZE(unvisited) << endl;
    for(auto& p: unvisited) {
        bool visible = false;
        for(auto& me: us) {
            auto d2 = dist2(me.p, p);
            if (d2 <= pow2(VR)) {
                visible = true;
                continue;
            }
        }
        if (!visible) {
            new_unvisited.pb( p );
        }
    }
    unvisited = new_unvisited;
    cerr << " after unvisited:" << SIZE(unvisited) << endl;
}

void update_ghost_info(vector<Entity>& ghosts, const vector<Entity>& us) {
    for (auto& g: ghosts) {
        auto id = g.id;
        auto p = g.p;
        
        ghost_info[id].p = p;
        ghost_info[id].state = "seen";

        int id_pair = (id % 2) ? (id + 1) : (id - 1);
        if (ghost_info[id].state == "seen" && id != 0) {
            if (ghost_info[id_pair].state == "unseen") {
                ghost_info[id_pair].state = "estimated";
                int centX = W / 2;
                int centY = H / 2;
                ghost_info[id_pair].p = 
                    P(centX * 2 - p.X, centY * 2 - p.Y);
            }
        }
    }

    // judge lost
    REP(i, SIZE(ghost_info)) {
        auto& g = ghost_info[i];
        if (g.state == "seen" || g.state == "estimated") {
            ll d2 = 1e15;
            for(auto& me: us) {
                d2 = min(d2, dist2(me.p, g.p));
            }
            bool visible = d2 <= pow2(VR);
            
            if (visible) {
                bool included = false;
                for(auto& g2: ghosts) {
                    if (g2.id == i) {
                        included = true;
                        break;
                    }
                }
                if (!included) {
                    g.state = "lost";
                }
            }
        }
    }
}

P go_to_pick_ghost(const P& cur, const P& g) {
    double best_distance = (BR1 + BR2) / 2.0;

    if (cur == g) {
        // trivial corner cases:
        if (g == our_base) {
            return P{best_distance, 0};
        }
        if (g == their_base) {
            return P{W - best_distance, 0};
        }

        if (dist2(cur, our_base) > pow2(best_distance)) {
            P ret = go_to_pick_ghost(our_base, g);
            return ret;
        }
        else {
            P ret = go_to_pick_ghost(their_base, g);
            return ret;
        }
    }

    // vector from ghost to buster
    double vec_x = cur.X - g.X;
    double vec_y = cur.Y - g.Y;
    double len = sqrt( pow2(vec_x) + pow2(vec_y) );
    vec_x /= len;
    vec_y /= len;

    P best_pos {
        g.X + vec_x * best_distance,
        g.Y + vec_y * best_distance
    };

    return best_pos;
}

P pick_unvisited_pos(const P& cur) {
    auto best = 1e15;
    P ret;
    for(auto& p: unvisited) {
        auto d2 = dist2(cur, p);
        if (d2 < best) {
            best = d2;
            ret = p;
        }
    }
    return ret;
}

P pick_random_pos(const P& cur) {
    while (true) {
        P ret = P{rand() % W, rand() % H};
        if (rand() % 2) {
            if (rand() % 2) {
                ret.X = 0 + VR / 2;
            }
            else {
                ret.X = W - VR / 2;
            }
        }
        else {
            if (rand() % 2) {
                ret.Y = 0 + VR / 2;
            }
            else {
                ret.Y = H - VR / 2;
            }
        }
        
        // avoid nearby bases
        if (dist2(ret, our_base) < pow2(4000)
            || dist2(ret, their_base) < pow2(4000)) {
            continue;
        }
        return ret;
    }
}

string make_move_string(int x, int y, string message) {
    stringstream sout;
    sout << "MOVE " << x << " " << y << " " << message;
    return sout.str();
}

// bool closest_ghost(const Entity& me, const string state, P& p, int dist) {
//     ll best = 1e15;
//     P goal;
//     for(auto& g: ghost_info) {
//         if (g.state == state) {
//             auto d2 = dist2(g.p, me.p);
//             if (d2 < best) {
//                 best = d2;
//                 goal = g.p;
//             }
//         }
//     }
//     p = goal;
//     return best != 1e15;
// }

string choose_act(
    const int i, 
    vector<Entity>& us,
    const vector<Entity>& them,
    const vector<Entity>& ghosts,
    set<int>& stunned_them_idx)
{
    auto& me = us[i];
    auto& me_state = us_state[i];

    // have reached initial goal
    if (me_state.next_goal == me.p) {
        me_state.ini_state = false;
    }


    // attempt to stun
    int them_idx = 0;
    if (stunnable(me, them, stun_used_turn, stunned_them_idx, them_idx)) {
        stun_used_turn[me.id] = turn;
        stunned_them_idx.insert(them_idx);
        stringstream sout;
        sout << "STUN " << them[them_idx].id << " stun " << them[them_idx].id;
        return sout.str();
    }

    // carrying a ghost
    if (me.state == CARRYING) {
        if (near_our_base(me.p)) {
            ++captured;
            ghost_info[me.value].state = "busted";
            return "RELEASE release";
        }
        else {
            return make_move_string(our_base.X, our_base.Y, "go home");
        }
    }

    // have no ghost

    // is there a ghost nearby?
    int g_idx;
    string state;
    find_closest_ghost(me, ghosts, g_idx, state);
    
    if (state == "bustable") {
        auto& ghost = ghosts[g_idx];
        stringstream sout;
        sout << "BUST " << ghost.id;
        return sout.str();
    }
    if (state == "too_close" || state == "nearby") {
        auto& ghost = ghosts[g_idx];
        auto pos = go_to_pick_ghost(me.p, ghost.p);
        return make_move_string(pos.X, pos.Y, state);
    }

    // no nearby ghost.

    // if almost ghosts are already captured, go to help
    if (captured > ghostCount * 0.4 && SIZE(ghosts) > 0) {
        ll best = 1e15;
        P goal;
        for(auto& g: ghosts) {
            auto d2 = dist2(g.p, me.p);
            if (d2 < best) {
                best = d2;
                goal = g.p;
            }
        }
        auto pos = go_to_pick_ghost(me.p, goal);
        return make_move_string(pos.X, pos.Y, "go to help");
    }
    
    // go to seen or estimated ghost
    {
        ll best = 1e15;
        P goal;
        string state;
        for(auto& g: ghost_info) {
            if (g.state == "seen" || g.state == "estimated") {
                // if ghost is too close to their base, ignore it
                auto d = sqrt(dist2(g.p, our_base)) - sqrt(dist2(g.p, their_base));
                if (d < 2000) {
                    auto d2 = dist2(g.p, me.p);
                    if (d2 < best) {
                        best = d2;
                        goal = g.p;
                        state = g.state;
                    }
                }
            }
        }
        if (best != 1e15) {
            return make_move_string(goal.X, goal.Y, state + " ghost");
        }
    }
    
    // if havn't reached ini goal
    if (me_state.ini_state && me_state.next_goal != me.p) {
        auto& p = me_state.next_goal;
        return make_move_string(p.X, p.Y,
                                "ini goal");
    }

    // if there is unvisited points
    if (!unvisited.empty()) {
        P p = pick_unvisited_pos(me.p);
        stringstream sout;
        sout << "unv " << p.X << "," << p.Y;
        return make_move_string(p.X, p.Y, sout.str());
    }

    // random

    P& next_goal = me_state.next_goal;
    // go far to find ghosts
    if (me_state.next_goal == me.p) {
        // random!
        next_goal = pick_random_pos(me.p);
    }
    return make_move_string(next_goal.X, next_goal.Y,
                            "random pos");
}

    
    

/**
 * Send your busters out into the fog to trap ghosts and bring them home!
 **/
int main() {
    cin >> bustersPerPlayer; cin.ignore();
    cin >> ghostCount; cin.ignore();
    cin >> myTeamId; cin.ignore();

    // initialize;
    const int unit = 400;
    REP(w, W / unit) {
        REP(h, H / unit) {
            P p{ unit * w, unit * h };
            if (dist2(p, our_base) < pow2(4000)
                || dist2(p, their_base) < pow2(4000)) {
                continue;
            }
            unvisited.pb(p);
        }
    }
    if (myTeamId == 0) {
        our_base = P{0,0};
        their_base = P{W,H};
    }
    else {
        our_base = P{W,H};
        their_base = P{0,0};
    }



    stun_used_turn.resize(bustersPerPlayer);
    us_state.resize(bustersPerPlayer);
    ghost_info.resize(ghostCount);

    setup_next_goals();


    // game loop
    while (1) {
        ++turn;

        vector<Entity> us;
        vector<Entity> them;
        vector<Entity> ghosts;
        input(us, them, ghosts, myTeamId);
        print_input_data(us, them, ghosts);

        set<int> stunned_them_idx;

        // check visited cells
        update_unvisited(us);

        update_ghost_info(ghosts, us);

        cerr << "ghost info:" << endl;
        REP(i, SIZE(ghost_info)) {
            auto& g = ghost_info[i];
            cerr << "  " << i << ": " << g.state << ", (" << g.p.X << "," << g.p.Y << ")" << endl;
        }

        REP(i, SIZE(us)) {
            auto act = choose_act(i, us, them, ghosts, stunned_them_idx);
            cout << act << endl;
        }
    }
}