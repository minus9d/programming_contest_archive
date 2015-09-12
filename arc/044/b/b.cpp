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

int N;
vector<int> as;

ll MOD = 1000000007;

ll mod_pow(ll x, ll n, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

ll f1(ll n1, ll n2)
{
    ll a = mod_pow(2, n2, MOD);
    ll b = a - 1;
    return mod_pow(b, n1, MOD);
}

// 2^(nC2)
ll f2(ll n1)
{
    if (n1 == 1) return 1;
    return mod_pow(2, n1 * (n1 - 1) / 2, MOD);
}

ll solve()
{
    // コーナーケース
    if (N == 1) {
        return (as[0] == 0) ? 1 : 0;
    }

    if (as[0] != 0) {
        return 0;
    }
    else {
        map<int,int> nums;
        REP(n,N) nums[ as[n] ]++;
        
        int seen = 0;
        int key = 0;
        int prev = -1;
        ll ret = 1;
        while(1) {
            int vs = nums[key];

            if (key == 0) {
                if (vs != 1) return 0;
            }

            if (vs == 0) {
                return 0;
            }

            if (key == 1) {
                // vs個の頂点間で線を引く引き方
                ret = f2(vs) % MOD;
            }
            else {
                // vs個の頂点のそれぞれから、prev個の頂点の少なくとも1つに線を引く引き方
                auto n1 = f1(vs, prev);
                // vs個の頂点間で線を引く引き方
                auto n2 = f2(vs);

                auto n3 = (n1 * n2) % MOD;
                ret = (ret * n3) % MOD;
            }

            prev = vs;
            seen += vs;
            key++;
            if (seen == N) break;
        }
        return ret;
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N;

    as.resize(N);
    REP(n,N) cin >> as[n];

    cout << solve() << endl;

    return 0;
}
