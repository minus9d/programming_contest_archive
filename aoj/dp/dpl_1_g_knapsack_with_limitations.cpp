// 個数制限付きナップサック問題
// i番目の品物はmi個まで選べる
// 参照: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=2119650#1

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

// N: 品物の個数
// W: ナップサックの容量
// v: 品物の価値
// w: 品物の重さ
// m: 品物の最大個数
ll knapsack(ll N, ll W, vector<ll>& v, vector<ll>& w, vector<ll>& m) {
    vector<ll> dp(W+1);
    dp[0] = 0;

    // ある品物を1, 2, 4, 8...個選んだときの<価値,重さ>
    // これらを新たな品物としてみなしていることに相当する
    vector<pair<ll,ll>> vec;
    REP(i, N) {
        int cnt = 1;
        while (m[i] > 0) {
            if (cnt > m[i]) { // 端数
                vec.pb(mp(m[i]*v[i], m[i]*w[i]));
                break;
            }
            vec.pb(mp(cnt*v[i], cnt*w[i]));
            m[i] -= cnt;
            cnt += 2;
        }
    }
    REP(i, SIZE(vec)) {
        for(ll j = W; j >= vec[i].second; j--) {
            dp[j] = max(dp[j], dp[j - vec[i].second] + vec[i].first);
        }
    }
    ll maxn = 0;
    REP(i, W+1) {
        maxn = max(maxn, dp[i]);
    }
    return maxn;
}

int main(){
    ll N, W;
    cin >> N >> W;
    vector<ll> v(N);
    vector<ll> w(N);
    vector<ll> m(N);
    REP(n, N) cin >> v[n] >> w[n] >> m[n];
    auto ans = knapsack(N, W, v, w, m);
    cout << ans << endl;

    return 0;
}
