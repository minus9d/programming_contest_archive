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

// 多重vector
// e.g. auto vec = make_v<ll>(2, 3, 4);
template <typename T>
vector<T> make_v(size_t a) { return vector<T>(a); }
template <typename T, typename... Ts>
auto make_v(size_t a, Ts... ts)
{
    return vector<decltype(make_v<T>(ts...))>(a, make_v<T>(ts...));
}

// 多重vectorのfill その1
// 組み込み型の多重vectorに使う
// e.g. fill_v(vec, 777);
template <typename T, typename V>
typename enable_if<is_class<T>::value == 0>::type
fill_v(T &t, const V &v) { t = v; }
template <typename T, typename V>
typename enable_if<is_class<T>::value != 0>::type
fill_v(T &t, const V &v)
{
    for (auto &e : t)
        fill_v(e, v);
}

// 多重vectorのfill その2
// 非組み込み型の多重vectorに使う
// e.g. fill_v2<mint>(vec, 777);
template <typename T, typename U, typename... V>
typename enable_if<is_same<T, U>::value != 0>::type
fill_v2(U &u, const V... v) { u = U(v...); }
template <typename T, typename U, typename... V>
typename enable_if<is_same<T, U>::value == 0>::type
fill_v2(U &u, const V... v)
{
    for (auto &e : u)
        fill_v2<T>(e, v...);
}

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

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int H, W;
    cin >> H >> W;
    auto cells = make_v<ll>(H, W);
    auto dp = make_v<ll>(H, W);
    auto money = make_v<ll>(H, W);
    fill_v(dp, 1e18);
    REP(h, H) {
        REP(w, W) {
            cin >> cells[h][w];
        }
    }
    vector<ll> P(H + W - 1);
    REP(i, H + W - 1) cin >> P[i];

    int day = 1;
    ll tmp = cells[0][0] - P[day-1];
    chmin(dp[0][0], tmp);
    money[0][0] = tmp;

    // REP(h, H) {
    //     REP(w, W) {
    //         cout << dp[h][w] << " ";
    //     }
    //     cout << endl;
    // }
    

    FOR(day, 2, H + W) {
        auto p = P[day-1];
        REP(h, H) {
            auto w = day - h - 1;
            if (w < 0 or w >= W) continue;

            ll tmp1 = -1e18;
            ll tmp2 = -1e18;
            ll mny1;
            ll mny2;

            auto w2 = w - 1;
            auto h2 = h;
            if (!(w2 < 0 or w2 >= W)) {
                mny1 = money[h2][w2];
                mny1 += cells[h][w];
                mny1 -= p;

                tmp1 = min(mny1, dp[h2][w2]);
            }

            w2 = w;
            h2 = h - 1;
            if (!(h2 < 0 or h2 >= H)) {
                mny2 = money[h2][w2];
                mny2 += cells[h][w];
                mny2 -= p;

                tmp2 = min(mny2, dp[h2][w2]);
            }

            if (tmp1 > tmp2) {
                dp[h][w] = tmp1;
                money[h][w] = mny1;
            } else {
                dp[h][w] = tmp2;
                money[h][w] = mny2;
            }
        }

        // REP(h, H) {
        //     REP(w, W) {
        //         cout << dp[h][w] << " ";
        //     }
        //     cout << endl;
        // }


    }

    if (dp[H-1][W-1] >= 0) {
        cout << 0 << endl;
    } else {
        cout << -dp[H-1][W-1] << endl;
    }

    return 0;
}
