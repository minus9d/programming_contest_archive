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
                }
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
    pair<ll,ll> s, e;
    cin >> s.first >> s.second >> e.first >> e.second;
    int N;
    cin >> N;
    vector<tuple<ll,ll,ll>> circles;
    REP(n,N) {
        ll x, y, r;
        cin >> x >> y >> r;
        circles.pb( mt(x,y,r) );
    }
    circles.pb( mt(s.first, s.second, 0) );
    circles.pb( mt(e.first, e.second, 0) );

    // start: N
    // end: N+1
    int size = SIZE(circles);
    Dijkstra<double> dij(size);
    REP(i, size-1) {
        const auto& c1 = circles[i];
        FOR(j, i+1, size) {
            const auto& c2 = circles[j];
            auto len1 = abs(get<0>(c1) - get<0>(c2));
            auto len2 = abs(get<1>(c1) - get<1>(c2));
            double dist = hypot(len1, len2);
            dist -= get<2>(c1) + get<2>(c2);
            dist = max(0.0, dist);
            //cout << "dist:" << dist << endl;
            dij.add_undir_edge(i, j, dist);
        }
    }
    auto shortests = dij.shortest_path(N);

    //for(auto e: shortests) {
    //    cout << e << ",";
    //}
    //cout << endl;

    printf("%.13lf\n", shortests[N + 1]);

    return 0;
}
