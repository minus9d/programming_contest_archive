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
#include <climits>

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

const int INF = INT_MAX;

// 頂点は0-originとする
class Dijkstra {

    struct edge { int to, cost; };
    typedef pair<int, int> P; // <最短距離, 頂点番号>

public:
    Dijkstra(int V) {
        m_V = V;
        m_G.resize(m_V);
    }

    // a -> bに片方向のエッジを張る
    void add_dir_edge(int a, int b, int cost) {
        m_G[a].push_back( edge{ b, cost } );
    }

    // a <-> bに両方向のエッジを張る
    void add_undir_edge(int a, int b, int cost) {
        add_dir_edge(a, b, cost);
        add_dir_edge(b, a, cost);
    }

    // 頂点sから各頂点までの距離を計算して返す
    vector<int> shortest_path(int s) {
        vector<int> d(m_V, INF);
        priority_queue<P, vector<P>, greater<P> > que;
        d[s] = 0;
        que.push(P(0, s));
    
        while(!que.empty()) {
            P p = que.top();
            que.pop();

            int dist = p.first;
            int v = p.second;
            if (d[v] < dist) continue;
            REP(i, m_G[v].size()) {
                edge e = m_G[v][i];
                if (d[e.to] > d[v] + e.cost) {
                    d[e.to] = d[v] + e.cost;
                    que.push(P(d[e.to], e.to));
                }
            }
        }

        return move(d);
    }

private:
    int m_V;
    vector<vector<edge> > m_G;
};


class BellmanFord {
    struct edge { int from, to, cost; };
    
public:
    BellmanFord(int V) {
        m_V = V;
        m_es.clear();
    }

    void add_dir_edge(int from, int to, int cost) {
        m_es.push_back( edge{from, to, cost} );
    }

    void add_undir_twoways(int v1, int v2, int cost) {
        add_dir_edge(v1, v2, cost);
        add_dir_edge(v2, v1, cost);
    }

    // 頂点sから各頂点までの距離を計算してdに格納
    vector<int> shortest_path(int s)
    {
        vector<int> d(m_V, INT_MAX);
        
        d[s] = 0;
        while (true) {
            bool update = false;
            REP(i, SIZE(m_es)) {
                edge e = m_es[i];
                if (d[e.from] != INT_MAX && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    update = true;
                }
            }
            if (!update) break;
        }

        return move(d);
    }

    // グラフ全体のどこかに負の経路があることを検出
    bool find_negative_loop(void) {
        vector<int> d(m_V);

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


int main(){
    int V, E, r;
    cin >> V >> E >> r;

    BellmanFord bf(V);

    REP(e,E) {
        int v1, v2, cost;
        cin >> v1 >> v2 >> cost;
        bf.add_dir_edge(v1, v2, cost);
    }

    if (bf.find_negative_loop()) {
        cout << "NEGATIVE CYCLE" << endl;
    }
    else {
        auto distances = bf.shortest_path(r);
        for(auto d : distances) {
            if (d == INT_MAX) cout << "INF" << endl;
            else cout << d << endl;
        }
        
    }


    return 0;
}

