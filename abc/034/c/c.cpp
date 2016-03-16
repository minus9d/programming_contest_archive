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

ll MOD = 1000000007;

ll modPow(ll x, ll y)
{
    ll r=1, a=x;
    while (y > 0) {
        if ( (y&1)==1 ) {
            r = (r * a) % MOD;
        }
        a = (a * a) % MOD;
        y /= 2;
    }

    return r;
}

ll modInverse(ll x)
{
    return modPow(x, MOD-2);
}

// Modular division x / y, find modular multiplicative inverse of y
// and multiply by x.
ll modDivision(ll p, ll q)
{
    return (p * modInverse(q)) % MOD;
}

// Binomial coifficient C(n,k) in O(k) time.
ll C(ll n, int k)
{
    if (k > n) {
        return 0;
    }
    ll p = 1, q = 1;
    for (int i=1; i<=k; i++) {
        q = ( q * i) % MOD;
        p = ( p * (n - i + 1) ) % MOD;
    }
    return modDivision( p, q);
}

int main(void)
{
    cin.sync_with_stdio(false);
    int W, H;
    cin >> W >> H;
    cout << C((W+H-2), W-1) << endl;

    return 0;
}
