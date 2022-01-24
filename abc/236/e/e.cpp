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

bool avg_sub(int N, double k, vector<ll>& As) {
    vector<double> Bs(N);
    REP(n, N) Bs[n] = As[n] - k;
    
    vector<vector<double>> dp(N, vector<double>(2));
    REP(n, N) {
        if (n == 0) {
            dp[n][0] = Bs[n];
        }
        else {
            dp[n][0] = max(dp[n - 1][0], dp[n - 1][1]) + Bs[n];
            dp[n][1] = dp[n - 1][0];
        }
    }

    // cout << "k, dp = " << k << endl;
    // REP(n, N) cout << dp[n][0] << " "; cout << endl;
    // REP(n, N) cout << dp[n][1] << " "; cout << endl;
    // cout << endl;

    return (max(dp[N-1][0], dp[N-1][1]) >= -1e-9);
}

double solve_avg(int N, vector<ll>& As) {

    // auto ret = avg_sub(N, 4, As);
    // cout << ret << endl;
    // return 7.7;

    double mn = 1;
    double mx = 1e9 + 1;
    REP(rep, 100) {
        double k = (mn + mx) / 2;
        // cerr << "k, mn, mx = " << k << "," << mn << "," << mx << endl;
        (avg_sub(N, k, As) ? mn : mx) = k;
    }
    return (mn + mx) / 2;
}

bool median_sub(int N, ll k, vector<ll>& As) {

    // 中央値がk以上 <=> k以上の数(N + 2) // 2以上ある
    vector<vector<int>> dp(N, vector<int>(2));
    REP(n, N) {
        if (n == 0) {
            dp[n][0] = (As[n] >= k) ? 1 : -1;
        }
        else {
            dp[n][0] = max(dp[n - 1][0], dp[n - 1][1]) + ((As[n] >= k) ? 1 : -1);
            dp[n][1] = dp[n - 1][0];
        }
    }

    // cout << "k, dp = " << k << endl;
    // REP(n, N) cout << dp[n][0] << " "; cout << endl;
    // REP(n, N) cout << dp[n][1] << " "; cout << endl;
    // cout << endl;

    // cout << "left:" << max(dp[N-1][0], dp[N-1][1]) << ". right = " << ((N + 2) / 2) << endl;

    return max(dp[N-1][0], dp[N-1][1]) >= 1;
}

double solve_median(int N, vector<ll>& As) {
    set<ll> set_a(ALL(As));
    vector<ll> vec_a(ALL(set_a));
    auto mn_a = *min_element(ALL(As));
    auto mx_a = *max_element(ALL(As));

    if (median_sub(N, mx_a, As)) {
        return mx_a;
    }

    int lo_idx = 0;
    int hi_idx = SIZE(vec_a) - 1;

    while (hi_idx - lo_idx > 1) {
        ll k_idx = (lo_idx + hi_idx) / 2;
        (median_sub(N, vec_a[k_idx], As) ? lo_idx : hi_idx) = k_idx;
    }

    // cout << "ok. lo, hi = " << lo_idx << "," << hi_idx << endl;

    return vec_a[lo_idx];
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    vector<ll> As(N);
    REP(n, N) cin >> As[n];

    auto avg = solve_avg(N, As);
    cout << fixed << setprecision(10) << avg << endl;

    auto median = solve_median(N, As);
    std::cout << std::defaultfloat;
    cout << median << endl;

    return 0;
}
