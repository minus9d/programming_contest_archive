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

//     5 1 3 2 4
// -------------
// 0   0 0 0 0 0
// 1   0 1 1 1 1
// 2   0 0 0 2 2
// 3   0 0 2 2 2
// 4   0 0 0 0 3
// 5   1 1 1 1 1




int main(){
    int N;
    cin >> N;

    // vector<int> as(N);
    int MX = 100000;
    vector<vector<int>> dp(N+1, vector<int>(100000));
    REP(n,N) {
        int a;
        cin >> a;

        if(n == 0) {
            dp[n+1][a] = 1;
        }
        else {
            // 数字を選んだ場合
            REP(b, a) {
                dp[n+1][a] = max(max(dp[n][a], dp[n+1][a]),  dp[n][b] + 1);
            }

            // 数字を選ばない場合
            REP(b, MX+1) {
                dp[n+1][b] = max(dp[n][b], dp[n+1][b]);
            }
        }
    }
    
    int ret = 0;
    REP(b,MX+1) {
        ret = max(ret, dp[N][b]);
    }

    cout << ret << endl;
    return 0;
}
