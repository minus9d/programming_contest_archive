// 解説PDFの通り実装
// 白→黒に入れ替わる回数を数える
// もし開始セルが黒なら+1

#include <algorithm>
#include <array>
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
typedef long long ll;
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())
template<class T> inline bool chmin(T& a, T b) {
    if (a > b) {
        a = b; return true;
    }
    return false;
}
template<class T> inline bool chmax(T& a, T b) {
    if (a < b) {
        a = b; return true;
    }
    return false;
}
#define pb push_back
#define mp make_pair
#define mt make_tuple

int main(void)
{
    cin.sync_with_stdio(false);
    int H, W;
    cin >> H >> W;
    vector<string> cells(H);
    REP(h, H) cin >> cells[h];

    vector<vector<int>> dp(H, vector<int>(W, 1e9));
    dp[0][0] = 0;
    REP(h, H) {
        REP(w, W) {
            if (w != 0) {
                chmin(dp[h][w],
                      dp[h][w - 1]
                      + (cells[h][w - 1] == '.' && cells[h][w] == '#'));
            }
            if (h != 0) {
                chmin(dp[h][w],
                      dp[h - 1][w]
                      + (cells[h - 1][w] == '.' && cells[h][w] == '#'));
            }
        }
    }

    // REP(h, H) {
    //     REP(w, W) {
    //         cout << dp[h][w] << " ";
    //     }
    //     cout << endl;
    // }

    auto ans = dp[H-1][W-1];
    ans += (cells[0][0] == '#');
    cout << ans << endl;

    return 0;
}
