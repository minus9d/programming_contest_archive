#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
#include <cstdlib>

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
    return (pow2(900) <= d2 && d2 <= pow2(1760));
}

void find_closest_ghost(const Entity& me, const vector<Entity>& ghosts,
                        int& g_idx, bool& ok)
{
    ok = false;
    ll nearest = 1e15;
    REP(i, SIZE(ghosts)) {
        auto& g = ghosts[i];
        auto d2 = dist2(me.p, g.p);
        if (can_bust(d2)) {
            g_idx = i;
            ok = true;
            return;
        }

        if (d2 < nearest) {
            nearest = d2;
            g_idx = i;
        }
    }
}

bool near_base(P& p, P& base) {
    auto d2 = dist2(p, base);
    return d2 <= pow2(1600);
}

/**
 * Send your busters out into the fog to trap ghosts and bring them home!
 **/
int main()
{
    int bustersPerPlayer; // the amount of busters you control
    cin >> bustersPerPlayer; cin.ignore();
    int ghostCount; // the amount of ghosts on the map
    cin >> ghostCount; cin.ignore();
    int myTeamId; // if this is 0, your base is on the top left of the map, if it is one, on the bottom right
    cin >> myTeamId; cin.ignore();

    P base;
    if (myTeamId == 0) {
        base = P{0,0};
    }
    else {
        base = P{16000,9000};
    }

    // game loop
    while (1) {
        vector<Entity> us;
        vector<Entity> them;
        vector<Entity> ghosts;

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
        
        
        

        for(auto& me: us) {
            if (me.state == 1) {
                if (near_base(me.p, base)) {
                    printf("RELEASE\n");
                }
                else {
                    printf("MOVE %d %d\n", base.first, base.second);
                }
            }
            else {
                if (SIZE(ghosts) == 0) {
                    // printf("MOVE %d %d\n",
                    // me.p.first + 500 * ((rand() % 3) - 1),
                    // me.p.second + 500 * ((rand() % 3) - 1)
                    // );
                    if (base.first == 0) {
                        printf("MOVE 16000 9000\n");
                    }
                    else {
                        printf("MOVE 0 0\n");
                    }
                }
                else {
                    int g_idx;
                    bool ok;
                    find_closest_ghost(me, ghosts, g_idx, ok);
                    auto& ghost = ghosts[g_idx];
    
                    if (ok) {
                        printf("BUST %d\n", ghost.id);
                    }
                    else {
                        printf("MOVE %d %d\n", ghost.p.first, ghost.p.second);
                    }
                }
            }
        }
    }
}
