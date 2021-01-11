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

map<ll, ll> cache;

ll solve(ll X, ll Y) {
    if (X >= Y) {
        return X - Y;
    }

    if (cache.count(Y)) return cache[Y];

    // cout << "X, Y = " << X << ", " << Y << endl;

    // assert (X < Y);

    if (Y % 2 == 0) {
        ll ans1 = Y - X;
        ll ans2 = solve(X, Y / 2) + 1;
        cache[Y] = min(ans1, ans2);
        return cache[Y];
    }
    else {
        ll ans1 = solve(X, Y + 1) + 1;
        ll ans2 = solve(X, Y - 1) + 1;
        ll ans3 = Y - X;
        cache[Y] = min(ans1, min(ans2, ans3));
        return cache[Y];
    }
}

ll solve_slow(ll X, ll Y) {
    if (X >= Y) {
        return X - Y;
    }
 
    // X < Y
 
    if (Y % 2 == 0) {
        ll ans1 = Y - X;
        ll ans2 = solve(X, Y / 2) + 1;
        return min(ans1, ans2);
    }
    else {
        ll ans1 = solve(X, Y + 1) + 1;
        ll ans2 = solve(X, Y - 1) + 1;
        ll ans3 = Y - X;
        return min(ans1, min(ans2, ans3));
    }
}


int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // while(1) {
    //     ll x = ((ll)rand() * (ll)rand()) % (ll)1e18 + 1;
    //     ll y = ((ll)rand() * (ll)rand()) % (ll)1e18 + 1;
    //     auto s = solve_slow(x, y);
    //     auto f = solve(x, y);
    //     if (s != f) {
    //         cout << "error: x, y, s, f = " << x << " " << y << " " << s << " " << f << endl;
    //         return 0;
    //     }else{
    //         cout << "ok: x, y, s, f = " << x << " " << y << " " << s << " " << f << endl;
    //     }
    //     cache.clear();
    // }
    // {
    //     FOR(x, 1, 1000) {
    //         FOR(y, 1e18 - 1000, 1e18 + 1) {
    //             auto s = solve_slow(x, y);
    //             auto f = solve(x, y);
    //             if (s != f) {
    //                 cout << "error: x, y, s, f = " << x << " " << y << " " << s << " " << f << endl;
    //                 return 0;
    //             }else{
    //                 cout << "ok: x, y, s, f = " << x << " " << y << " " << s << " " << f << endl;
    //             }
    //             cache.clear();
    //         }
    //     }
    // }

    ll X, Y;
    cin >> X >> Y;

    cout << solve(X, Y) << endl;

    return 0;
}
