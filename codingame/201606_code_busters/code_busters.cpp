#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>

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


using P = pair<int,int>;
const int W = 16000;
const int H = 9000;
const int BR1 = 900;
const int BR2 = 1760;
const int VR = 2200;
const int VR_ROOT = VR * 0.7071 - 1;
P our_base;
P their_base;

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

ll pow2(ll x) {
    return x * x;
}

ll dist2(const P& p1, const P& p2) {
    return pow2(p1.first - p2.first)
        + pow2(p1.second - p2.second);
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
               const vector<int>& last_stun,
               const set<int>& stunned_them_idx,
               const int time,
               int& them_idx)
{
    int kept = -1;

    REP(i, SIZE(them)) {
        auto& him = them[i];

        // avoid to stun the same enemy
        if (stunned_them_idx.count(i)) continue;
        // avoid to stun the enemy already stunned
        if (him.state == 2) continue;

        auto d2 = dist2(me.p, him.p);
        if (d2 <= pow2(1760)
            && last_stun[me.id] + 20 <= time
            ) {
            if (him.state == 1 || him.state == 3) {
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

P pick_random_pos() {
    while (true) {
        P ret = P{rand() % W, rand() % H};
        if (rand() % 2) {
            if (rand() % 2) {
                ret.first = 0 + VR;
            }
            else {
                ret.first = W - VR;
            }
        }
        else {
            if (rand() % 2) {
                ret.second = 0 + VR;
            }
            else {
                ret.second = H - VR;
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
    int bustersPerPlayer; // the amount of busters you control
    cin >> bustersPerPlayer; cin.ignore();
    int ghostCount; // the amount of ghosts on the map
    cin >> ghostCount; cin.ignore();
    int myTeamId; // if this is 0, your base is on the top left of the map, if it is one, on the bottom right
    cin >> myTeamId; cin.ignore();

    if (myTeamId == 0) {
        our_base = P{0,0};
        their_base = P{W,H};
    }
    else {
        our_base = P{W,H};
        their_base = P{0,0};
    }

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

    if (our_base.first == W) {
        for(auto& g: initial_goals) {
            g.first = W - g.first;
            g.second = H - g.second;
        }
    }
    
    vector<P> next_goals(bustersPerPlayer);
    REP(i, bustersPerPlayer) {
        next_goals[i] = initial_goals[i];
    }

    vector<int> last_stun(bustersPerPlayer);

    int time = 0;

    // game loop
    while (1) {
        ++time;

        vector<Entity> us;
        vector<Entity> them;
        vector<Entity> ghosts;

        set<int> stunned_them_idx;


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
        
        cerr << "ghost num:" << SIZE(ghosts) << endl;
        for(auto& g: ghosts) cerr << g.id << ",";
        cerr << endl;
        
        
        
        REP(i, SIZE(us)) {
            auto& me = us[i];
            // have ghost
            if (me.state == 1) {
                if (near_our_base(me.p)) {
                    printf("RELEASE %s\n", "release");
                }
                else {
                    printf("MOVE %d %d %s\n",
                           our_base.first, our_base.second, "go home");
                }
            }
            // have no ghost
            else {
                // attempt to stun
                int them_idx = 0;
                if (stunnable(me, them, last_stun, stunned_them_idx, time, them_idx)) {
                    stringstream sout;
                    sout << "stun " << them[them_idx].id;
                    printf("STUN %d %s\n", them[them_idx].id, sout.str().c_str());
                    last_stun[me.id] = time;
                    stunned_them_idx.insert(them_idx);
                }
                else {
                    // is there a ghost nearby?
                    int g_idx;
                    string state;
                    find_closest_ghost(me, ghosts, g_idx, state);

                    if (state == "bustable") {
                        auto& ghost = ghosts[g_idx];
                        printf("BUST %d\n", ghost.id);
                    }
                    else if (state == "too_close") {
                        // TODO: should be more fast
                        printf("MOVE %d %d %s\n", me.p.first, me.p.second, "too close");
                    }
                    else if (state == "nearby") {
                        // TODO: should be more fast
                        auto& ghost = ghosts[g_idx];
                        printf("MOVE %d %d %s\n", ghost.p.first, ghost.p.second, "nearby ghost");
                    }
                    else {
                        // go far to find ghosts
                        if (next_goals[i] == me.p) {
                            // random!
                            // TODO: point on edge
                            next_goals[i] = pick_random_pos();
                        }
                        printf("MOVE %d %d\n", next_goals[i].first, next_goals[i].second);
                    }
                }
            }
        }
    }
}
