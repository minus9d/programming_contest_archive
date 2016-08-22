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

const ll MOD = 1000000007;
 
int main(void)
{
    cin.sync_with_stdio(false);
    ll N, C;
    cin >> N >> C;
    vector<ll> As(N);
    vector<ll> Bs(N);
    REP(n,N) cin >> As[n];
    REP(n,N) cin >> Bs[n];

    vector<vector<ll>> dp(N+1, vector<ll>(C+1));
    REP(n,N) {
        if (n == 0) {
            ll v = 1;
            REP(c,C+1){
                dp[n][c] = v;
                v = (v * As[0]) % MOD;
            }
        }
        else {
            REP(c,C+1){
                ll v = 1;
                REP(c2,c+1) {
                    dp[n][c] += dp[n-1][c-c2] * v;
                    dp[n][c] %= MOD;
                    v = (v * As[n]) % MOD;
                }
            }
        }

        // cout << "n:" << n << endl;
        // cout << "  ";
        // REP(c,C+1) cout << dp[n][c] << ",";
        // cout << endl;
    }

    cout << dp[N-1][C] << endl;
    return 0;
}

