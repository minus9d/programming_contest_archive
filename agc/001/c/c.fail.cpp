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

int N, K;
set<pair<int,int>> edges;
vector<set<int>> neighs;
set<int> vs;

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


int get_d(int& d, int& v1, int& v2) {
    if (SIZE(vs) <= 1) return 0;
    int v = *vs.begin();

    Dijkstra<int> dij(N);
    for(auto& e: edges) {
        dij.add_undir_edge(e.first, e.second, 1);
    }
    
    auto res = dij.shortest_path(v);
    int longest = -1;
    int longest_v1 = -1;
    REP(i, SIZE(res)) {
        if (res[i] > longest && res[i] != dij.INF) {
            longest = res[i];
            longest_v1 = i;
        }
    }

    longest = -1;
    int longest_v2 = -1;
    res = dij.shortest_path(longest_v1);
    REP(i, SIZE(res)) {
        if (res[i] > longest && res[i] != dij.INF) {
            longest = res[i];
            longest_v2 = i;
        }
    }



    d = longest;
    v1 = longest_v1;
    v2 = longest_v2;
}

void delete_v_neighs(int v) {

    vector<int> should_be_deleted;

    for (auto v_n : neighs[v]) {
        if (SIZE(neighs[v_n]) == 1) {
            neighs[v_n] == set<int>();
            should_be_deleted.push_back(v_n);
            edges.erase(mp(v_n, v));
            edges.erase(mp(v, v_n));
            vs.erase(v_n);
        }
    }

    for (auto v_d : should_be_deleted) neighs[v].erase(v_d);
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> K;
    neighs.resize(N);
    REP(n,N-1) {
        int a,b;
        cin >> a >> b;
        --a; --b;
        edges.insert(mp(a,b));
        neighs[a].insert(b);
        neighs[b].insert(a);
    }
    REP(n,N) vs.insert(n);


    if (K == 1) {
        cout << (N - 2) << endl;
        return 0;
    }
    
    int ans = 0;
    while (true) {
        int d, v1, v2;
        get_d(d, v1, v2);
        //cout << "longest:" << d << endl;
        if (d <= K) break;

        int v1_n = *neighs[v1].begin();
        int v2_n = *neighs[v2].begin();
        int v_deleted = (SIZE(neighs[v1_n]) < SIZE(neighs[v2_n])) ? v1_n : v2_n;
        ans += SIZE(neighs[v_deleted]) - 1;
        //cerr << v_deleted << "'s neighbors will be deleted" << endl;
        delete_v_neighs(v_deleted);
    }
    cout << ans << endl;

    return 0;
}
