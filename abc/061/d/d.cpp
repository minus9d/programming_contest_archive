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
class BellmanFord {
    struct edge {
        int from;
        int to;
        T cost;
    };

public:
    T INF;
    T NEGATIVE_INF;

    BellmanFord(int V)
        : INF(std::numeric_limits<T>::max())
        , NEGATIVE_INF(std::numeric_limits<T>::min())
        , m_V(V) {
        m_es.clear();
    }

    void add_dir_edge(int from, int to, T cost) {
        m_es.push_back( edge{from, to, cost} );
    }

    void add_undir_twoways(int v1, int v2, T cost) {
        add_dir_edge(v1, v2, cost);
        add_dir_edge(v2, v1, cost);
    }

    // 頂点sから各頂点までの距離を計算してdに格納
    vector<T> shortest_path(int s)
    {
        // INF: その頂点には到達できない
        // INF以外: sからの最短距離
        vector<T> d(m_V, INF);
        vector<char> has_negative_loop(m_V);
        d[s] = 0;
        REP(try_num, m_V) {
            bool update = false;
            REP(i, SIZE(m_es)) {
                edge e = m_es[i];
                if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    update = true;

                    // 無限ループ発見
                    if (try_num == m_V - 1) {
                        has_negative_loop[e.to] = 1;
                    }
                }
            }
            if (!update) break;
        }

        // cout << "dists:" << endl;
        // for (auto e: d) cout << e << " ";
        // cout << endl;
        // cout << "negative loop:" << endl;
        // for (auto e: has_negative_loop) cout << int(e) << " ";
        // cout << endl;

        // negative loopがある頂点の最短路をNEGATIVE_INFに書き換える
        REP(i, m_V) {
            if (has_negative_loop[i]) d[i] = NEGATIVE_INF;
        }

        return move(d);
    }

    // sから各頂点までの最短路に閉路があるかを返す
    bool find_negative_loop_from_v(int s) {
        vector<T> d(m_V, INF);
        
        d[s] = 0;
        // ループの実行は高々|V|-1回のはず
        // ループの実行回数が|V|よりも大きければ閉路があったとみなす
        int count = 0;
        while (true) {
            bool update = false;
            REP(i, SIZE(m_es)) {
                edge e = m_es[i];
                if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    update = true;
                }
            }
            if (!update) break;

            ++count;
            if (count > m_V) return true;
        }

        return false;
    }

    // グラフ全体のどこかに負の経路があることを検出
    bool find_negative_loop_somewhere(void) {
        vector<T> d(m_V);

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

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;

    BellmanFord<ll> bf(N);
    REP(m, M) {
        ll a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        bf.add_dir_edge(a, b, -c);
    }

    auto dists = bf.shortest_path(0);
    if (dists[N-1] == bf.NEGATIVE_INF) {
        cout << "inf" << endl;
    }
    else {
        cout << -dists[N-1] << endl;
    }

    return 0;
}
