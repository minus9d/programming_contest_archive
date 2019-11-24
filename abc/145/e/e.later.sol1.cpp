// 解説PDF https://img.atcoder.jp/abc145/editorial.pdf
// の解法1を実装

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


vector<vector<ll>> dp_solver(vector<ll>& A, vector<ll>& B, ll T) {

    ll N = SIZE(A);
    vector<vector<ll>> dp(N + 1, vector<ll>(3001));

    REP(n, N) {
        ll a = A[n];
        ll b = B[n];
        REP(time, T + 1) {
            dp[n + 1][time] = dp[n][time];
        }

        REP(time, T + 1) {
            auto before_time = time - a;
            if (before_time < 0) continue;
            dp[n + 1][time] = max(dp[n + 1][time],
                                  dp[n][before_time] + b);
        }
    }
    return dp;
}


ll solve(ll N, ll T, vector<ll>& A, vector<ll>& B) {
    auto dp1 = dp_solver(A, B, T);

    reverse(ALL(A));
    reverse(ALL(B));
    auto dp2 = dp_solver(A, B, T);
    reverse(ALL(A));
    reverse(ALL(B));

    ll ans = 0;

    // 最後に食べる料理をnとする
    REP(n, N) {
        ll local_ans = 0;
        REP(t, T) {
            auto tmp1 = dp1[n][t];
            auto tmp2 = dp2[N - n - 1][T - 1 - t];
            local_ans = max(local_ans, tmp1 + tmp2 + B[n]);
        }
        ans = max(ans, local_ans);
    }

    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, T;
    cin >> N >> T;
    vector<ll> A(N);
    vector<ll> B(N);

    REP(n, N) {
        ll a, b;
        cin >> a >> b;
        A[n] = a;
        B[n] = b;
    }
    cout << solve(N, T, A, B) << endl;
    return 0;
}
