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
class WarshallFloyd {
private:
    int m_V;                   
    vector<vector<T>> m_d;
    
public:
    const T INF = std::numeric_limits<T>::max();
    WarshallFloyd(int V)
        : m_V(V) {

        // 辺のコストを初期化
        // 辺が存在しないときはINFとする
        m_d.resize(m_V, vector<T>(m_V, INF));
        REP(i,V) m_d[i][i] = 0;
    }
    void add_dir_edge(int from, int to, T cost) {
        m_d[from][to] = cost;
    }
    void add_undir_twoways(int v1, int v2, T cost) {
        add_dir_edge(v1, v2, cost);
        add_dir_edge(v2, v1, cost);
    }
    // 全点間の最短距離を求める
    vector<vector<T>> shortest_path() {
        REP(k, m_V) REP(i, m_V) REP(j, m_V) 
            // 辺が存在するときのみ短縮できる 
           if(m_d[i][k] != INF && m_d[k][j] != INF)
                m_d[i][j] = min(m_d[i][j], m_d[i][k] + m_d[k][j]);
        return m_d;
    }
    // shortest_pathを呼んだあとに呼ぶこと
    bool has_negative_loop() {
        REP(i, m_V) {
            if (m_d[i][i] < 0) return true;
        }
        return false;
    }
};


int H, W;

int to_idx(int h, int w) {
    return h * W + w;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> H >> W;
    
    vector<string> cells(H);
    REP(h, H) cin >> cells[h];

    WarshallFloyd<int> wf(H * W);

    REP(h, H) {
        REP(w, W - 1) {
            if (cells[h][w] == '.' && cells[h][w+1] == '.') {
                wf.add_undir_twoways(to_idx(h, w), to_idx(h, w+1), 1);
            }
        }
    }
    REP(w, W) {
        REP(h, H - 1) {
            if (cells[h][w] == '.' && cells[h+1][w] == '.') {
                wf.add_undir_twoways(to_idx(h, w), to_idx(h+1, w), 1);
            }
        }
    }
    auto res = wf.shortest_path();

    int ans = -1;
    for(auto x: res) {
        for(auto y: x) {
            if (y == wf.INF) continue;
            ans = max(ans, y);
            // cerr << y << endl;
        }
    }
    cout << ans << endl;

    return 0;
}
