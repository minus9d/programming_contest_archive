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
#include <iomanip>

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

const int PLAYER = 0;
const int BOMB = 1;

const int ME = 0;
const int YOU = 1;

// globals
int W;
int H;
int MYID;

struct Player {
    int id;
    int num_of_bombs;
    int expl_range;
};

struct Bomb {
    int owner;
    int timer;
    int expl_range;
};

struct State {
    vector<string> cells;
    Player me;
    Player you;
    vector<Bomb> bombs;
};

State get_state() {
    State s;
    s.cells.resize(H);
    REP(h, H) {
        cin >> s.cells[h];
    }
    int entities;
    cin >> entities; cin.ignore();
    for (int i = 0; i < entities; i++) {
        int entityType;
        int owner;
        int x;
        int y;
        int param1;
        int param2;
        cin >> entityType >> owner >> x >> y >> param1 >> param2; cin.ignore();
        if (entityType == PLAYER) {
            if (owner == MYID) {
                s.me = Player{ owner, param1, param2 };
            }
            else {
                s.you = Player{ owner, param1, param2 };
            }
        }
        else {
            s.bombs.pb( Bomb{ owner, param1, param2 } );
        }
    }
    return s;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    cin >> W >> H >> MYID; cin.ignore();

    // game loop
    while (1) {
        State s = get_state();
        cout << "BOMB 6 5" << endl;
    }
}
