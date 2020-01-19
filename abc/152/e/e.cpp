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

// verify
// Nを素因数分解して、<素因数, 登場回数>のペアを得る
// N=12に対して <2, 2>, <3, 1>を得る
map<ll, int> getFactorsMap(ll N){
    map<ll, int> ret;
    while(!(N % 2)){
        N /= 2;
        ++ret[2];
    }
    for (ll p = 3; p*p <= N; p += 2) {
        while (N % p == 0) {
            N /= p;
            ++ret[p];
        }
    }
    if (N > 1) ++ret[N];
    return ret;
}

// 2数の最大公約数
ll getGcdSimple(const ll a, const ll b)
{
    if (b == 0) return a;
    return getGcdSimple(b, a % b);
}

// 2数の最小公倍数
ll getLcmSimple(const ll a, const ll b)
{
    return a / getGcdSimple(a, b) * b;
}

// 数のリストから最大公約数を求める
ll getGcd(const vector<ll>& n){
    auto size = SIZE(n);
    assert(size > 0);
    ll ans = n[0];
    FOR(i, 1, size) ans = getGcdSimple(ans, n[i]);
    return ans;
}

const ll MOD = 1e9 + 7;

// 数のリストからleast common multiple(最小公倍数)を求める
ll getLcm(const vector<ll>& n){
    map<ll, int> allFactors;
    for(size_t i = 0; i < n.size(); ++i){
        map<ll, int> factors = getFactorsMap(n[i]);
        for(auto it = factors.begin();
            it != factors.end();
            ++it){
            if (allFactors[ it->first ] < it->second){
                allFactors[ it->first ] = it->second;
            }
        }
    }
    ll ret = 1;
    for(map<ll, int>::iterator it = allFactors.begin();
        it != allFactors.end();
        ++it){
        for(int i = 0; i < it->second; ++i){
            ret *= it->first;
            ret %= MOD;
        }
    }
    return ret;
}

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

        // n < kのときは nCk = 0
        FOR(n, n1, k) {
            table.pb(0);
        }

        ll tmp = -1;
        FOR(n, k, n2 + 1) {
            if (n == k) {
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

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];

    auto res = getLcm(As);
    NCK nck(MOD);

    ll ans = 0;
    for(auto a: As) {
        ans += res * nck.modInverse(a);
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}
