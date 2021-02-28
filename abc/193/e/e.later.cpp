// 解説通りに実装

#include <algorithm>
#include <array>
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

#include <atcoder/math>

using namespace std;
typedef long long ll;
#define REP(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define FOR(i, a, b) for (ll i = (a); i < (ll)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())
template <class T>
inline bool chmin(T &a, T b)
{
    if (a > b)
    {
        a = b;
        return true;
    }
    return false;
}
template <class T>
inline bool chmax(T &a, T b)
{
    if (a < b)
    {
        a = b;
        return true;
    }
    return false;
}
template <int MOD>
struct Fp
{
    ll val;
    constexpr Fp(ll v = 0) noexcept : val(v % MOD)
    {
        if (val < 0)
            val += MOD;
    }
    constexpr int getmod() { return MOD; }
    constexpr Fp operator-() const noexcept
    {
        return val ? MOD - val : 0;
    }
    constexpr Fp operator+(const Fp &r) const noexcept { return Fp(*this) += r; }
    constexpr Fp operator-(const Fp &r) const noexcept { return Fp(*this) -= r; }
    constexpr Fp operator*(const Fp &r) const noexcept { return Fp(*this) *= r; }
    constexpr Fp operator/(const Fp &r) const noexcept { return Fp(*this) /= r; }
    constexpr Fp &operator+=(const Fp &r) noexcept
    {
        val += r.val;
        if (val >= MOD)
            val -= MOD;
        return *this;
    }
    constexpr Fp &operator-=(const Fp &r) noexcept
    {
        val -= r.val;
        if (val < 0)
            val += MOD;
        return *this;
    }
    constexpr Fp &operator*=(const Fp &r) noexcept
    {
        val = val * r.val % MOD;
        return *this;
    }
    constexpr Fp &operator/=(const Fp &r) noexcept
    {
        ll a = r.val, b = MOD, u = 1, v = 0;
        while (b)
        {
            ll t = a / b;
            a -= t * b;
            swap(a, b);
            u -= t * v;
            swap(u, v);
        }
        val = val * u % MOD;
        if (val < 0)
            val += MOD;
        return *this;
    }
    constexpr bool operator==(const Fp &r) const noexcept
    {
        return this->val == r.val;
    }
    constexpr bool operator!=(const Fp &r) const noexcept
    {
        return this->val != r.val;
    }
    friend constexpr ostream &operator<<(ostream &os, const Fp<MOD> &x) noexcept
    {
        return os << x.val;
    }
    friend constexpr Fp<MOD> modpow(const Fp<MOD> &a, ll n) noexcept
    {
        if (n == 0)
            return 1;
        auto t = modpow(a, n / 2);
        t = t * t;
        if (n & 1)
            t = t * a;
        return t;
    }
};
constexpr ll MOD = 1e9 + 7;
using mint = Fp<MOD>;

#define pb push_back
#define mp make_pair
#define mt make_tuple

// 負の数にも対応した mod
// 例えば -17 を 5 で割った余りは本当は 3 (-17 ≡ 3 (mod. 5))
// しかし単に -17 % 5 では -2 になってしまう
inline ll mod(ll a, ll m)
{
    return (a % m + m) % m;
}

// 拡張 Euclid の互除法
// ap + bq = gcd(a, b) となる (p, q) を求め、d = gcd(a, b) をリターンします
ll extGcd(ll a, ll b, ll &p, ll &q)
{
    if (b == 0)
    {
        p = 1;
        q = 0;
        return a;
    }
    ll d = extGcd(b, a % b, q, p);
    q -= a / b * p;
    return d;
}

// 中国剰余定理
// m1で割ってb1余り、m2で割ってb2余る数を求めたいとき
// すなわち x ≡ b1 (mod. m1) かつ x ≡ b2 (mod. m2) である xを求めたいとき
// ChineseRem(b1, m1, b2, m2) で ペア(r, m)が戻る。
// 解は x ≡ r (mod. m)
// 解なしの場合は (0, -1)
//
// e.g. 3で割って2余り、5で割って3余る数を求めたいとき
//      すなわち x ≡ 2 (mod. 3) かつ x ≡ 3 (mod. 5) である xを求めたいとき
//      ChineseRem(2, 3, 3, 5) で (8, 15) が戻る。
//      これは、解が x ≡ 8 (mod. 15) であることを意味する
pair<ll, ll> chineseRemSimple(ll b1, ll m1, ll b2, ll m2)
{
    ll p, q;
    ll d = extGcd(m1, m2, p, q); // p is inv of m1/d (mod. m2/d)
    if ((b2 - b1) % d != 0)
        return make_pair(0, -1);
    ll m = m1 * (m2 / d); // lcm of (m1, m2)
    ll tmp = (b2 - b1) / d * p % (m2 / d);
    ll r = mod(b1 + m1 * tmp, m);
    return make_pair(r, m);
}

// 解説通りに実装
ll solve(ll X, ll Y, ll P, ll Q)
{
    ll INF = numeric_limits<ll>::max();
    ll ans = INF;
    FOR(t1, X, X + Y)
    {
        FOR(t2, P, P + Q)
        {
            // 2X + 2Yで割ると余りがt1で、P + Qで割ると余りがt2となる最小の非負整数tを求める
            auto [r, m] = chineseRemSimple(t1, 2 * X + 2 * Y, t2, P + Q);
            if (r != 0)
            {
                chmin(ans, r);
            }
        }
    }

    if (ans == INF)
    {
        return -1;
    }
    else
    {
        return ans;
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    REP(t, T)
    {
        ll X, Y, P, Q;
        cin >> X >> Y >> P >> Q;
        auto ans = solve(X, Y, P, Q);
        if (ans == -1)
        {
            cout << "infinity" << endl;
        }
        else
        {
            cout << ans << endl;
        }
    }

    return 0;
}
