// 注意：Stack Overflowする可能性が高い。g++の場合以下のようにすること
// g++ -Wl,-stack,1000000000 c.s.later.cpp

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>
#include <complex>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

class FordFulkerson {

private:
    // 行き先、容量、逆辺
    struct edge { int to, cap, rev; };
    const int INF = 1e9;
    vector<vector<edge> > G;
    vector<char> used;

public:

    FordFulkerson(int V){
        G.resize(V);
        used.resize(V);
    }

    void add_uni_edge(int from, int to, int cap) {
        // revには、逆辺の容量をすぐに得るためのインデックスを記録
        G[from].push_back( edge{ to, cap, SIZE(G[to])});
        G[to].push_back( edge{from, 0, SIZE(G[from]) - 1});
    }

    // 未テスト
    void add_bi_edge(int v1, int v2, int cap) {
        add_uni_edge(v1, v2, cap);
        add_uni_edge(v2, v1, cap);
    }

    int max_flow(int s, int t) {
        int flow = 0;
        while (true) {
            fill(ALL(used), 0);
            int f = dfs(s, t, INF);
            if (f == 0) return flow;
            flow += f;
        }
    }

    void debug_print() {
        REP(from, SIZE(G)){
            cout << "from " << from << ": " << endl;
            for (auto e : G[from]) {
                printf(" -> %d, capacity(%d), rev(%d)\n", e.to, e.cap, G[e.to][e.rev].cap);
            }
            cout << endl;
        }
    }

private:
    // fは、頂点vの時点でわかっている可能な最大流の大きさ??
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        used[v] = true;

        // v番目の頂点が持つ辺でループ
        REP(i, SIZE(G[v])){
            edge &e = G[v][i];
            // まだ辺eに余裕がある場合
            if (!used[e.to] && e.cap > 0) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

};

struct Bldg {
    int x0;
    int y0;
    int x1;
    int y1;
};

int getIdx(int h, int w, int W, bool isIn) {
    return 2 * (h * W + w) + (!isIn);
}

// Maximum Flowを実装
// 各頂点および各エッジは容量1
void solve(void)
{
    int W, H, B;
    cin >> W >> H >> B;

    vector<Bldg> Bldgs(B);
    
    REP(b,B) {
        cin >> Bldgs[b].x0
            >> Bldgs[b].y0
            >> Bldgs[b].x1
            >> Bldgs[b].y1;
    }
    
    // ビルを1で表す
    vector<vector<int>> cells(H, vector<int>(W));
    for(auto& b : Bldgs) {
        int x0 = b.x0;
        int y0 = b.y0;
        int x1 = b.x1;
        int y1 = b.y1;
        FOR(y, y0, y1+1) {
            FOR(x, x0, x1+1) {
                cells[y][x] = 1;
            }
        }
    }

    FordFulkerson ff(W*H*2+2); // 頂点を2つに分離。 0をin, 1をoutとする
    REP(h,H) {
        REP(w,W) {
            if (w != 0) {
                if (cells[h][w] + cells[h][w-1] == 0) {
                    ff.add_uni_edge(getIdx(h, w, W, 0), getIdx(h, w-1, W, 1), 1);
                    ff.add_uni_edge(getIdx(h, w-1, W, 0), getIdx(h, w, W, 1), 1);
                }
            }
            if (h != 0) {
                if (cells[h][w] + cells[h-1][w] == 0) {
                    ff.add_uni_edge(getIdx(h, w, W, 0), getIdx(h-1, w, W, 1), 1);
                    ff.add_uni_edge(getIdx(h-1, w, W, 0), getIdx(h, w, W, 1), 1);
                }
            }

			// 分離した二つの頂点を結ぶ辺
            ff.add_bi_edge(getIdx(h, w, W, 0), getIdx(h, w, W, 1), 1);
        }
    }

    int sourceIdx = W * H * 2;
    int sinkIdx = sourceIdx + 1;
    REP(w,W) {
		if (cells[0][w] == 0) ff.add_uni_edge(sourceIdx, getIdx(0, w, W, 1), 1);
		if (cells[H-1][w] == 0) ff.add_uni_edge(getIdx(H - 1, w, W, 0), sinkIdx, 1);
    }

	auto flow = ff.max_flow(sourceIdx, sinkIdx);

	cout << flow;
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": ";
        solve();
        cout << endl;
    }

    return 0;
}
