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
// class UnionFind
// {
// public:
//     UnionFind(){};
//     ~UnionFind(){};
//     void init(int num_entries) {
//         num_entries_ = num_entries;
//         par_.resize(num_entries_);
//         rank_.resize(num_entries_, 0);
//         REP(i, num_entries_) par_[i] = i;
//     }
//     int find(int x) {
//         if (par_[x] == x) return x;
//         else return par_[x] = find(par_[x]);
//     }
//     void unite(int x, int y) {
//         x = find(x); y = find(y);
//         if (x == y) return;
//         if (rank_[x] < rank_[y]) par_[x] = y;
//         else {
//             par_[y] = x;
//             if (rank_[x] == rank_[y]) rank_[x]++;
//         }
//     }
//     bool same(int x, int y) { return find(x) == find(y); }
// private:
//     int num_entries_;
//     std::vector<int> par_;
//     std::vector<int> rank_;
// };

int to_idx(int h, int w, int W) {
    return h * W + w;
}

vector<vector<char>> can_go(vector<string>& cells) {
    int H = SIZE(cells);
    int W = SIZE(cells[0]);

    // (x, y) = (0, y1)から(x, y) = (W - 1, y2)にいける場合1,
    // いけない場合0であるようなマトリックス
    vector<vector<char>> ret(H, vector<char>(H));

    Dijkstra<int> dij(H * W);
    REP(h, H) {
        REP(w, W) {
            if (w != W - 1) {
                if (cells[h][w] == '.' && cells[h][w + 1] == '.') {
                    dij.add_dir_edge(to_idx(h, w, W), to_idx(h, w + 1, W), 1);
                }
            }
            if (h != H - 1) {
                if (cells[h][w] == '.' && cells[h + 1][w] == '.') {
                    dij.add_dir_edge(to_idx(h, w, W), to_idx(h + 1, w, W), 1);
                }
            }
        }
    }
    REP(y1, H) {
        auto paths = dij.shortest_path(to_idx(y1, 0, W));
        REP(y2, H) {
            ret[y1][y2] = (paths[to_idx(y2, W - 1, W)] == dij.INF) ? 0 : 1;
        }
    }

    // cout << "debug" << endl;
    // REP(h1, H) {
    //     REP(h2, H) {
    //         cout << (int)ret[h1][h2] << " " ;
    //     }
    //     cout << endl;
    // }

    return ret;
}


int main(void)
{
    cin.sync_with_stdio(false);
    int H, W;
    cin >> H >> W;

    vector<string> cells(H);
    REP(h, H) cin >> cells[h];
    auto ret = can_go(cells);

    REP(h, H) {
        if (ret[0][h] && ret[h][h] && ret[h][H - 1]) {
            cout << "Yay!" << endl;
            return 0;
        }
    }

    cout << ":(" << endl;
    return 0;
}
