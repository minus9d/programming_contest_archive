// 本番提出コード
// 両側から探索するように変更。
// 実装合っているかは怪しい

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

int solve_slow(int N, int M, vector<int>& C, vector<pair<int, int>>& UV) {
    if (C[0] == C[N-1]) return -1;

    vector<vector<int>> edges(N);
    for(auto [u, v]: UV) {
        edges[u].pb(v);
        edges[v].pb(u);
    }

    // u, v, turn
    deque<tuple<int, int, int>> st;
    st.push_back({0, N-1, 0});

    set<pair<int, int>> seen;
    seen.insert({0, N-1});

    while(!st.empty()) {
        auto [u, v, turn] = st.front();
        st.pop_front();

        // wrong?
        // if (turn > N) return -1;

        if (u == N - 1 && v == 0) return turn;

        for(auto u2: edges[u]) {
            for(auto v2: edges[v]) {
                if (C[u2] != C[v2] && !seen.count({u2, v2})) {
                    st.push_back({u2, v2, turn + 1});
                    seen.insert({u2, v2});
                }
            }
        }
    }
    return -1;
}

int solve_fast(int N, int M, vector<int>& C, vector<pair<int, int>>& UV) {

    if (C[0] == C[N-1]) return -1;

    vector<vector<int>> edges(N);
    for(auto [u, v]: UV) {
        edges[u].pb(v);
        edges[v].pb(u);
    }

    // u, v, turn
    deque<tuple<int, int, int>> st;
    st.push_back({0, N-1, 0});

    map<pair<int, int>, int> seen;
    seen[{0, N-1}] = 0;

    int ans = 1e9;
    while(!st.empty()) {
        auto [u, v, turn] = st.front();
        st.pop_front();

        for(auto u2: edges[u]) {
            for(auto v2: edges[v]) {
                if (C[u2] == C[v2]) continue;

                if (u == N - 1 && v == 0) {
                    chmin(ans, turn);
                }

                // 逆順から辿って来れる？
                if (seen.count({v2, u2})) {
                    // cout << "gyaku atta." << endl;
                    // cout << "u, v, u2, v2 = " << u << "," << v << "," << u2 << "," << v2 << endl;
                    // cout << "turn, seen[] = " << turn << "," << seen[{v2, u2}] << endl;

                    chmin(ans, seen[{v2, u2}] + turn + 1);
                }

                else if (!seen.count({u2, v2})) {
                    st.push_back({u2, v2, turn + 1});
                    seen[{u2, v2}] = turn + 1;
                }
            }
        }
    }
    if (ans == 1e9) return -1;
    else return ans;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // int ok = 0;
    // while (1) {

    //     // int N = rand() % 4 + 2;
    //     int N = rand() % 7 + 2;

    //     int M_max = N * (N - 1) / 2;
    //     int M = (rand() % M_max) + 1;
    //     vector<int> C(N);
    //     REP(n, N) C[n] = rand() % 2;
    //     vector<pair<int, int>> UV(M);
    //     set<pair<int, int>> seen;
    //     REP(m, M) {
    //         while(1) {
    //             int u = rand() % N;
    //             int v = rand() % N;
    //             if (u == v) continue;
    //             if (!seen.count({u, v})) {
    //                 UV[m] = {u, v};
    //                 seen.insert({u, v});
    //                 seen.insert({v, u});
    //                 break;
    //             }
    //         }
    //     }
    //     auto gt = solve_slow(N, M, C, UV);
    //     auto mine = solve_fast(N, M, C, UV);
    //     if (gt != mine) {
    //         cout << N << " " << M << endl;
    //         for(auto c: C) cout << c << " ";
    //         cout << endl;
    //         REP(m, M) {
    //             cout << (UV[m].first + 1) << " " << (UV[m].second + 1) << endl;
    //         }
    //         cout << endl;

    //         cout << "error: gt = " << gt << ", mine = " << mine << endl;
    //         return 0;
    //     } else {
    //         ++ok;
    //     }
    //     if (ok % 100 == 0) cout << "ok " << ok << endl;
    // }

    int T; cin >> T;
    REP(t, T) {
        int N, M; cin >> N >> M;
        vector<int> C(N);
        REP(n, N) cin >> C[n];
        vector<pair<int, int>> UV(M);
        REP(m, M) {
            int u, v; cin >> u >> v; --u; --v;
            UV[m] = {u, v};
        }
        cout << solve_fast(N, M, C, UV) << endl;
    }
    return 0;
}
