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

int H, W;
int to_idx(int h, int w) {
    return h * W + w;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> H >> W;

    Dijkstra<int> dij(H * W);

    int Ch, Cw;
    cin >> Ch >> Cw;
    --Ch; --Cw;
    int Dh, Dw;
    cin >> Dh >> Dw;
    --Dh; --Dw;

    int dh[4] = {0, 1, 0, -1};
    int dw[4] = {1, 0, -1, 0};

    vector<string> cells(H);
    REP(h, H) cin >> cells[h];

    REP(h, H) {
        REP(w, W) {
            auto v = to_idx(h, w);
            if (cells[h][w] == '#') continue;

            REP(d, 4) {
                int h2 = h + dh[d];
                int w2 = w + dw[d];
                if (h2 < 0 || h2 >= H || w2 < 0 || w2 >= W) continue;
                if (cells[h2][w2] == '.') {
                    auto u = to_idx(h2, w2);
                    dij.add_undir_edge(v, u, 0);
                    // printf("(%d, %d) -> (%d, %d) 0\n", 
                    //        h, w, h2, w2);
                }
            }
            for(int i = -2; i <= 2; ++i) {
                for(int j = -2; j <= 2; ++j) {
                    if (abs(i) + abs(j) <= 1) continue;
                    int h2 = h + i;
                    int w2 = w + j;
                    if (h2 < 0 || h2 >= H || w2 < 0 || w2 >= W) continue;
                    if (cells[h2][w2] == '.') {
                        auto u = to_idx(h2, w2);
                        dij.add_undir_edge(v, u, 1);
                        // printf("(%d, %d) -> (%d, %d) 1\n", 
                        //        h, w, h2, w2);
                    }
                }
            }
        }
    }

    auto s = to_idx(Ch, Cw);
    auto g = to_idx(Dh, Dw);
    auto ret = dij.shortest_path(s);
    if (ret[g] == dij.INF) {
        cout << -1 << endl;
    } else {
        cout << ret[g] << endl;
    }
    return 0;
}
