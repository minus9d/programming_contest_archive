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

/////////////
// Libraries
/////////////

class UnionFind
{
public:
    UnionFind(){};
    ~UnionFind(){};

    void Init(int num_entries) {
        num_entries_ = num_entries;
        par_.resize(num_entries_);
        rank_.resize(num_entries_, 0);
        for (int i = 0; i < num_entries_; ++i)
        {
            par_[i] = i;
        }
    }
    int Find(int x) {
        if (par_[x] == x)
        {
            return x;
        }
        else
        {
            return par_[x] = Find(par_[x]);
        }
    }
    
    void Unite(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;

        if (rank_[x] < rank_[y])
        {
            par_[x] = y;
        }
        else
        {
            par_[y] = x;
            if (rank_[x] == rank_[y])
            {
                rank_[x]++;
            }
        }
    }
    bool Same(int x, int y) {
        return Find(x) == Find(y);
    }

private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
};


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
    int num_of_set_bombs;
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
    vector<Player> you;
    vector<Bomb> bombs;
    vector<Item> items;
};

struct GlobalState {
    bool at_least_one_bomb_is_set = false;
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

const int TIMER_MAX = 8;

const P NO_MOVE = P{-1,-1};

const int ITEM_EXTRA_RANGE = 1;
const int ITEM_EXTRA_BOMB = 2;

const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};

// globals
int W;
int H;
int MYID;
GlobalState gs;

string ptos(const P& pos) {
    ostringstream sout;
    sout << pos.x << " " << pos.y;
    return sout.str();
}

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
bool is_untargeted_box(const State& s, const P& p) {
    if (!within_board(s, p)) return false;
    auto ch = s.cells[p.y][p.x];
    return (ch == BOX_SIGN1 || ch == BOX_SIGN2);
}

bool is_item(const State& s, const P& p) {
    if (!within_board(s, p)) return false;
    auto ch = s.cells[p.y][p.x];
    return ch == ITEM_SIGN;
}

bool is_cell_in_safe(const State& s, const P& p) {
    for(auto& b: s.bombs) {
        if (same_pos(p, b.pos)) return false;
        REP(d,4) {
            FOR(i,1,b.expl_range) {
                P p2{b.pos.x + dx[d] * i, b.pos.y + dy[d] * i};
                if (!within_board(s, p2)) break;
                if (is_wall(s, p2)) break;
                if (is_box(s, p2)) break;
                if (is_bomb(s, p2)) break;
                if (same_pos(p, p2)) return false;
            }
        }
    }
    return true;
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
                s.you.pb( Player{ owner, param1, param2, P{x,y} } );
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
                if (is_untargeted_box(s, p2)) {
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


P find_object(const State& s, std::function<bool(const State& s, const P& p)> func)
{
    // BFS
    queue<P> q;
    set<P> seen;
    q.push(s.me.pos);
    P ini = s.me.pos;
    seen.insert(ini);

    // for backtrace
    map<P, P> parents;
    parents[ini] = NO_MOVE;

    int loop_num = 0;
    while(!q.empty()) {
        P p = q.front();
        q.pop();

        if (func(s, p)) {
            if (same_pos(ini,p)) 
                return p;

            // backtrace and return the initial move
            while(!same_pos(parents[p],ini)) {
                p = parents[p];
            }
            return p;
        }

        REP(i,4) {
            P p2 = p;
            p2.x += dx[i];
            p2.y += dy[i];
            if (within_board(s, p2) && is_floor(s, p2) && !seen.count(p2)) {
                q.push(p2);
                seen.insert(p2);
                parents[p2] = p;
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

P find_nearest_item(const State& s) {
    return find_object(s, is_item);
}

P find_safe_pos(const State& s) {
    // todo: take timer into account
    return find_object(s, is_cell_in_safe);
}

bool box_will_be_destroyed_by_putting_bomb(const State& s, const P& p) {
    // bomb can put only on floor
    if (!is_floor(s, p)) return false;

    // avoid suicide
    State s_copy = s;
    s_copy.bombs.pb( Bomb{ s.me.id, TIMER_MAX, s.me.expl_range, p } );
    s_copy.me.pos = p;

    auto safe_pos = find_safe_pos(s_copy);
    if (same_pos(safe_pos, NO_MOVE)) {
        return false;
    }

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

P find_nearest_bomb_sight(const State& s) {
    return find_object(s, box_will_be_destroyed_by_putting_bomb);
}

bool calc_explosion_time(const State& s_orig) {
    // TODO
    State s = s_orig;

    // pos to bomb_idx table
    map<P, int> pos_to_bomb_idx;
    REP(i, SIZE(s.bombs)) {
        auto& b = s.bombs[i];
        pos_to_bomb_idx[b.pos] = i;
    }

    // union-find to connect bombs
    UnionFind uf;
    uf.Init(SIZE(s.bombs));
    REP(i, SIZE(s.bombs)) {
        auto& b = s.bombs[i];
        REP(d,4) {
            FOR(i,1,b.expl_range) {
                P p2{b.pos.x + dx[d] * i, b.pos.y + dy[d] * i};
                if (!within_board(s, p2)) break;
                if (is_wall(s, p2)) break;
                if (is_box(s, p2)) break;
                if (is_bomb(s, p2)) {
                    auto idx = pos_to_bomb_idx[p2];
                    uf.Unite(i, idx);
                }
            }
        }
    }

    // overwrite bombs' timer
    map<int,int> ufid_to_timer;
    REP(i, SIZE(s.bombs)) {
        auto& b = s.bombs[i];
        auto ufid = uf.Find(i);
        if (ufid_to_timer.count(ufid)) {
            ufid_to_timer[ufid] = min(ufid_to_timer[ufid],b.timer);
        }
        else {
            ufid_to_timer[ufid] = b.timer;
        }
    }
    REP(i, SIZE(s.bombs)) {
        auto& b = s.bombs[i];
        auto ufid = uf.Find(i);
        b.timer = ufid_to_timer[ufid];
    }

    // todo
}


string decide_action(const State& s) {
    // if in dange cell, escape
    if (!is_cell_in_safe(s, s.me.pos)) {
        auto safe_pos = find_safe_pos(s);
        if (same_pos(safe_pos, NO_MOVE)) {
            return "MOVE " + ptos(s.me.pos) + " fin";
        }
        else {
            return "MOVE " + ptos(safe_pos) + " escape";
        }
    }

    const auto pos = find_nearest_bomb_sight(s);
    if (!same_pos(pos, NO_MOVE)) {
        if (pos == s.me.pos) {
            ostringstream sout;
            sout << "BOMB " << pos.x << " " << pos.y << " set_bomb";
            gs.at_least_one_bomb_is_set = true;
            return sout.str();
        }

        if (!is_cell_in_safe(s, pos)) {
            // do nothing
            return "MOVE " + ptos(s.me.pos) + " freeze";
        }

        return "MOVE " + ptos(pos) + " go_to_set_bomb";
    }

    // do nothing
    return "MOVE " + ptos(s.me.pos) + " do_nothing";
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
        auto ret = decide_action(s);
        cout << ret << endl;
    }
}

