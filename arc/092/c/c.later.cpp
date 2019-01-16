// 本番後にAC
//
// 二部マッチングで解いたが、解説PDFによるとgreedyにも解ける

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
        for(auto u: m_G[v]) {
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
    int N;
    cin >> N;
    BipartiteMatching bm(N, N);
    vector<pair<int, int>> reds(N);
    vector<pair<int, int>> blues(N);
    REP(n, N) cin >> reds[n].first >> reds[n].second;
    REP(n, N) cin >> blues[n].first >> blues[n].second;
    REP(n1, N) {
        REP(n2, N) {
            auto& r = reds[n1];
            auto& b = blues[n2];
            if (r.first < b.first && r.second < b.second) {
                bm.add_edge(n1, n2);
            }
        }
    }
    cout << bm.bipartite_matching() << endl;
    return 0;
}
