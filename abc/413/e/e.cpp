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

bool is_first_larger(vector<int>& P, int len, int first_start, int second_start) {
    REP(i, len) {
        int v1 = P[first_start + i];
        int v2 = P[second_start + i];
        if (v1 < v2) return false;
        if (v1 > v2) return true;
    }
    return false;
}

void swap_arr(vector<int>& P, int len, int first_start, int second_start) {
    REP(i, len) {
        swap(P[first_start + i], P[second_start + i]);
    }
}


int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    REP(test, T) {
        int N; cin >> N;
        vector<int> P(1 << N);
        REP(n, (1 << N)) {
            int p; cin >> p;
            P[n] = p;
        }

        // // debug print
        // REP(n, (1 << N)) cout << P[n] << " ";
        // cout << endl;

        int len = 1;
        
        while(len < (1 << N)) {

            int first_start = 0;
            int second_start = len;
            while(first_start < (1 << N)) {
                if (is_first_larger(P, len, first_start, second_start)) {
                    swap_arr(P, len, first_start, second_start);
                }
                first_start += len * 2;
                second_start += len * 2;
            }
            len *= 2;
        }

        // ans
        REP(n, (1 << N)) {
            cout << (n == 0 ? "" : " ") << P[n];
        }
        cout << endl;
    }

    return 0;
}
