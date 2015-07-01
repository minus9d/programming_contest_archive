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


int main(){
    int N, W;
    cin >> N >> W;

    vector<int> vs(N);
    vector<int> ws(N);
    REP(i, N) cin >> vs[i] >> ws[i];

    // [何個目まで見たか][重さ] = 価値
    vector<vector<int>> dp(N+1, vector<int>(W+1));

    FOR(n, 1, N+1) {
        auto weight = ws[n-1];
        auto value = vs[n-1];
        REP(w, W+1) {
            if (w >= weight) {
                dp[n][w] = max(dp[n-1][w - weight] + value,
                               max(dp[n-1][w],
                                   dp[n][w - weight] + value
                                   ));
            }
            else 
                dp[n][w] = dp[n-1][w];
        }
    }

    int ret = 0;
    REP(w, W+1) {
        ret = max(ret, dp[N][w]);
    }
    cout << ret << endl;

    return 0;
}
