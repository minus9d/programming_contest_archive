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

int solve_slow(int N, int M, vector<int> As) {
    vector<int> pile(N);
    REP(m, M) {
        auto a = As[m];
        pile[a]++;
    }

    int mex = N;
    REP(i, N) {
        if (pile[i] == 0) {
            mex = i;
            break;
        }
    }

    int i = 0;
    int ans = mex;
    while(true) {
        int j = i + M;
        if (j >= N) break;

        auto ai = As[i];
        pile[ai]--;
        auto aj = As[j];
        pile[aj]++;

        int tmp_mex = -1;
        REP(k, N) {
            if (pile[k] == 0) {
                tmp_mex = k;
                break;
            }
        }
        
        chmin(ans, tmp_mex);
        ++i;
    }
    return ans;
}
int solve_fast(int N, int M, vector<int> As) {
    vector<int> pile(N);
    REP(m, M) {
        auto a = As[m];
        pile[a]++;
    }

    int mex = N;
    REP(i, N) {
        if (pile[i] == 0) {
            mex = i;
            break;
        }
    }
    // cerr << "mex = " << mex << endl;

    int i = 0;
    int ans = mex;
    while(true) {
        int j = i + M;
        if (j >= N) break;

        auto ai = As[i];
        pile[ai]--;
        auto aj = As[j];
        pile[aj]++;

        if (pile[ai] == 0) {
            if (ai < mex) {
                mex = ai;
            }
        }
        if (pile[aj] == 1) {
            if (mex == aj) {
                mex++;
            }
        }
        chmin(ans, mex);
        ++i;
    }
    return ans;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;
    vector<int> As(N);

    // while(1){
    //     int N = rand() % 10 + 1;
    //     int M = (rand() % N) + 1;
    //     vector<int> As(N);
    //     REP(n, N) As[n] = rand() % N;

    //     cout << endl;
    //     cout << N << " " << M << endl;
    //     for(auto a: As) cout << a << " ";
    //     cout << endl;

    //     auto gt = solve_slow(N, M, As);
    //     cout << "gt = " << gt << endl;

    //     auto mine = solve_fast(N, M, As);
    //     cout << "mine = " << mine << endl;

    //     if (gt != mine) {
    //         cout << N << " " << M << endl;
    //         for(auto a: As) cout << a << " ";
    //         cout << endl;
    //         cout << "gt = " << gt << ", mine = " << mine << endl;
    //         return 0;
    //     } else {
    //         cout << "ok.." << endl;
    //     }
    // }

    REP(n, N) {
        cin >> As[n];
    }
    cout << solve_fast(N, M, As) << endl;

    return 0;
}
