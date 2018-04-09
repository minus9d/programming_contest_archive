// 巡回セールスマン問題
// 蟻本p173と同じ。
// 訪問済状態をビットで表すとbitDPで解ける

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
#include <cassert>

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

// S: これまでたどった頂点  v: 今いる頂点   V: 頂点数
ll rec(int S, int v,
        const int V,
        vector<vector<ll>>& dp, const vector<vector<ll>>& dist) {
    if (dp[S][v] >= 0) return dp[S][v];
    if (S == (1 << V) - 1 && v == 0) {
        return dp[S][v] = 0;
    }

    ll res = INF;
    REP(u, V) {  // vの次に行く頂点をuとする
        if (!(S & (1 << u))) { // uに未訪問の場合
            auto d = dist[v][u];
            if (d != INF) { // v -> uにエッジがある場合
                auto tmp = rec(S | 1 << u, u, V, dp, dist) + d;
                res = min(res, tmp);
                cout << "  v(" << v << ") -> u(" << u << ") = " << tmp << endl;
            }
        }
    }
    cout << "dp[";
        REP(u, V) { 
            cout << ((S & (1 << u)) ? "1" : "0");
        }
        cout << "][" << v << "] = " << res << endl;
    return dp[S][v] = res;
}

ll travelling_salesman(int V, vector<vector<ll>>& dist) {
    vector<vector<ll>> dp(1<<V, vector<ll>(V, -INF));
    return rec(0, 0, V, dp, dist);
}

int main(){
    int V, E;
    cin >> V >> E;
    vector<vector<ll>> dist(V, vector<ll>(V, INF));
    REP(e, E) {
        int s, t;
        ll d;
        cin >> s >> t >> d;
        dist[s][t] = d;
    }
    auto ret = travelling_salesman(V, dist);
    cout << (ret == INF ? -1 : ret) << endl;
}
