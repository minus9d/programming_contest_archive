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
#include <complex>

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

int dp[5001][5001];

int solve(int i, int weight, vector<pair<int, int> > &knapsacks){
    // printf("i, weight = %d, %d\n", i, weight);

    int ret ;
    
    if (dp[i][weight]) return dp[i][weight];
    
    if (i >= knapsacks.size()){
        ret = 0;
    }
    else if (knapsacks[i].first > weight){
        ret = solve(i+1, weight, knapsacks);
    }
    else {
        ret = max( solve(i+1, weight - knapsacks[i].first, knapsacks) + knapsacks[i].second 
                , solve(i+1, weight, knapsacks) );
    }

    dp[i][weight] = ret;
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N, P;
    cin >> N >> P;

    vector<pair<int,int>> vs(N);
    REP(n,N) {
        cin >> vs[n].first >> vs[n].second;
    }
    sort(ALL(vs));

    int ret = 0;

    // 一番小さいのを決める
    REP(i, N) {
        int value = vs[i].second;
        // 決めたのより大きなものだけでP以下になるよう価値最大化
        value += solve(i+1, P, vs);
        ret = max(ret, value);
    }

    cout << ret << endl;

    return 0;
}
