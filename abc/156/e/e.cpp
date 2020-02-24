// 本番中に解けた
//
// N = 5の場合を例に考える
//
// (i) K = 1のとき (今回の制約では存在しない)
// 5部屋のうち1部屋が0に、4部屋が1以上になる
// 0になる部屋の決め方は 5C1
// 残り4部屋の人のパターンは以下の4通り
//   2 1 1 1
//   1 2 1 1
//   1 1 2 1
//   1 1 1 2
// 各部屋とも1人以上いることが条件なので、すべての部屋から1を引くと
//   1 0 0 0
//   0 1 0 0
//   0 0 1 0
//   0 0 0 1
// この場合の数は、「1個のボールを、3個の仕切りで4分割」する場合の数と同じ。
// よって 4! / (1! * 3!) = 4通り
// (i)の場合の数は 5C1 * 4 = 20通り
//
// (ii) K = 2のとき
// 以下の3パターンのどれか
//   (a) 5部屋すべてが1
//   (b) 5部屋のうち1部屋が0に、4部屋が1以上
//   (c) 5部屋のうち2部屋が0に、3部屋が1以上
// (a)は1通り
// (b)は(i)と同じで20通り
// (c)は(b)と同じように考える
//  0になる部屋の決め方は 5C2
//  3部屋に、5人を、どの部屋にも1人以上になるよう割り振る場合の数は、
//  「2個のボールを、2個の仕切りで3分割」する場合の数と同じ。
//  つまり 4!/(2! * 2!) = 6通り
// (c)の場合の数は 5C2 * 6 = 60通り
//
// 以下同様

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

template<int MOD> struct Fp {
    ll val;
    constexpr Fp(ll v = 0) noexcept : val(v % MOD) {
        if (val < 0) val += MOD;
    }
    constexpr int getmod() { return MOD; }
    constexpr Fp operator - () const noexcept {
        return val ? MOD - val : 0;
    }
    constexpr Fp operator + (const Fp& r) const noexcept { return Fp(*this) += r; }
    constexpr Fp operator - (const Fp& r) const noexcept { return Fp(*this) -= r; }
    constexpr Fp operator * (const Fp& r) const noexcept { return Fp(*this) *= r; }
    constexpr Fp operator / (const Fp& r) const noexcept { return Fp(*this) /= r; }
    constexpr Fp& operator += (const Fp& r) noexcept {
        val += r.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    constexpr Fp& operator -= (const Fp& r) noexcept {
        val -= r.val;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr Fp& operator *= (const Fp& r) noexcept {
        val = val * r.val % MOD;
        return *this;
    }
    constexpr Fp& operator /= (const Fp& r) noexcept {
        ll a = r.val, b = MOD, u = 1, v = 0;
        while (b) {
            ll t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        val = val * u % MOD;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr bool operator == (const Fp& r) const noexcept {
        return this->val == r.val;
    }
    constexpr bool operator != (const Fp& r) const noexcept {
        return this->val != r.val;
    }
    friend constexpr ostream& operator << (ostream &os, const Fp<MOD>& x) noexcept {
        return os << x.val;
    }
    friend constexpr Fp<MOD> modpow(const Fp<MOD> &a, ll n) noexcept {
        if (n == 0) return 1;
        auto t = modpow(a, n / 2);
        t = t * t;
        if (n & 1) t = t * a;
        return t;
    }
};

const ll MOD = 1e9 + 7;
using mint = Fp<MOD>;

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
    ll N, K;
    cin >> N >> K;

    NCK nck(MOD);
    auto table = nck.makeNckTableFromN0ToNN(N, N);

    mint ans = 0;
    mint fact = 0;
    mint prev = 0;
    FOR(k, 1, min(K + 1, N + 1)) {
        if (k == 1) {
            fact = N - 1;
        } else {
            fact /= k;
            fact *= (N - k);
        }

        if (k == 1) {
            ans = fact * table[k];
            // cout << "ans = " << fact << " * " << table[k] << endl;
            prev = ans;
        } else {
            ans += fact * table[k];
            prev = ans;
        }
    }

    if (K == 1) {
        cout << ans << endl;
    } else {
        cout << (ans + 1) << endl;
    }
    return 0;
}
