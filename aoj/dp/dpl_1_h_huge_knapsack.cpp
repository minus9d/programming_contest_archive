// 巨大ナップサック問題  N <= 40の代わりにv, wが巨大
// 蟻本p148と同じ

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
ll knapsack(ll N, ll W, vector<ll>& v, vector<ll>& w) {
    ll INF = 1e18;
    // 前半部の全列挙
    vector<pair<ll,ll>> wv;
    ll N2 = N / 2;
    REP(i, (1 << N2)) {
        ll sw = 0, sv = 0;
        REP(j, N2) {
            if ((i >> j) & 1) {
                sw += w[j];
                sv += v[j];
            }
        }
        wv.pb(mp(sw, sv));
    }
    // 無駄な要素を削除（重さが重いのに価値が少ないようなものを捨てる）
    sort(wv.begin(), wv.end());
    int m = 1;
    FOR(i, 1, (1 << N2)) {
        if (wv[m-1].second < wv[i].second) {
            wv[m++] = wv[i];
        }
    }
    wv.resize(m); // 無駄な要素を捨てる

    // 後半部の全列挙
    ll ans = 0;
    REP(i, (1 << (N - N2))) {
        ll sw = 0, sv = 0;
        REP(j, N - N2) {
            if ((i >> j) & 1) {
                sw += w[N2 + j];
                sv += v[N2 + j];
            }
        }
        if (sw <= W) {
            auto t = (lower_bound(wv.begin(), wv.end(), make_pair(W - sw, INF)) - 1);
            ll tw = t->first;
            ll tv = t->second;
            // cout << "sw " << sw << " + tw " << tw << " = " << (sw + tw) << ". value = " << (sv + tv) <<  endl;
            ans = max(ans, sv + tv);
        }
    }
    return ans;
}

int main(){
    ll N, W;
    cin >> N >> W;
    vector<ll> v(N);
    vector<ll> w(N);
    REP(n, N) cin >> v[n] >> w[n];
    auto ans = knapsack(N, W, v, w);
    cout << ans << endl;
    return 0;
}
