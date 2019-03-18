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

const ll MOD = 1000000007;

int main(void)
{
    cin.sync_with_stdio(false);
    ll N;
    cin >> N;

    vector<ll> prev_loc(2 * 100001, -1);
    vector<ll> dp(N + 10);
    dp[0] = 1;
    FOR(n, 1, N + 1) {
        ll c;
        cin >> c;
        if (n == 1) {
            dp[n] = 1;
        }
        else {
            dp[n] = dp[n - 1];
            if (prev_loc[c] == -1
                || prev_loc[c] == n - 1) {
                // do nothing
            }
            else {
                dp[n] += dp[prev_loc[c]];
                dp[n] %= MOD;
            }
        }
        prev_loc[c] = n;
    }
    cout << dp[N] << endl;

    // REP(n, N + 1) cout << dp[n] << ","; cout << endl;

    return 0;
}
