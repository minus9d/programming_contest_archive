// 2語からなる論文のタイトルのリストが与えられる。
// このうちfakeな論文のタイトルは、realな論文のタイトルから前半、後半それぞれ1語ずつを拝借して作成されたもの。
// fakeな論文の最大数を求める
//
// largeはContent Analysis通りの方針で解く
//

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
#include <cstring>

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
#define mt make_tuple


// 左側の頂点、右側の頂点の両方を通してindexを付与しているので注意
// 例えば左側の頂点数がV1, 右側の頂点数がV2の場合、
// 左側の頂点は順に0, 1, ..., V1-1
// 右側の頂点は順にV1, V1+1, ..., V1+V2-1
class BipartiteMatching {
public:
    // V: 両側の頂点数の和
    BipartiteMatching(int V) {
        m_V = V;
        m_G.resize(m_V);
        m_match.resize(m_V);
        m_used.resize(m_V);
    }

    // Uの頂点とVの頂点の間に辺を張る
    void add_edge(int u, int v) {
        m_G[u].push_back(v);
        m_G[v].push_back(u);
    }

    // 二部グラフの最大マッチングを求める
    int bipartite_matching() {
        int res = 0;
        fill(ALL(m_match), -1);
        REP(v, m_V) {
            if (m_match[v] < 0) {
                fill(ALL(m_used), 0);
                if (dfs(v)) {
                    ++res;
                }
            }
        }
        return res;
    }

    void debug_print() {
        REP(i, SIZE(m_match)) {
            cout << "v" << i << " ";
            auto m = m_match[i];
            if (m == -1) {
                cout << "has no pair" << endl;
            }
            else {
                cout << "is matched with " << m << endl;
            }
        }
    }

    bool are_pair(int u, int v) {
        return m_match[u] == v;
    }

    int return_pair(int u) {
        return m_match[u];
    }

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

private:
    int m_V; // 両側の頂点数の合計

    vector<vector<int>> m_G; // グラフの隣接リスト表現
    vector<int> m_match; // マッチングのペア
    vector<char> m_used; // DFSですでに調べたかのフラグ
};




void solve() {
    int N;
    cin >> N;

    vector<string> word_vec1;
    vector<string> word_vec2;

    set<string> word_set1;
    set<string> word_set2;

    REP(n, N) {
        string s1, s2;
        cin >> s1 >> s2;
        word_vec1.pb(s1);
        word_vec2.pb(s2);

            //cout << s1 << " " << s2 << endl;

        word_set1.insert(s1);
        word_set2.insert(s2);
    }

    map<string, int> word_to_idx1;
    map<string, int> word_to_idx2;
    int idx = 0;
    for(auto& w: word_set1) {
        word_to_idx1[w] = idx;
        ++idx;
    }
    for(auto& w: word_set2) {
        word_to_idx2[w] = idx;
        ++idx;
    }

    int V = idx;
    BipartiteMatching bm(V);
    REP(n, N) {
        string s1 = word_vec1[n];
        string s2 = word_vec2[n];
        bm.add_edge(word_to_idx1[s1], word_to_idx2[s2]);
    }

    // 二部マッチングのエッジ数を数える
    auto real_num = bm.bipartite_matching();

    // マッチングから漏れた頂点を数える
    REP(i, V) {
        auto p = bm.return_pair(i);
        real_num += (p == -1);
    }

    cout << N - real_num << endl;
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": ";
        solve();
    }

    return 0;
}
