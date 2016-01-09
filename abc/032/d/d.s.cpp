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
 
ll INF = 1e15;
 
int N, W;
vector<int> vs;
vector<int> weights;
 
void dataset1()
{
    ll ret = 0;
    REP(i, (1<<N)) {
        ll value = 0;
        ll weight = 0;
        REP(j, N) {
            if ((1 << j) & i) {
                weight += weights[j];
                value += vs[j];
            }
        }
        if (weight <= (ll)W) ret = max(ret, value);
    }
    cout << ret << endl;
}
 
void dataset3()
{
    vector<vector<ll>> dp(201, vector<ll>(200*1000*1+1, INF));
 
    dp[0][0] = 0;
    REP(i,N) {
        REP(j, N*1000+1) {
            if (j < vs[i]) {
                dp[i + 1][j] = dp[i][j];
            }
            else {
                dp[i + 1][j] = min(dp[i][j], dp[i][j-vs[i]] + weights[i]);
            }
        }
    }
    ll res = 0;
    REP(i, N*1000+1) {
        if (dp[N][i] <= W) res = i;
    }
 
    cout << res << endl;
}
 
int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> W;
    vs.resize(N);
    weights.resize(N);
    REP(n,N) cin >> vs[n] >> weights[n];
 
    // if (N <= 30) {
    //     dataset1();
    // }
    // else {
        dataset3();
    // }
 
 
    return 0;
}
