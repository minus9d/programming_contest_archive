#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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

ll N, K, R, S, P;
string T;

ll judge(char player, char machine) {
    if (player == 'r' && machine == 's') return R;
    if  (player == 's' && machine == 'p') return S;
    if  (player == 'p' && machine == 'r' ) return P;
    return 0;
}

ll func(vector<char> &arr) {
    ll dp[N][3];
    auto size = SIZE(arr);
    REP(i, size) {
        if (i == 0) {
            dp[i][0] = judge('r', arr[i]);
            dp[i][1] = judge('s', arr[i]);
            dp[i][2] = judge('p', arr[i]);
        } else {
            dp[i][0] = max(dp[i-1][1], dp[i-1][2]) +  judge('r', arr[i]);
            dp[i][1] = max(dp[i-1][2], dp[i-1][0]) +  judge('s', arr[i]);
            dp[i][2] = max(dp[i-1][0], dp[i-1][1]) +  judge('p', arr[i]);
        }
    }
    ll ans = 0;
    REP(j, 3) ans = max(ans, dp[size-1][j]);
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> K >> R >> S >> P >> T;

    ll ans = 0;
    REP(k, K) {
        vector<char> arr;
        ll i = k;
        while(i < N) {
            arr.pb(T[i]);
            i += K;
        }
        ans += func(arr);
    }
    cout << ans << endl;
    return 0;
}

