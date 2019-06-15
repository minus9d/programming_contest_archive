// 本番中に書いてTLEになったコード
//
// A->B, B->Aを別々に考える。
//
// (1)A->Bに行くとき、
//    Aにて金に何グラム変えるか、銀に何グラム変えるかを全探索して、
//    Bでのドングリの数を最大化。
//
// (2)B->Aも同様。
//
// 本番ではドングリの数を最大化するところでTLEした。
// https://atcoder.jp/contests/diverta2019-2/submissions/5926907
// を参考にDPで解き直した。
//
// 最初のドングリの数をナップサックの容量と考える。
// ドングリP個をドングリQ個に変えられるというのを、
// 容量Pで価値Qの品物だと読み替える。

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

ll solve(ll Ga, ll Sa, ll Ba,
         ll Gb, ll Sb, ll Bb,
         ll N) { 
    vector<ll> dp(N + 1);
    FOR(i, 1, N + 1) {
        dp[i] = dp[i - 1] + 1;  // ドングリから金属に変えない場合
        if (i >= Ga) dp[i] = max(dp[i], dp[i - Ga] + Gb);
        if (i >= Sa) dp[i] = max(dp[i], dp[i - Sa] + Sb);
        if (i >= Ba) dp[i] = max(dp[i], dp[i - Ba] + Bb);
    }
    return dp[N];
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N;
    cin >> N;
    ll Ga, Sa, Ba;
    ll Gb, Sb, Bb;
    cin >> Ga >> Sa >> Ba;
    cin >> Gb >> Sb >> Bb;

    ll acorns1 = solve(Ga, Sa, Ba, Gb, Sb, Bb, N);
    cerr << acorns1 << endl;
    ll acorns2 = solve(Gb, Sb, Bb, Ga, Sa, Ba, acorns1);
    cout << acorns2 << endl;
    return 0;
}
