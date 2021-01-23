// 目jが出る確率をp(j), 地点iでの期待値をf(i)とおく。
// 期待値は f(i) = ○f(0) + ○ の形で表せて、
// f(N)から逆方向に期待値を計算していくと、// 
// 最終的に f(0) = ○f(0) + ○になる。これを解くとf(0)になる

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
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i = 0; i < (ll)(n); ++i)
#define FOR(i,a,b) for(ll i = (a); i < (ll)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())
template<class T> inline bool chmin(T& a, T b) {
    if (a > b) {
        a = b; return true;
    }
    return false;
}
template<class T> inline bool chmax(T& a, T b) {
    if (a < b) {
        a = b; return true;
    }
    return false;
}
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
constexpr ll MOD = 1e9 + 7;
using mint = Fp<MOD>;

#define pb push_back
#define mp make_pair
#define mt make_tuple

struct Exp {
    long double n;
    long double c0;
};

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N, M, K; cin >> N >> M >> K;

    vector<ll> As(K);
    REP(k, K) cin >> As[k];

    set<ll> As_set(ALL(As));

    vector<Exp> exp(N + 1);

    ll cnt = 0;
    Exp sum_of_exp{0, 0};
    for(int i = N; i >= 0; i--) {
        if (i == N) {
            exp[i] = {0, 0};
        }
        else if (As_set.count(i)) {
            exp[i] = {0, 1};
        }
        else {
            Exp e = {1, 0};

            // 最初, tmp = 1.0 / M を計算してから tmp をかけていたら1WA...
            e.n += sum_of_exp.n / M;
            e.c0 += sum_of_exp.c0 / M;

            exp[i] = e;
        }
        // cout << "i " << i << ": (" << exp[i].n << "," << exp[i].c0 << ")" << endl;

        if (cnt == M) {
            // 古いのを捨てる
            sum_of_exp.n -= exp[i + M].n;
            sum_of_exp.c0 -= exp[i + M].c0;
        }
        sum_of_exp.n += exp[i].n;
        sum_of_exp.c0 += exp[i].c0;

        ++cnt;
        chmin(cnt, M);
    }

    // f(0) = o + of(0)
    long double a = (1.0 - exp[0].c0);
    long double b = exp[0].n;
    long double ans = b / a;

    // 
    if (ans < 1 || isinf(ans)) {
        cout << -1 << endl;
    } else {
        cout << fixed << setprecision(10) << ans << endl;
    }

    return 0;
}
