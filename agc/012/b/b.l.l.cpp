// 参考：http://pekempey.hatenablog.com/entry/2017/04/02/010647

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

// 頂点vから距離dの範囲の塗りつぶしを、時刻dp[d][v]に出された命令により行う
int dp[11][100000];

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> edges(M);

    REP(m, M) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        edges[m] = mp(a, b);
    }
    // 便宜上、自分から自分にもエッジが張られているとする
    REP(n, N) edges.pb(mp(n, n));

    int Q;
    cin >> Q;
    // 時刻tの色を保持  便宜上t = 0は色0とする
    vector<int> colors(Q + 1); 
    REP(q, Q) {
        int v, d, c;
        cin >> v >> d >> c;
        --v;
        dp[d][v] = q + 1;
        colors[q+1] = c;
    }

    for(int i = 10; i >= 1; --i) {
        for(auto edge: edges) {
            int u, v;
            tie(u, v) = edge;
            dp[i-1][u] = max(dp[i-1][u], dp[i][v]);
            dp[i-1][v] = max(dp[i-1][v], dp[i][u]);
        }
    }
    REP(v, N) {
        cout << colors[dp[0][v]] << endl;
    }
    return 0;
}
