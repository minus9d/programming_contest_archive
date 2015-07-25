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
#include <cstdlib>
#include <cstring>

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
    
    if (dp[i][weight] >= 0) return dp[i][weight];
    
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

    // weight, value
    vector<pair<int,int>> vs(N);
    REP(n,N) {
        cin >> vs[n].first >> vs[n].second;
    }
    sort(ALL(vs));

    memset(dp, -1, sizeof(dp));

    // 普通にP以下で01ナップサック
    auto ret = solve(0, P, vs);

    cout << "ret = " << ret << endl;

    // ナップサックに入っているもののうち重さ最小のものを探す
    // http://stackoverflow.com/questions/7489398/how-to-find-which-elements-are-in-the-bag-using-knapsack-algorithm-and-not-onl
    // → 探し方分からず…
    auto i = N-1;
    int line = P;
    vector<char> chosen(N);
    int mn = 1e9;
    int weight = 0;
    int ret2 = ret;
    while(i >= 0) {
        if (dp[line][i] - dp[line - vs[i].first][i-1] == vs[i].second) {
            chosen[i] = 1;
            mn = min(mn, vs[i].first);
            line = line - vs[i].first;
            weight += vs[i].first;
        }
        --i;
    }

    for(auto v : chosen) cout << (int)v << ",";
    cout << endl;

    // 条件をそこなわずに追加できるものを探す
    int mx_val = 0;
    REP(i, N) {
        if(chosen[i]) continue;
        if(weight + vs[i].first - min(mn, vs[i].first) <= P) {
            mx_val = max(mx_val, vs[i].second);
        }
    }

    cout << ret + mx_val << endl;

    return 0;
}
