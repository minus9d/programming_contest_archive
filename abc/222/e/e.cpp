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
#include <random>
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
constexpr ll MOD = 998244353;
using mint = Fp<MOD>;

#define pb push_back
#define mp make_pair
#define mt make_tuple

template <typename T>
class CumSum1D
{
public:
    CumSum1D(){};
    ~CumSum1D(){};
    void init(vector<T>& arr) {
        m_cum = arr;
        m_N = arr.size();
        FOR(i, 1, m_N) m_cum[i] += m_cum[i - 1];
    }
    // get sum of [l, r]. 0-based.
    T getSum(int l, int r) const {
        T ret = m_cum[r];
        if (l != 0) ret -= m_cum[l - 1];
        return ret;
    }
private:
    size_t m_N;
    vector<T> m_cum;
};

// 頂点は0-originとする
template <typename T>
class Dijkstra {
    struct edge { int to; T cost; };
    typedef pair<T, int> P; // <最短距離, 頂点番号>

private:
    int m_V;
    vector<vector<edge> > m_G;
public:
    const T INF = std::numeric_limits<T>::max();
    vector<int> m_prev_path; // 最短パスを辿るため

    Dijkstra(int V) : m_V(V) {
        m_G.resize(m_V);
    }

    // a -> bに片方向のエッジを張る
    void add_dir_edge(int a, int b, T cost) {
        m_G[a].push_back( edge{ b, cost } );
    }

    // a <-> bに両方向のエッジを張る
    void add_undir_edge(int a, int b, T cost) {
        add_dir_edge(a, b, cost);
        add_dir_edge(b, a, cost);
    }

    // 頂点sから各頂点までの距離を計算して返す
    vector<T> shortest_path(int s) {
        m_prev_path.clear(); m_prev_path.resize(m_V, -1);

        vector<T> d(m_V, INF);
        priority_queue<P, vector<P>, greater<P> > que;
        d[s] = 0;
        que.push(P(0, s));

        while(!que.empty()) {
            P p = que.top();
            que.pop();

            auto dist = p.first;
            auto v = p.second;
            if (d[v] < dist) continue;
            REP(i, m_G[v].size()) {
                edge e = m_G[v][i];
                if (d[e.to] > d[v] + e.cost) {
                    d[e.to] = d[v] + e.cost;
                    que.push(P(d[e.to], e.to));
                    m_prev_path[e.to] = v;
                }
            }
        }

        return d;
    }

    // shortest_path()が呼ばれた後に呼ばれることを期待する
    // s -> v1 -> v2 -> v3 -> t の場合、{s, v1, v2, v3, t} からなるvectorを返す
    vector<int> get_path(int t)
    {
        vector<int> path;
        for(; t != -1; t = m_prev_path[t]) path.push_back(t);
        reverse(ALL(path));
        return path;
    }
};

using P = pair<int, int>;

ll solve(int N, int M, int K,
         vector<int> As,
         vector<P> UVs) {

    Dijkstra<int> dij(N);
    map<P, int> vertexs2edgeidx;
    REP(n, N - 1) {
        auto [u, v] = UVs[n];
        vertexs2edgeidx[P(u, v)] = n;
        vertexs2edgeidx[P(v, u)] = n;
        dij.add_undir_edge(u, v, 1);
    }

    // 各辺を通る回数
    vector<int> edgecount(N - 1);

    int prev_a = -1;
    REP(m, M) {
        int a = As[m];
        if (m != 0) {
            // prev_aからaまでの経路
            dij.shortest_path(prev_a);
            auto path = dij.get_path(a);
            REP(i, SIZE(path) - 1) {
                auto v1 = path[i];
                auto v2 = path[i + 1];
                auto edgeidx = vertexs2edgeidx[P(v1, v2)];
                edgecount[edgeidx] += 1;
            }
        }
        prev_a = a;
    }
    // for(auto ec: edgecount) cout << ec << " ";
    // cout << endl;

    int countsum = accumulate(ALL(edgecount), 0);
    if ((countsum + K) % 2) {
        return 0;
    }

    // dp
    vector<vector<mint>> dp(2, vector<mint>(100001));
    bool flip = 0;
    dp[flip][0] = 1;
    REP(n, N - 1) {
        flip = !flip;
        fill(ALL(dp[flip]), 0);

        auto cnt = edgecount[n];
        REP(i, 100001) {
            dp[flip][i] += dp[!flip][i];
            if (i + cnt <= 100000) {
                dp[flip][i + cnt] += dp[!flip][i];
            }
        }

        // REP(i, 10) {
        //     cout << dp[flip][i] << " ";
        // }
        // cout << endl;
    }

    int r_num = (countsum + K) / 2;
    int b_num = (countsum - K) / 2;
    if (r_num < 0 || b_num < 0) {
        return 0;
    }

    return dp[flip][r_num].val;
}


int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // std::mt19937 mt(12345);
    // while(1) {
    //     // int N = 1000;
    //     // int M = 100;
    //     // int K = rand() % 100000 - 50000;

    //     int N = 6;
    //     int M = 4;
    //     int K = rand() % 100000 - 50000;
    //     cout << N << " " << M << " " << K << endl;
    //     vector<int> As(M);
    //     REP(m, M) {
    //         As[m] = rand() % N;
    //     }
        
    //     for(auto a: As) cout << a << " ";
    //     cout << endl;
    //     vector<P> UVs;
    //     REP(n, N - 1) {
    //         std::uniform_int_distribution<> myrand(0, n);        // [0, 99] 範囲の一様乱数
    //         int u = n + 1;
    //         int v = myrand(mt);
    //         UVs.pb(P(v, u));
    //         cout << u << " " << v << endl;
    //     }
    //     cout << solve(N, M, K, As, UVs) << endl;
    //     cout << endl;
    // }

    int N, M, K;
    cin >> N >> M >> K;
    vector<int> As(M);
    REP(m, M) {
        cin >> As[m]; As[m]--;
    }

    vector<P> UVs;
    REP(n, N - 1) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        UVs.pb(P(u, v));
    }

    cout << solve(N, M, K, As, UVs) << endl;

    return 0;
}
