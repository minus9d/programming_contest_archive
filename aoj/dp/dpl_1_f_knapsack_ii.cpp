// 0-1 ナップサック その2
// 蟻本p60と同じ
// 重さに対する価値の値が小さいので、価値に対する最小の重さをDPで計算する

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
#include <climits>
#include <cassert>

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

// N: 品物の個数
// W: ナップサックの容量
// MAX_V: 品物の最大の価値
// Vs: 品物の価値
// Ws: 品物の重さ
ll knapsack(ll N, ll W, ll MAX_V, vector<ll>& Vs, vector<ll>& Ws) {
    ll INF = 1e18;
    // dp[i+1][j] := i番目までの品物から価値の総和がjとなるように選んだときの
    //               重みの総和の最小値
    vector<vector<ll>> dp(N + 1, vector<ll>(N * MAX_V + 1, INF));
    dp[0][0] = 0;

    REP(i, N) {
        REP(j, N * MAX_V + 1) {
            if (j < Vs[i]) dp[i + 1][j] = dp[i][j];
            else dp[i + 1][j] = min(dp[i][j], dp[i][j - Vs[i]] + Ws[i]);
        }
    }
    ll ans = 0;
    REP(i, N * MAX_V + 1) {
        if (dp[N][i] <= W) ans = i;
    }
    return ans;
}

int main(){
    ll N, W;
    cin >> N >> W;
    vector<ll> Vs(N);
    vector<ll> Ws(N);
    REP(n, N) cin >> Vs[n] >> Ws[n];
    auto ans = knapsack(N, W, 100, Vs, Ws);
    cout << ans << endl;

    return 0;
}
