// 解説PDFの通り実装

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

int main(void)
{
    int N;
    cin >> N;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];

    ll n_fact = 1;
    REP(n, N) {
        n_fact *= (n + 1);
        n_fact %= MOD;
    }

    // 累積和を求める
    NCK nck(MOD);
    vector<ll> prob(N);
    REP(n, N) {
        prob[n] = nck.modDivision(n_fact, n + 1);
    }
    vector<ll> cum(N);
    REP(n, N) {
        cum[n] = prob[n];
        if (n != 0) cum[n] += cum[n-1];
        cum[n] %= MOD;  // 最初忘れていた
    }

    // 0  1  2  3  4  5  6
    // o  o  o  o  o  o  o
    //       ↑
    // e.g.  n == 2の場合
    // [0, 1, 2]の累積和、[2, 3, 4, 5, 6]の累積和を使う。
    // 2を二重にカウントしてしまうので最後に引く
    ll ans = 0;
    REP(n, N) {
        ans += As[n] * cum[n];
        ans %= MOD;
        ans += As[n] * cum[N-n-1];
        ans %= MOD;
        ans -= As[n] * prob[0];
        ans %= MOD;
    }
    ans += MOD;
    ans %= MOD;
    cout << ans << endl;
    return 0;
}
