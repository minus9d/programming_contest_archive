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

struct P {
    int x;
    int y;
};

// this function enables set<P>
inline bool operator<(const P& lhs, const P& rhs)
{
    return lhs.x == rhs.x ? (lhs.y < rhs.y) : lhs.x < rhs.x;
}

// not effective??
inline bool operator==(const P& lhs, const P& rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

struct Player {
    int id;
    int num_of_bombs;
    int expl_range;
    P pos;
};

struct Bomb {
    int owner;
    int timer;
    int expl_range;
    P pos;
};

struct Item {
    int item_type;
    P pos;
};

struct State {
    vector<string> cells;
    Player me;
    Player you;
    vector<Bomb> bombs;
    vector<Item> items;
};

const char FLOOR_SIGN = '.';
const char BOX_SIGN1 = '1';
const char BOX_SIGN2 = '2';
const char DBOX_SIGN1 = '3';
const char DBOX_SIGN2 = '4';
const char WALL_SIGN = 'X';

const char BOMB_SIGN = 'B';
const char ITEM_SIGN = 'I';


const int PLAYER = 0;
const int BOMB = 1;
const int ITEM = 2;

const int ME = 0;
const int YOU = 1;

const P NO_MOVE = P{-1,-1};

const int ITEM_EXTRA_RANGE = 1;
const int ITEM_EXTRA_BOMB = 2;

const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};

// globals
int W;
int H;
int MYID;

bool same_pos(const P& p1, const P& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

void print_cells(const State& s) {
    for(auto& line: s.cells) {
        cerr << line << endl;
    }
    cerr << endl;
}

void print_pos(const P& p) {
    cerr << "(" << p.x << "," << p.y << ")" << endl;
}

bool within_board(const State& s, const P& p) {
    return 0 <= p.x && p.x <= W-1 && 0<= p.y && p.y <= H-1;
}

// TODO: bomb check
bool is_floor(const State& s, const P& p) {
    if (!within_board(s, p)) return false;
    auto ch = s.cells[p.y][p.x];
    return ch == FLOOR_SIGN || ch == ITEM_SIGN;
}

bool is_wall(const State& s, const P& p) {
    return within_board(s, p) && s.cells[p.y][p.x] == WALL_SIGN;
}

bool is_bomb(const State& s, const P& p) {
    return within_board(s, p) && s.cells[p.y][p.x] == BOMB_SIGN;
}

// TODO: bomb check
bool is_box(const State& s, const P& p) {
    if (!within_board(s, p)) return false;
    auto ch = s.cells[p.y][p.x];
    return (ch == BOX_SIGN1
         || ch == BOX_SIGN2
         || ch == DBOX_SIGN1
         || ch == DBOX_SIGN2);
}

// whether p is a box which is not targeted by any bomb
bool is_bombable_box(const State& s, const P& p) {
    if (!within_board(s, p)) return false;
    auto ch = s.cells[p.y][p.x];
    return (ch == BOX_SIGN1 || ch == BOX_SIGN2);
}

bool is_item(const State& s, const P& p) {
    if (!within_board(s, p)) return false;
    auto ch = s.cells[p.y][p.x];
    return ch == ITEM_SIGN;
}


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
                s.me = Player{ owner, param1, param2, P{x,y} };
            }
            else {
                s.you = Player{ owner, param1, param2, P{x,y} };
            }
        }
        else if (entityType == BOMB) {
            s.bombs.pb( Bomb{ owner, param1, param2, P{x,y} } );
        }
        else if (entityType == ITEM) {
            s.items.pb( Item{ param1, P{x,y} } );
        }
    }

    // overwrite 'I' signs on items
    for(auto& i: s.items) {
        s.cells[i.pos.y][i.pos.x] = 'I';
    }

    // overwrite 'B' signs on bombs
    for(auto& b: s.bombs) {
        s.cells[b.pos.y][b.pos.x] = 'B';
    }

    // check boxes which will be destroyed
    for(auto& b: s.bombs) {
        int range = b.expl_range;
        REP(d,4) {
            FOR(i,1,range) {
                P p2{b.pos.x + dx[d] * i, b.pos.y + dy[d] * i};
                if (!within_board(s, p2)) break;
                if (is_wall(s, p2)) break;
                if (is_bomb(s, p2)) break;
                if (is_bombable_box(s, p2)) {
                    if (s.cells[p2.y][p2.x] == BOX_SIGN1) {
                        s.cells[p2.y][p2.x] = DBOX_SIGN1;
                    }
                    if (s.cells[p2.y][p2.x] == BOX_SIGN2) {
                        s.cells[p2.y][p2.x] = DBOX_SIGN2;
                    }
                    break;
                }
            }
        }
    }

    return s;
}


// 
bool bombable(const State& s, const P& p) {
    // can't put a bomb!
    if (!is_floor(s, p)) return false;
    auto range = s.me.expl_range;
    REP(d, 4) {
        REP(i, range) {
            P p2{p.x + dx[d] * i, p.y + dy[d] * i};
            if (is_wall(s, p2)) break;
            if (is_box(s, p2)) return true;
        }
    }
    return false;
}

P find_object(const State& s, std::function<bool(const State& s, const P& p)> func)
{
    // BFS
    queue<P> q;
    set<P> seen;
    q.push(s.me.pos);
    P tmp = s.me.pos;
    seen.insert(tmp);

    int loop_num = 0;
    while(!q.empty()) {
        P p = q.front();
        q.pop();

        if (func(s, p)) {
            return p;
        }

        REP(i,4) {
            P p2 = p;
            p2.x += dx[i];
            p2.y += dy[i];
            if (within_board(s, p2) && is_floor(s, p2) && !seen.count(p2)) {
                q.push(p2);
                seen.insert(p2);
            }
        }
        ++loop_num;
        if (loop_num > 1000) {
            cerr << "something's wrong! infinite loop" << endl;
            cerr << "popped is ";
            print_pos(p);
        }
    }

    return P{-1,-1};
}

P find_nearest_bomb_sight(const State& s) {
    return find_object(s, bombable);
}

P find_nearest_item(const State& s) {
    return find_object(s, is_item);
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
        print_cells(s);

        const auto pos = find_nearest_bomb_sight(s);

        cerr << "cur pos:";
        print_pos(s.me.pos);
        cerr << "target pos:";
        print_pos(pos);


        // nothing to do
        if (same_pos(pos, NO_MOVE)) {
            cout << "BOMB 6 5" << endl;
        }
        else {
            const auto item = find_nearest_item(s);
            if (s.me.num_of_bombs == 0 && !same_pos(item, NO_MOVE)) {
                cout << "MOVE " << item.x << " " << item.y << endl;
            }
            else {
                if (pos == s.me.pos) {
                    cout << "BOMB " << pos.x << " " << pos.y << endl;
                }
                else {
                    cout << "MOVE " << pos.x << " " << pos.y << endl;
                }
            }
        }
    }
}

