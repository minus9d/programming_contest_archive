// 解法：状態を持つノードを複数のノードに分けて新たなグラフを作る
// 参考: http://puru.hatenablog.com/entry/2016/09/12/201439

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
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
    void add_undir_edge(int a, int b, int cost) {
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


struct Rail {
    int p;
    int q;
    int c;
};
map<pair<int,int>, int> table;
int idx = 0;

void make_table(int node, int c) {
    if (!table.count(mp(node, c))) {
        table[mp(node, c)] = idx++;
    }
}

int to_idx(int node, int c) {
    return table[mp(node,c)];
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;

    // 入力を全部受けて、pair(頂点番号,路線) -> int というテーブルを作る
    vector<Rail> rails;
    REP(m,M) {
        int p,q,c;
        cin >> p >> q >> c;
        --p; --q;
        rails.pb( Rail{p,q,c} );

        make_table(p, 0);
        make_table(q, 0);
        make_table(p, c);
        make_table(q, c);
    }

    // 始点、終点に繋がる路線が一つも存在しないとtableにインデックスが存在しないままなので
    // 強制的にインデックスを作る
    // (例えば終点に繋がる路線が一つもない場合、
    // to_idx(N-1, 0)が0を返してしまうため, 最後の距離計算で間違える)
    // 路線が一つもない場合のコーナーケースもこれで回避できる
    make_table(0, 0);
    make_table(N-1, 0);

    Dijkstra<int> dij(idx);

    // 解説のように頂点を状態で分けていく
    for(auto& r: rails) {
        dij.add_undir_edge(to_idx(r.p, r.c), to_idx(r.q, r.c), 0);
        dij.add_dir_edge(to_idx(r.p, r.c), to_idx(r.p, 0), 0);
        dij.add_dir_edge(to_idx(r.q, r.c), to_idx(r.q, 0), 0);
        dij.add_dir_edge(to_idx(r.p, 0), to_idx(r.p, r.c), 1);
        dij.add_dir_edge(to_idx(r.q, 0), to_idx(r.q, r.c), 1);
    }

    auto res = dij.shortest_path(to_idx(0, 0));
    auto cand = res[to_idx(N-1, 0)];
    cout << ((cand == dij.INF) ? -1 : cand) << endl;

    return 0;
}
