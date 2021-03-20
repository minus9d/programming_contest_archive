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

vector<ll> solve_slow(
    int N,
    vector<ll>& As,
    vector<ll>& Ts,
    int Q, vector<ll>& Xs) {

    auto ans = Xs;
    REP(n, N) {
        auto a = As[n];
        auto t = Ts[n];

        if (t == 1) {
            REP(q, Q) ans[q] += a;
        }
        // max
        else if (t == 2) {
            REP(q, Q) chmax(ans[q], a);
        }
        // min
        else {
            REP(q, Q) chmin(ans[q], a);
        }
    }
    return ans;
}

vector<ll> solve_fast(
    int N,
    vector<ll>& As,
    vector<ll>& Ts,
    int Q, vector<ll>& Xs) {

    auto Ys = Xs;

    // 数値は [min_value, max_value] にクランプされる
    ll min_value = -1e18;
    ll max_value = 1e18;

    ll offset = 0;
    REP(n, N) {
        auto a = As[n];
        auto t = Ts[n];

        if (t == 1) {
            // 数列の値全体に値を加える代わりに、max操作, min操作の閾値を変える
            offset += a;
        }
        // max操作: クランプの下限が変わる
        else if (t == 2) {
            a -= offset;
            chmax(min_value, a);
            chmax(max_value, a); // このコーナーケースに注意
        }
        // min操作: クランプの上限が変わる
        else {
            a -= offset;
            chmin(min_value, a); // このコーナーケースに注意
            chmin(max_value, a);
        }
    }

    vector<ll> ans(Q);
    REP(q, Q) {
        auto x = Xs[q];
        ans[q] = clamp(x, min_value, max_value) + offset;
    }
    return ans;
}

                      

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // while (1) {
    //     int N = 3;
    //     vector<ll> As(N);
    //     vector<ll> Ts(N);
    //     REP(n, N) As[n] = rand() % 10 - 5;
    //     REP(n, N) Ts[n] = rand() % 3 + 1;
    //     int Q = 3;
    //     vector<ll> Xs(Q);
    //     REP(q, Q) Xs[q] = rand() % 10 - 5;
        
    //     auto gt = solve_slow(N, As, Ts, Q, Xs);
    //     auto ans = solve_fast(N, As, Ts, Q, Xs);
    //     if (gt != ans) {
    //         cout << "As:"; REP(n, N) cout << As[n] << " "; cout << endl;
    //         cout << "Ts:"; REP(n, N) cout << Ts[n] << " "; cout << endl;
    //         cout << "Xs:"; REP(q, Q) cout << Xs[q] << " "; cout << endl;
    //         cout << "gt :"; for(auto e: gt) cout << e << " "; cout << endl;
    //         cout << "ans:"; for(auto e: ans) cout << e << " "; cout << endl;
    //         return 0;
    //     }
    // }

    int N;
    cin >> N;
    vector<ll> As(N);
    vector<ll> Ts(N);
    REP(n, N) {
        cin >> As[n] >> Ts[n];
    }

    int Q; cin >> Q;
    vector<ll> Xs(Q);
    REP(q, Q) {
        ll x; cin >> x;
        Xs[q] = x;
    }
    auto ans = solve_fast(N, As, Ts, Q, Xs);

    REP(q, Q) cout << ans[q] << endl;


    return 0;
}
