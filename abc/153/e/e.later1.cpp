// 本番中に考えていた方針そのままで
// バグのみを修正したもの
//
// DPの形が汚い

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

ll H, N;
vector<ll> As;
vector<ll> Bs;


ll solve_fast(ll N, vector<ll>& As, vector<ll>& Bs) {
    vector<vector<ll>> dp(N + 1, vector<ll>(H + 10010, 1e18));
    dp[0][0] = 0;
    REP(i, N) {
        ll a = As[i];
        ll b = Bs[i];

        dp[i + 1][0] = 0;
        REP(k, 1e9) {
            if (a * k >= H * 2 + 10) break;
            dp[i + 1][a * k] = b * k;
        }

        // 本番時はこれでWA
        // 魔力1で体力10000減らせる魔法があり、
        // かつH = 100のときに失敗
        // REP(j, H * 2 + 10) {

        // 正しくは以下
        REP(j, H + 10000) {
            dp[i + 1][j] = min(dp[i + 1][j],
                               dp[i][j]);
            if (j - a >= 0) {
                if (dp[i][j - a] != 1e18) {
                    dp[i + 1][j] = min(dp[i + 1][j],
                                       dp[i][j - a] + b);
                }
                if (dp[i + 1][j - a] != 1e18) {
                    dp[i + 1][j] = min(dp[i + 1][j],
                                       dp[i + 1][j - a] + b);
                }
            }
        }
    }

    ll ans = 1e18;

    // 本番時は以下
    // FOR(h, H, H * 2 + 10) {

    // 正しくは以下
    FOR(h, H, H + 10000) {
        ans = min(ans, dp[N][h]);
    }
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> H >> N;
    As.resize(N);
    Bs.resize(N);
    REP(n, N) {
        cin >> As[n] >> Bs[n];
    }
    cout << solve_fast(N, As, Bs) << endl;

    return 0;
}
