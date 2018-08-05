#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
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

using P = pair<int,int>;
const int INF = 1e9;

int H, W, K;
vector<vector<int>> dist;
vector<string> cells;
map<char, pair<int,int>> dydx;

P go_next(P cand, pair<int,int> dir) {
    return P{cand.first + dir.first,
            cand.second + dir.second};
}

bool not_legal(P nxt) {
    auto y = nxt.first;
    auto x = nxt.second;
    return (y < 0 || y >= H || x < 0 || x >= W || cells[y][x] == '#');
}

bool can_move(P nxt) {
    bool move = false;
    for (auto kv : dydx) {
        auto dir = kv.second;
        if (!not_legal(go_next(nxt, dir))) return true;
    }
    return false;
}



int get_next_turn(set<char> movable_dir, int turn) {
    int 
}

// 現在のターン % Kをkとしたとき、次に'U'が来るまでの最短のターン数をnext_turn[k]['U']で返す。
// 'U'が永遠に来ない場合は-1を返す
vector<map<int, int>> next_turn;


int main(void)
{
    dydx['U'] = P(-1, 0);
    dydx['D'] = P(1, 0);
    dydx['L'] = P(0, -1);
    dydx['R'] = P(0, 1);

    cin.sync_with_stdio(false);
    cin >> H >> W >> K;
    string dirs;
    cin >> dirs;
    cells.resize(H);
    REP(h, H) cin >> cells[h];

    dist.resize(H, vector<int>(W, INF));

    P start;
    P goal;

    REP(h, H) REP(w, W) {
        if (cells[h][w] == 'S') {
            start = {h, w};
        }
        else if (cells[h][w] == 'G') {
            goal = {H, w};
        }
    }

    dist[start.first][start.second] = 0;
    set<P> cands; cands.insert(start);

    set<P> seen_dir; // いっても意味のない向きを記録
    int turn = 0;
    while(true) {
        auto dir = dydx[dirs[turn % K]];

        if (cands.empty()) break;

        cout << "cands:";
        for(auto yx: cands) cout << "(" << yx.first << "," << yx.second << ")" << endl;
        cout << "dist:";
        REP(h, H) {
            REP(w, W) cout << dist[h][w] << " ";
            cout << endl;
        }
        for(auto yx: cands) cout << "(" << yx.first << "," << yx.second << ")" << endl;

        set<P> next_cands_tmp = cands;

        // candsの中で移動できる可能性がある向きを列挙
        set<P> movable_dir;
        for (auto cand : cands) {
            bool move = false;
            for (auto kv : dydx) {
                auto dir_char = kv.second;
                auto dir = kv.second;
                auto nxt = go_next(cand, dir);
                if (!not_legal(nxt) && dist[nxt.first][nxt.second] == INF) {
                    movable_dir.insert(dir_char);
                }
            }
        }

        // 移動できる向きがくるまでターンを飛ばす
        turn = get_next_turn(movable_dir, turn);
        if (turn == -1) {
            cout << -1 << endl;
            return 0;
        }

        for(auto cand: cands) {
            P nxt = go_next(cand, dir);
            if (nxt == goal) {
                cout << (dist[cand.first][cand.second]) << endl;

                cout << "dist:" << endl;
                REP(h, H) {
                    REP(w, W) cout << dist[h][w] << " ";
                    cout << endl;
                }
                return 0;
            }
            if (not_legal(nxt)) continue;
            if (dist[nxt.first][nxt.second] != INF) continue;
            next_cands_tmp.insert(nxt);
            dist[nxt.first][nxt.second] = turn + 1;
        }

        cands.clear();
        for (auto cand : next_cands_tmp) {
            if (can_move(cand)) cands.insert(cand);
        }

        ++turn;
    }

    cout << -1 << endl;
    return 0;
}
