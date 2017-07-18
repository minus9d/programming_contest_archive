#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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

// 頂点は0-originとする
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
    vector<T> shortest_path(int s, vector<int>& prev_path) {
        vector<T> d(m_V, INF);
        prev_path.resize(m_V, -1);
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
                    prev_path[e.to] = v;
                }
            }
        }
        return d;
    }

private:
    int m_V;
    vector<vector<edge> > m_G;
};

vector<int> get_path(int t, vector<int>& prev)
{
    vector<int> path;
    for(; t != -1; t = prev[t]) path.push_back(t);
    reverse(ALL(path));
    return path;
}

int N;
vector<vector<int>> edges;
vector<int> bw;

vector<int> seen;
void dfs(int v) {
    seen[v] = 1;
    for(auto v2: edges[v]) {
        auto color = bw[v];
        if (seen[v2] == 0) {
            if (bw[v2] == 0) {
                bw[v2] = color;
            }
            seen[v2] = 1;
            dfs(v2);
        }
    }
}

    

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N;

    Dijkstra<int> dij(N);
    edges.resize(N);
    REP(n, N-1) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        dij.add_undir_edge(a, b, 1);
        edges[a].pb(b);
        edges[b].pb(a);
    }
    vector<int> prev_path;
    auto dummy = dij.shortest_path(0, prev_path);
    auto path = get_path(N-1, prev_path);
    //for(auto e: path) {
    //    cout << e << ",";
    //}
    //cout << endl;

    // -1: black  1: white 
    bw.resize(N);
    bw[0] = -1;
    bw[N-1] = 1;
    auto num = SIZE(path) - 2;
    if (num > 0) {
        auto n1 = (num + 1) / 2;
        auto n2 = num - n1;
        REP(i, n1) {
            bw[path[i+1]] = -1;
        }
        REP(i, n2) {
            bw[path[i+1+n1]] = 1;
        }
    }

	seen.resize(N);
    dfs(0);

    //cout << "bw:" << endl;
    //for(auto e: bw) cout << e << ",";
    //cout << endl;
    //cout << endl;

    int b_num = 0;
    int w_num = 0;
    for(auto e: bw) {
        if (e == -1) ++b_num;
        else if (e == 1) ++w_num;
    }


    assert(b_num + w_num == N);
    if (b_num > w_num) {
        cout << "Fennec" << endl;
    } else {
        cout << "Snuke" << endl;
    }

    return 0;
}
