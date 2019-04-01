// 解説PDfを見た
//
// 解説でわからなかったのが、
// 直前の文字が "3 2 7 2"で、つぎ3がくると"5 7 5"が完成してしまうのを
// どうやって検知するかということ。
// 検知には、右から5, 12, 17番目のビットを見ればよい。
//
// 例えば、10010100000010 に 100 を結合すると、
// 10010100000010100。これの右から5, 12, 17番目は1なので
// 575が完成してしまっていることがわかる

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

ll dp[41][300000];
ll MOD = ll(1e9) + 7;

string bin(ll i) {
    string ret;
    while(i) {
        ret += '0' + (i % 2);
        i /= 2;
    }
    reverse(ALL(ret));
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, X, Y, Z;
    cin >> N >> X >> Y >> Z;

    auto MAX_DIGIT = 10;
    auto MAX = X + Y + Z;
    dp[0][0] = 1;
    FOR(n, 1, N + 1) {
        REP(i, 1 << (MAX + 1)) {
            FOR(j, 1, MAX_DIGIT + 1) {
                auto next_i = i << j;
                next_i |= (1 << (j - 1));
                if ((next_i & (1 << (X + Y + Z - 1)))
                    && (next_i & (1 << (Y + Z - 1)))
                    && (next_i & (1 << (Z - 1)))) {
                    
                    //if (n == 4 && dp[n - 1][i]) {
                    //    cout << bin(next_i) << " " << dp[n - 1][i] << endl;
                    //}

                    continue;
                }
                next_i &= ((1 << (MAX + 1)) - 1);
                dp[n][next_i] += dp[n - 1][i];
                dp[n][next_i] %= MOD;
            }
        }
    }



    ll ans1 = 0;
    REP(i, 1 << (MAX + 1)) {
        ans1 += dp[N][i];
        ans1 %= MOD;
    }

    ll ans2 = 1;
    REP(i, N) {
        ans2 *= MAX_DIGIT;
        ans2 %= MOD;
    }

    ll ans = ((ans2 - ans1) + MOD) % MOD;
    cout << ans << endl;

    return 0;
}
