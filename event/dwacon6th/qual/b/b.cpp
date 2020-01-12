// 本番中に解けた。実験して法則を求めた
//
//  a   b   c   d   e
//  x---x---x---x---x
//    d1  d2  d3  d4
//
//  上記の位置関係を例に取る。
//  スライムdが取り除かれるときの移動距離は
//     24回  d4
//  スライムcが取り除かれるときの移動距離は
//     12回  d3
//     12回  d3 + d4
//  スライムbが取り除かれるときの移動距離は
//     12回  d2
//      4回  d2 + d3
//      8回  d2 + d3 + d4
//  スライムaが取り除かれるときの移動距離は
//     12回  d1
//      4回  d1 + d2
//      2回  d1 + d2 + d3
//      6回  d1 + d2 + d3 + d4
// 上記の登場回数を集計すると
//      d4   24 + 12 + 8 + 6
//      d3   24 + 12 + 8
//      d2   24 + 12
//      d1   24
// これを無駄のないよう足し合わせればOK

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

const ll MOD = ll(1e9) + 7;

class NCK {
private:
    ll m_mod;

public:
    // mod must be a prime number
    NCK(ll mod) : m_mod(mod) {}

    // x^y % m_mod
    ll modPow(ll x, ll y)
    {
        ll r = 1, a = x;
        while (y > 0) {
            if ((y&1) == 1) {
                r = (r * a) % m_mod;
            }
            a = (a * a) % m_mod;
            y /= 2;
        }
        return r;
    }

    // a^-1 ≡ a^(p-2) (mod p)   (p is prime)
    ll modInverse(ll x)
    {
        return modPow(x, m_mod-2);
    }

    // Modular division x / y, find modular multiplicative inverse of y
    // and multiply by x.
    ll modDivision(ll p, ll q)
    {
        return (p * modInverse(q)) % m_mod;
    }

    // Binomial coifficient C(n,k) in O(k) time.
    ll choose(ll n, ll k)
    {
        if (k > n) {
            return 0;
        }
        ll p = 1, q = 1;
        for (int i=1; i<=k; i++) {
            q = (q * i) % m_mod;
            p = (p * (n - i + 1)) % m_mod;
        }
        return modDivision(p, q);
    }

    // make nCk table from 0C0 to nCn
    vector<vector<ll>> makeNckTableFrom00ToNN(ll n_max) {
        assert(n_max > 0);
        vector<vector<ll>> table(n_max+1, vector<ll>(n_max+1));
        table[0][0] = 1;
        FOR(i, 1, n_max + 1) {
            table[i][0] = 1;
            FOR(j, 1, n_max + 1) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % m_mod;
            }
        }
        return table;
    }

    // make nCk table from nC0 to nCn
    vector<ll> makeNckTableFromN0ToNN(ll n, ll k_max) {
        assert(n > 0);
        assert(n >= k_max);
        vector<ll> table(n+1);
        table[0] = 1;
        ll p = 1, q = 1;
        table[0] = 1;
        FOR(i, 1, k_max+1) {
            q = (q * i) % m_mod;
            p = (p * (n - i + 1)) % m_mod;
            table[i] = modDivision(p, q);
        }
        return table;
    }

    // make nCk table from n1Ck to n2Ck
    vector<ll> makeTableFromN1CkToN2Ck(ll n1, ll n2, ll k) {
        vector<ll> table;
        ll tmp = -1;
        FOR(n, n1, n2 + 1) {
            if (n == n1) {
                tmp = this->choose(n, k);
            }
            else {
                tmp *= n;
                tmp %= this->m_mod;
                tmp = this->modDivision(tmp, n - k);
            }
            table.pb(tmp);
        }
        return table;
    }

    // make modInverse table from 0 to n_max
    vector<ll> makeModInverseTable(ll n_max) {
        assert(n_max > 0);
        vector<ll> table(n_max + 1);
        FOR(i, 1, n_max + 1) {
            table[i] = modInverse(i);
        }
        return table;
    }
};


ll solve(ll N, vector<ll>& As) {
    NCK nck(MOD);

    vector<ll> dists;
    REP(i, N - 1) {
        dists.pb(As[i + 1] - As[i]);
    }
    ll dist_sum = accumulate(ALL(dists), 0LL);

    ll factorial = 1;
    REP(n, N - 1) {
        factorial *= (n + 1);
        factorial %= MOD;
    }

    ll ans = 0;
	FOR(n, 2, N + 1) {
        ans += factorial * dist_sum;
        ans %= MOD;

        factorial *= (n - 1);
        factorial %= MOD;

        factorial = nck.modDivision(factorial, n);

        dist_sum -= dists[n - 2];
    }

    return ans % MOD;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N;
    cin >> N;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];

    cout << solve(N, As) << endl;

    return 0;
}
