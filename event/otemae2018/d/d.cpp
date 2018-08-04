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

int N; // 頂点数

vector<int> Ts;
vector<vector<int>> As;

vector<vector<int>> dp;

int INF = 1e9;

// S: これまでたどった頂点  v: 今いる頂点
ll rec(int S, int v) {
    if (dp[S][v] >= 0) return dp[S][v];
    if (S == (1 << N) - 1) {
        return dp[S][v] = 0;
    }

    ll res = INF;
    REP(u, N) {  // vの次に行く頂点をuとする
        if (!(S & (1 << u))) { // uに未訪問の場合
            int need = Ts[u];
            // 勉強済みのがあるか？
            REP(n, N) {
                if (S & (1 << n)) {
                    need -= As[n][u];
                }
            }
            need = max(0, need);
            
            auto tmp = need + rec(S | (1 << u), u);
            res = min(res, tmp);
        }
    }
    //cout << "dp[";
    //    REP(u, N) {
    //        cout << ((S & (1 << u)) ? "1" : "0");
    //    }
    //    cout << "][" << v << "] = " << res << endl;
    return dp[S][v] = res;
}

int main(){
    cin >> N;
    Ts.resize(N);
    As.resize(N, vector<int>(N));
    REP(n, N) cin >> Ts[n];
    REP(n1, N) REP(n2, N) cin >> As[n1][n2];

    // dp用のテーブル
    dp.resize(1<<N, vector<int>(N, -INF));

    cout << rec(0, 0) << endl;
    return 0;
}

