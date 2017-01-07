#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>


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

set<pair<int,int>> used_edge;

template <typename T>
class Dijkstra {
    struct edge { int to; T cost; };
    typedef pair<T, int> P; // <最短距離, 頂点番号>

public:
    T INF;

    Dijkstra(int V) 
        : INF(std::numeric_limits<T>::max())
        , m_V(V)
        {
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
        vector<T> d(m_V, INF);
        vector<pair<int,int>> last_edge(m_V);

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
                    last_edge[e.to] = mp(v, e.to);
                }
            }
        }

        for (auto edge : last_edge) {
            int v1 = edge.first;
            int v2 = edge.second;
            if (v1 != v2) {
                used_edge.insert(mp(v1,v2));
                used_edge.insert(mp(v2,v1));
            }
        }

        return d;
    }

private:
    int m_V;
    vector<vector<edge> > m_G;
};

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;

    Dijkstra<int> dij(N);
    REP(m,M) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        dij.add_undir_edge(a, b, c);
    }
    REP(n,N) {
        auto res = dij.shortest_path(n);
    }
    cout << (M - (SIZE(used_edge) / 2)) << endl;

    return 0;
}
