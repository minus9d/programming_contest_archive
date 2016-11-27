// 解説pdf通りに実装

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

const int MAX = 1e9;
int main(void)
{
    cin.sync_with_stdio(false);
    int H, W;
    cin >> H >> W;
    vector<string> cells_ini(H);
    REP(h, H) cin >> cells_ini[h];

    // 縦横入れ替え
    vector<string> cells(W);
    REP(h, H) REP(w, W) {
        cells[w] += cells_ini[h][w];
    }

    int ret = 0;

    // i列目とi+1(=j)列目との間での処理を考える
    REP(i, W - 1) {
        auto j = i + 1;

        // 初期状態から、i列目をx段、2列目をy段沈めるまでのコスト
        vector<vector<int>> dp(H + 1, vector<int>(H + 1, MAX));

        // i列目がx, j列目がy沈んでいるときのコストを前計算しておく
        vector<vector<int>> cost(H + 1, vector<int>(H + 1));

        // 愚直にやるとH^3で間に合わない　以下はそのコード
        //REP(x,H+1) {
        //    REP(y,H+1) {
        //        REP(h, H) {
        //            if (h >= x && h >= y) {
        //                cost[x][y] += (cells[i][h-x] == cells[j][h-y]);
        //            }
        //        }
        //    }
        //}

        // 改善版
        for (int y = H - 1; y >= 0; --y) {
            for (int x = H - 1; x >= 0; --x) {
                cost[x][y]
                    = cost[x + 1][y + 1]
                    + (cells[i][H - x - 1] == cells[j][H - y - 1]);
            }
        }

        dp[0][0] = 0;
        FOR(sum, 1, 2*H+1) {
            REP(x, sum+1) {
                auto y = sum - x;
                if (x > H || y > H) continue;
                if (x-1 >= 0) dp[x][y] = min(dp[x][y], dp[x - 1][y] + cost[x - 1][y]);
                if (y-1 >= 0) dp[x][y] = min(dp[x][y], dp[x][y - 1] + cost[x][y - 1]);
            }
        }
        ret += dp[H][H];
    }
    cout << ret << endl;
    return 0;
}
