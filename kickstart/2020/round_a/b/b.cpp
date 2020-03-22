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

void solve() {
    ll N, K, P;
    cin >> N >> K >> P;
    vector<vector<ll>> piles(N, vector<ll>(K));
    REP(n, N) {
        REP(k, K) {
            cin >> piles[n][k];
        }
    }
    vector<vector<ll>> dp(N + 1, vector<ll>(P + 1));
    REP(n, N) {
        REP(p, P + 1) {
            ll sum = 0;
            REP(k, K + 1) {
                if (p + k <= P) {
                    dp[n + 1][p + k] = max(dp[n + 1][p + k],
                                           dp[n][p] + sum);
                }
                if (k != K) {
                    sum += piles[n][k];
                }
            }
        }
    }

    // REP(n, N) {
    //     REP(p, P + 1) {
    //         cout << dp[n][p] << " ";
    //     }
    //     cout << endl;
    // }

    cout << dp[N][P];
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
