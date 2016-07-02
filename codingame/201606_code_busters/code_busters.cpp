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
const int W = 16000;
const int H = 9000;
const int BR1 = 900;
const int BR2 = 1760;
const int VR = 2200;
const int VR_ROOT = VR * 0.7071 - 1;
P our_base;
P their_base;


const int cell_size = 800;

int turn = 0;
int captured = 0;

int bustersPerPlayer; // the amount of busters you control
int ghostCount; // the amount of ghosts on the map
int myTeamId; // if this is 0, your base is on the top left of the map, if it is one, on the bottom right

vector<vector<char>> visited;
vector<int> stun_used_turn;
map<int, P> seen_ghosts;
vector<P> next_goals;


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

    next_goals.resize(bustersPerPlayer);
    REP(i, bustersPerPlayer) {
        next_goals[i] = initial_goals[i];
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

bool near_our_base(P& p) {
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

P find_nearby_unvisited_pos(const P& cur) {
    int h_num = SIZE(visited);
    int w_num = SIZE(visited[0]);

    ll shortest = 1e15;
    P ret;
    REP(h, h_num) {
        REP(w, w_num) {
            if (!visited[h][w]) {
                P cell_center{
                    h * cell_size + cell_size / 2,
                    w * cell_size + cell_size / 2
                        };
                auto d2 = dist2(cell_center, cur);
                if (d2 < shortest) {
                    shortest = d2;
                    ret = cell_center;
                }
            }
        }
    }
    if (shortest == 1e15) {
        ret = P{-1,-1};
    }
    return ret;
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

P pick_random_pos(const P& cur) {

    // TODO: there is a bug
    // auto nearby = find_nearby_unvisited_pos(cur);
    // if (nearby != P{-1,-1}) {
    //     return nearby;
    // }

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


/**
 * Send your busters out into the fog to trap ghosts and bring them home!
 **/
int main() {
    cin >> bustersPerPlayer; cin.ignore();
    cin >> ghostCount; cin.ignore();
    cin >> myTeamId; cin.ignore();

    // initialize;
    visited = vector<vector<char>>(H / cell_size + 1, vector<char>(W / cell_size));
    if (myTeamId == 0) {
        our_base = P{0,0};
        their_base = P{W,H};
    }
    else {
        our_base = P{W,H};
        their_base = P{0,0};
    }


    setup_next_goals();

    stun_used_turn.resize(bustersPerPlayer);

    // game loop
    while (1) {
        ++turn;

        vector<Entity> us;
        vector<Entity> them;
        vector<Entity> ghosts;
        input(us, them, ghosts, myTeamId);
        print_input_data(us, them, ghosts);

        set<int> stunned_them_idx;

        for (auto& g: ghosts) {
            auto id = g.id;
            seen_ghosts[id] = g.p;
        }
        
        REP(i, SIZE(us)) {
            auto& me = us[i];

            // check visited cells
            ++visited[me.p.Y / cell_size][me.p.X / cell_size];

            // attempt to stun
            int them_idx = 0;
            if (stunnable(me, them, stun_used_turn, stunned_them_idx, them_idx)) {
                stringstream sout;
                sout << "stun " << them[them_idx].id;
                printf("STUN %d %s\n", them[them_idx].id, sout.str().c_str());
                stun_used_turn[me.id] = turn;
                stunned_them_idx.insert(them_idx);
            }
            // have a ghost
            else if (me.state == CARRYING) {
                seen_ghosts.erase(me.value);
                if (near_our_base(me.p)) {
                    printf("RELEASE %s\n", "release");
                    ++captured;
                }
                else {
                    printf("MOVE %d %d %s\n",
                           our_base.X, our_base.Y, "go home");
                }
            }
            // have no ghost
            else {
                // is there a ghost nearby?
                int g_idx;
                string state;
                find_closest_ghost(me, ghosts, g_idx, state);

                if (state == "bustable") {
                    auto& ghost = ghosts[g_idx];
                    printf("BUST %d\n", ghost.id);
                    seen_ghosts.erase(ghost.id);
                }
                else if (state == "too_close" || state == "nearby") {
                    auto& ghost = ghosts[g_idx];
                    auto pos = go_to_pick_ghost(me.p, ghost.p);
                    printf("MOVE %d %d %s\n", pos.X, pos.Y, state.c_str());
                    seen_ghosts.erase(ghost.id);
                }
                else {
                    // if almost ghosts are already captured
                    if (captured > ghostCount * 0.4 && SIZE(ghosts) > 0) {
                        ll best = 1e15;
                        P goal;
                        int id;
                        for(auto& g: ghosts) {
                            auto d2 = dist2(g.p, me.p);
                            if (d2 < best) {
                                best = d2;
                                goal = g.p;
                                id = g.id;
                            }
                        }
                        auto pos = go_to_pick_ghost(me.p, goal);
                        printf("MOVE %d %d %s\n", pos.X, pos.Y,
                               "go to help");
                        seen_ghosts.erase(id);
                    }
                    else {
                        // if there is a seen but unhandled ghost
                        if (!seen_ghosts.empty()) {
                            // TODO: if the ghost is too far, ignore it
                            ll best = 1e15;
                            P goal;
                            int id;
                            for(auto& g: seen_ghosts) {
                                auto d2 = dist2(g.second, me.p);
                                if (d2 < best) {
                                    best = d2;
                                    goal = g.second;
                                    id = g.first;
                                }
                            }
                            printf("MOVE %d %d %s\n", goal.X, goal.Y,
                                   "seen ghost"
                                );
                            if (goal == me.p) {
                                seen_ghosts.erase(id);
                            }
                        }
                        else {
                            // go far to find ghosts
                            if (next_goals[i] == me.p) {
                                // random!
                                next_goals[i] = pick_random_pos(me.p);
                            }
                            printf("MOVE %d %d\n", next_goals[i].X, next_goals[i].Y);
                        }
                    }
                }
            }
        }
    }
}
