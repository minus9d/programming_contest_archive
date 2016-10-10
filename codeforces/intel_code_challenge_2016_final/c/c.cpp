// 左上を原点として解いているので解説図と異なるので注意
// 光線の動きを愚直にシミュレーションして、反射するごとに通った点を調べて記録。
// もっとシンプルに書けないのだろうか？

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

int H, W, K;

//void update_xy(int x_remain, int y_remain, int dir1, int dir2, int& dir, int& x, int& y) {
//    auto dist = min(x_remain, y_remain);
//    if (x_remain >= y_remain) {
//        dir = dir1;
//    }
//    else {
//        dir = dir2;
//    }
//    x += dist;
//    y -= dist;
//}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> W >> H >> K;

    vector<vector<int>> to_rd(H + W);
    vector<vector<int>> to_rt(H + W);

    vector<pair<int, int>> locs;
    REP(k, K) {
        int x, y;
        cin >> x >> y;
        to_rt[x + y].pb(k);
        to_rd[x + (H - y)].pb(k);
        locs.push_back(mp(x, y));
    }

    const ll INF = 1e18;
    vector<ll> ans(K, INF);
    for (auto e : to_rd[0 + (H - 0)]) {
        ans[e] = locs[e].first;
    }

    vector<char> seen_top(W + 1);
    vector<char> seen_bot(W + 1);
    vector<char> seen_left(H + 1);
    vector<char> seen_right(H + 1);

    const int RD = 0;
    const int RT = 1;
    const int LD = 2;
    const int LT = 3;
    int dir = -1;
    int x = -1;
    int y = -1;
    if (W >= H) {
        x = y = H;
        dir = RT;
        seen_bot[H] = 1;
    }
    else {
        x = y = W;
        dir = LD;
        seen_right[H] = 1;
    }

    ll turn = min(H, W);
    while (true) {
        //printf("(x,y) = (%d,%d)\n", x, y);

        int x1 = x;
        int x2 = W - x;
        int y1 = y;
        int y2 = H - y;

        if ((x == 0 && (y == 0 || y == H))
            || (x == W && (y == 0 || y == H))) {
            break;
        }
        if (dir == RT) {
            for (auto e : to_rt[x + y]) {
                ans[e] = min(ans[e], turn + abs(locs[e].first - x));
            }

            auto dist = min(x2, y1);
            if (x2 >= y1) {
                dir = RD;
            }
            else {
                dir = LT;
            }
            x += dist;
            y -= dist;
        }
        else if (dir == LT) {
            for (auto e : to_rd[x + (H - y)]) {
                ans[e] = min(ans[e], turn + abs(locs[e].first - x));
            }

            auto dist = min(x1, y1);
            if (x1 >= y1) {
                dir = LD;
            }
            else {
                dir = RT;
            }
            x -= dist;
            y -= dist;
        }
        else if (dir == RD) {
            for (auto e : to_rd[x + (H - y)]) {
                ans[e] = min(ans[e], turn + abs(locs[e].first - x));
            }

            auto dist = min(x2, y2);
            if (y2 >= x2) {
                dir = LD;
            }
            else {
                dir = RT;
            }
            x += dist;
            y += dist;
        }
        else if (dir == LD) {
            for (auto e : to_rt[x + y]) {
                ans[e] = min(ans[e], turn + abs(locs[e].first - x));
            }

            auto dist = min(x1, y2);
            if (y2 >= x1) {
                dir = RD;
            }
            else {
                dir = LT;
            }
            x -= dist;
            y += dist;
        }

        turn += abs(x - x1);
    }

    for (auto e : ans) {
        if (e == INF) cout << -1 << endl;
        else cout << e << endl;
    }

    return 0;
}
