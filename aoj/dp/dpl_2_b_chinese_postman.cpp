// 中国人郵便配達問題
//   連結無向グラフが与えられる。各辺を少なくとも一度通り元の場所に戻る最短経路を求める。
// 参照: https://gist.github.com/tjkendev/898454acfc4961b5bdd09b4088b75de3
//      https://ja.wikipedia.org/wiki/%E4%B8%AD%E5%9B%BD%E4%BA%BA%E9%83%B5%E4%BE%BF%E9%85%8D%E9%81%94%E5%95%8F%E9%A1%8C
// 方針:
//   すべての頂点の次数が偶数のとき、すべての辺を一度だけ通って一周できる（オイラー閉路）。
//   奇数次数の頂点はかならず偶数個ある。この頂点を適当に二つずつ組み合わせる。
//   このペアとなった頂点組について、最短経路を見つけて、最短経路上にある辺をそれぞれ1本増やすことで、
//   奇数次数の頂点が2個減らせる。
//   頂点の組み合わせの取り方のうち、もっともよいペアリングをbitDPで見つける。

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

ll INF = 1e18;

const int MAX_V = 15;
ll memo[(1 << MAX_V)]; // memo

// まだペアリングされていない奇数次数の頂点について、最適なペアリングを行ったときに
// 増加する辺コストの和を返す。
// state: 各ビットが、奇数次数の頂点がすでにペアリングされたか否かを表す
ll dfs(int state, vector<int>& odd, vector<vector<ll>>& e) {
    if (memo[state] >= 0) return memo[state];
    ll res = INF;
    // 頂点uと頂点vがまだペアリングされていなければペアリングする
    REP(i, SIZE(odd)) {
        auto u = odd[i];
        if (state & (1 << i)) {
            continue;
        }
        REP(j, SIZE(odd)) {
            auto v = odd[j];
            if (u == v || state & (1 << j) || e[u][v] == INF) {
                continue;
            }
            res = min(res, dfs(state | (1 << i) | (1 << j), odd, e) + e[u][v]);
        }
    }
    memo[state] = res;
    return res;
}

int main(void) {
    int V, E;
    cin >> V >> E;

    ll INF = 1e9;
    vector<vector<ll>> e(V, vector<ll>(V, INF));  // 全2点間の最小距離
    vector<ll> deg(V);
    ll su = 0;
    REP(i, E) {
        int s, t; ll d;
        cin >> s >> t >> d;
        e[s][t] = e[t][s] = min(e[s][t], d);
        deg[s] += 1;
        deg[t] += 1;
        su += d;
    }

    // 次数が奇数の頂点を格納。必ず奇数個となる
    vector<int> odd;
    REP(v, V) {
        if (deg[v] % 2) odd.pb(v);
    }

    memset(memo, -1, sizeof(memo));
    memo[(1 << SIZE(odd)) - 1] = 0;

    // Warshall–Floyd Algorithm
    REP(k, V) REP(i, V) REP(j, V) e[i][j] = min(e[i][j], e[i][k] + e[k][j]);

    cout << dfs(0, odd, e) + su << endl;
    return 0;
}
