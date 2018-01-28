// 本番中
//   .でつながる領域をunion findで特定
//   各領域につき、市松模様が最適と仮定し、2種類のスコアを出して、良い方のスコアの和をとった
// 上の誤り
//   以下のとき、正解は5だが、4と返してしまう
//       .**.
//       ....
//       .**.
// 本番後
//   解説pdfの通り解く
//   つまり、
//     「グリッドグラフでの最大独立集合のサイズを求めよ」という問題に帰着。//     二部グラフについて、最大独立集合のサイズは (頂点数) - (最大マッチングのサイズ) で求まるのを利用。
//   証明方法不明

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
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

class BipartiteMatching {
public:
    // V1, V2: 左側・右側それぞれの頂点数
    BipartiteMatching(int V1, int V2) : m_V1(V1), m_V2(V2) {
        m_G.resize(m_V1 + m_V2);
        m_match.resize(m_V1 + m_V2, -1);
        m_used.resize(m_V1 + m_V2);
    }
    // 左側の頂点と右側の頂点の間に辺を張る
    void add_edge(int v1, int v2) {
        v2 += m_V1;
        m_G[v1].push_back(v2);
        m_G[v2].push_back(v1);
    }
    // 二部グラフの最大マッチングを求める
    int bipartite_matching() {
        int res = 0;
        fill(ALL(m_match), -1);
        REP(v, m_V1 + m_V2) {
            if (m_match[v] < 0) {
                fill(ALL(m_used), 0);
                if (dfs(v)) ++res;
            }
        }
        return res;
    }
    void debug_print() {
        REP(i, SIZE(m_match)) {
            cout << "v" << i << " ";
            auto m = m_match[i];
            if (m == -1) cout << "has no pair" << endl;
            else cout << "is matched with " << m << endl;
        }
    }
    bool has_matching(int v1, int v2) { return m_match[v1] == m_V1 + v2; }
private:
    bool dfs(int v) {
        m_used[v] = true;
        for (auto u : m_G[v]) {
            int w = m_match[u];
            if (w < 0 || !m_used[w] && dfs(w)) {
                m_match[v] = u;
                m_match[u] = v;
                return true;
            }
        }
        return false;
    }
    int m_V1;
    int m_V2;
    vector<vector<int>> m_G; // グラフの隣接リスト表現
    vector<int> m_match; // マッチングのペア
    vector<char> m_used; // DFSですでに調べたかのフラグ
};

int main(void)
{
    cin.sync_with_stdio(false);
    int R, C;
    cin >> R >> C;
    vector<string> cells(R);
    REP(r, R) {
        cin >> cells[r];
    }

    int v1 = 0;
    int v2 = 0;
    map<pair<int, int>, int> v1map;
    map<pair<int, int>, int> v2map;
    REP(r, R) {
        REP(c, C) {
            if (cells[r][c] == '.') {
                if ((r + c) % 2) { v1map[mp(r, c)] = v1;  ++v1; }
                else { v2map[mp(r, c)] = v2;  ++v2; }
            }
        }
    }
 
    BipartiteMatching bm(SIZE(v1map), SIZE(v2map));

    // エッジがあるか？
    for (auto e1 : v1map) {
        auto c1 = e1.first;
        auto v1 = e1.second;
        for (auto e2 : v2map) {
            auto c2 = e2.first;
            auto v2 = e2.second;
            if (abs(c1.first - c2.first) + abs(c1.second - c2.second) == 1) {
                bm.add_edge(v1, v2);
            }
        }

    }
    auto pair_num = bm.bipartite_matching();
    cout << (SIZE(v1map) + SIZE(v2map) - pair_num) << endl;

    return 0;
}
