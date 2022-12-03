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


// 頂点は0-originとする
template <typename T>
class BellmanFord {
    struct edge {
        int from;
        int to;
        T cost;
    };

public:
    const T INF = std::numeric_limits<T>::max();
    const T NINF = std::numeric_limits<T>::min();
    BellmanFord(int V)
        : m_V(V) {
        m_es.clear();
    }

    void add_dir_edge(int from, int to, T cost) {
        m_es.push_back( edge{from, to, cost} );
    }

    void add_undir_twoways(int v1, int v2, T cost) {
        add_dir_edge(v1, v2, cost);
        add_dir_edge(v2, v1, cost);
    }

    // 頂点sから各頂点までの距離を計算してdに格納 負の閉路も検出する
    vector<T> shortest_path(int s)
    {
        // INF: その頂点には到達できない
        // NINF: 負の経路があり、sからの最短距離は-∞
        // INF以外: sからの最短距離
        vector<T> d(m_V, INF);
        vector<char> has_negative_loop(m_V);
        d[s] = 0;
        REP(try_num, m_V) {
            bool update = false;
            REP(i, SIZE(m_es)) {
                edge e = m_es[i];
                if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    update = true;

                    // 無限ループ発見
                    if (try_num == m_V - 1) {
                        has_negative_loop[e.to] = 1;
                    }
                }
            }
            if (!update) break;
        }

        // cout << "dists:" << endl;
        // for (auto e: d) cout << e << " ";
        // cout << endl;
        // cout << "negative loop:" << endl;
        // for (auto e: has_negative_loop) cout << int(e) << " ";
        // cout << endl;

        // sからたどり着くまでにnegative loopが存在するような頂点に関して、
        // その最短路をNINFに書き換える
        REP(i, m_V) {
            if (has_negative_loop[i]) d[i] = NINF;
        }

        return d;
    }

    // sから各頂点までの最短路に閉路があるかを返す
    bool find_negative_loop_from_v(int s) {
        vector<T> d(m_V, INF);
        
        d[s] = 0;
        // ループの実行は高々|V|-1回のはず
        // ループの実行回数が|V|よりも大きければ閉路があったとみなす
        int count = 0;
        while (true) {
            bool update = false;
            REP(i, SIZE(m_es)) {
                edge e = m_es[i];
                if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    update = true;
                }
            }
            if (!update) break;

            ++count;
            if (count > m_V) return true;
        }

        return false;
    }

    // グラフ全体のどこかに負の経路があることを検出
    bool find_negative_loop_somewhere(void) {
        vector<T> d(m_V);

        REP(i, SIZE(d)) {
            REP(j, SIZE(m_es)) {
                edge e = m_es[j];
                if (d[e.to] > d[e.from] + e.cost){
                    d[e.to] = d[e.from] + e.cost;
                    // n回目にも更新があるなら負の経路が存在する
                    if (i == SIZE(d) - 1) {
                        return true;
                    }
                }
            }

            // for(int i = 0; i < SIZE(d); ++i) {
            //     cout << d[i] << ", ";
            // }
            // cout << endl;
        }
        return false;
    }

private:
    int m_V;                   
    vector<edge> m_es;
};


class UnionFind
{
public:
    UnionFind(int num_entries)
    {
        num_entries_ = num_entries;
        par_.resize(num_entries_);
        rank_.resize(num_entries_, 0);
        member_num_.resize(num_entries_, 1);
        edge_num_.resize(num_entries, 0);
        REP(i, num_entries_)
        {
            par_[i] = i;
        }
    }
    ~UnionFind(){};
    int find(int x)
    {
        if (par_[x] == x)
            return x;
        else
            return par_[x] = find(par_[x]);
    }
    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
        {
            edge_num_[x]++;
            return;
        }
        if (rank_[x] < rank_[y])
        {
            par_[x] = y;
            member_num_[y] += member_num_[x];
            member_num_[x] = 0;
            edge_num_[y] += edge_num_[x] + 1;
        }
        else
        {
            par_[y] = x;
            member_num_[x] += member_num_[y];
            member_num_[y] = 0;
            edge_num_[x] += edge_num_[y] + 1;
            if (rank_[x] == rank_[y])
                rank_[x]++;
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int vertex_size(int x)
    {
        return member_num_[this->find(x)];
    }
    int edge_size(int x)
    {
        return edge_num_[this->find(x)];
    }

private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
    std::vector<int> member_num_;
    std::vector<int> edge_num_;
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

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, Q;
    cin >> N >> M >> Q;

    UnionFind uf(N);
    BellmanFord<ll> bf(N);
    Dijkstra<ll> dij(N);

    std::vector<std::pair<std::pair<int,int>,long long>> E;
    
    REP(m, M) {
        ll a, b, c; cin >> a >> b >> c;
        --a; --b;

        // 正負を入れ替える
        bf.add_dir_edge(a, b, -c);
        bf.add_dir_edge(b, a, c);
        dij.add_dir_edge(a, b, -c);
        dij.add_dir_edge(b, a, c);
        uf.unite(a, b);
    }


    // -1: 負のループがあることを確認済
    // 1: 負のループがないことを確認済
    map<int, int> has_neg_loop;

    REP(q, Q) {
        ll x, y; cin >> x >> y;
        --x; --y;

        if (!uf.same(x, y)) {
            cout << "nan" << endl;
        }
        else {
            auto id = uf.find(x);
            if (has_neg_loop.count(id)) {
                // 負のループの検出が終わっている
                auto loop_res = has_neg_loop[id];
                if (loop_res == -1) {
                    cout << "inf" << endl;
                } else {
                    // // 普通にダイクストラで
                    // auto res = dij.shortest_path(x);
                    // cout << -res[y] << endl;

                    // for debug
                    cout << 777 << endl;
                }
            }
            else {
                // 負のループ検出する
                auto res = bf.shortest_path(x);
                if (res[y] == bf.NINF) {
                    // 負のループある
                    has_neg_loop[id] = -1;
                    cout << "inf" << endl;
                } else {
                    // 負のループない
                    has_neg_loop[id] = 1;
                    cout << -res[y] << endl;
                }
            }
        }
    }

    return 0;
}
