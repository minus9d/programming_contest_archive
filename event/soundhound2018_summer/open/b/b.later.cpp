// 本番中は全く解けず
// 0以下の数値がK以上連続して並ぶならそこはすべて0にできる、
// など考えていたが、何をしていいかわからなかった
//
// https://beta.atcoder.jp/contests/soundhound2018-summer-final-open/submissions/2912994
// を参考に実装
//
//

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

int main(void)
{
    cin.sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    vector<ll> Bs(N);
    REP(i, N) cin >> Bs[i];


    // dp[i+1]: 配列の1番目からi番目までのサブ配列での答。
    // ma[i+1]: dp[1] ~ dp[i+1]までの最大値。
    //          気持ちとしては、
    //          配列の1番目からi番目までのサブ配列において
    //          サブ配列の右端から任意個の要素をゼロにできる、
    //          と条件を緩和したときの答になっている

    vector<ll> dp(N + 1);
    vector<ll> ma(N + 1);

    FOR(i, 1, N + 1) {
        dp[i] = dp[i - 1] + Bs[i - 1];
        if (i >= K) {
            dp[i] = max(dp[i], ma[i - K]);
        }
        ma[i] = max(ma[i - 1], dp[i]);
    }

    cerr << "B : ";
    REP(i, N) cerr << Bs[i] << "\t"; cerr << endl;
    cerr << "dp: ";
    FOR(i, 1, N + 1) cerr << dp[i] << "\t"; cerr << endl;
    cerr << "ma: ";
    FOR(i, 1, N + 1) cerr << ma[i] << "\t"; cerr << endl;


    cout << dp[N] << endl;
    return 0;
}
