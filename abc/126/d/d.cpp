#include <algorithm>
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
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

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

int main(void)
{
    cin.sync_with_stdio(false);
    ll N;
    cin >> N;

    Dijkstra<ll> dij(N);

    REP(n, N-1) {
        ll u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        dij.add_undir_edge(u, v, w);
    }

    auto res = dij.shortest_path(0);
    REP(n, N) {
        cout << ((res[n] % 2) ? 0 : 1) << endl;
    }
    return 0;
}
