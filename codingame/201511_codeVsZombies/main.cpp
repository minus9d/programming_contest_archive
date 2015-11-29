#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>

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
#define eb emplace_back

using namespace std;

struct Coord {
    int x;
    int y;
    Coord(int _x, int _y)
        : x(_x), y(_y) {};
    Coord() {};
    void print() {
        fprintf(stderr, "(%d, %d)", x, y);
    }
};

struct Object {
    int id;
    Coord pos;
    Coord goal;
    Object(int _id, int _x, int _y)
        : id(_id)
        , pos(_x, _y)
        {};
    Object(int _id, int _x, int _y, int _x2, int _y2)
        : id(_id)
        , pos(_x, _y)
        , goal(_x, _y)
        {};
};

struct State {
    Coord ashPos;
    vector<Object> humans;
    vector<Object> zombies;
    void print() {
        cerr << "ash: ";
        ashPos.print();
        cerr << "humans: " << endl;
        for (auto& h : humans) {
            cerr << "  ";
            h.pos.print();
            cerr << endl;
        }
        cerr << "zombies: " << endl;
        for (auto& z : zombies) {
            cerr << "  ";
            z.pos.print();
            cerr << ", ";
            z.goal.print();
            cerr << endl;
        }
    }
};

int pow2(int a)
{
    return a * a;
}

int getDist2(const Coord& c1, const Coord& c2)
{
    return pow2(c1.x - c2.x) + pow2(c1.y - c2.y);
}

int getClosestHuman(const State& s)
{
    int mn = 1e9;
    int mn_idx = 0;
    REP(i, SIZE(s.humans))
    {
        int dist2 = getDist2(s.humans[i].pos, s.ashPos);
        if (dist2 < mn) {
            mn = dist2;
            mn_idx = i;
        }
    }
    return mn_idx;
}

/**
 * Save humans, destroy zombies!
 **/
int main()
{
    // game loop
    while (1) {
        State s;
        cin >> s.ashPos.x >> s.ashPos.y; cin.ignore();
        int humanCount;
        cin >> humanCount; cin.ignore();
        REP(i, humanCount) {
            int humanId;
            int humanX;
            int humanY;
            cin >> humanId >> humanX >> humanY; cin.ignore();
            s.humans.emplace_back(humanId, humanX, humanY);
        }
        int zombieCount;
        cin >> zombieCount; cin.ignore();
        REP(i, zombieCount) {
            int zombieId;
            int zombieX;
            int zombieY;
            int zombieXNext;
            int zombieYNext;
            cin >> zombieId >> zombieX >> zombieY >> zombieXNext >> zombieYNext; cin.ignore();
            s.zombies.emplace_back(zombieId, zombieX, zombieY, zombieXNext, zombieYNext);
        }

        s.print();
        
        // Ç∆ÇËÇ†Ç¶Ç∏ç≈äÒÇËÇÃhumanÇÃÇªÇŒÇ≈ë“ã@ÅBÇªÇ§Ç∑ÇÍÇŒëSñ≈ÇÕñhÇ∞ÇÈ
        int closestHumanIdx = getClosestHuman(s);
        Coord goal = s.humans[closestHumanIdx].pos;

        cout << goal.x << " " << goal.y << endl; // Your destination coordinates
    }
}
