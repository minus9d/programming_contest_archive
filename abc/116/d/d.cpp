// 本番中にAC
//
// まずおいしい順にK個の寿司を取る
// i in [K+1, N] 番目の寿司について以下をする
//   ・i番目の寿司と同じ種類の寿司がK個の中にある場合、何もしない
//   ・それ以外の場合
//      K個の寿司の中で、取り除いても寿司の異なり数を減らさず、
//      かつ、もっともおいしさの小さい寿司を取り除き、
//      i番目の寿司を代わりに入れる。このときのスコアを計算し、
//      最高スコアを更新しているかどうかチェックする

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

ll solve(ll N, ll K, vector<pair<ll, ll>>& d_and_ts) {
    // おいしさの大きい順に、単にとっていく
    ll base = 0;
    set<ll> seen;
    priority_queue<ll, vector<ll>, greater<ll> > deletable;
    ll kind = 0;
    REP(k, K) {
        auto d = -d_and_ts[k].first;
        auto t = d_and_ts[k].second;
        // cout << "d, t = " << d << "," << t << endl;
        base += d;
        if (seen.count(t)) {
            deletable.push(d);
        } else {
            ++kind;
        }
        seen.insert(t);
    }
    ll bonus = kind * kind;
    ll score = base + bonus;
    ll ans = score;
    // cout << "base " << base << " + bonus " << bonus << " = score " << score << endl;

    // deletableから1個減らし、代わりに新しい種類を加える
    FOR(k, K, N) {
        if (deletable.empty()) break;

        auto d = -d_and_ts[k].first;
        auto t = d_and_ts[k].second;
        if (!seen.count(t)) {
            seen.insert(t);
            ++kind;
            auto dele = deletable.top();
            deletable.pop();
            base -= dele;
            base += d;
            ll bonus = kind * kind;
            ll score = base + bonus;
            ans = max(ans, score);
            // cout << "base " << base << " + bonus " << bonus << " = score " << score << endl;
        }
    }
    return ans;
}



int main(void)
{
    cin.sync_with_stdio(false);
    ll N, K;
    cin >> N >> K;

    vector<pair<ll, ll>> d_and_ts;
    map<ll, vector<ll>> t_to_ds;
    REP(n, N) {
        ll t, d;
        cin >> t >> d;
        t_to_ds[t].pb(d);
        d_and_ts.pb({-d, t});
    }
    sort(ALL(d_and_ts));

    auto mine = solve(N, K, d_and_ts);
    cout << mine << endl;

    // vector<ll> bests;
    // vector<ll> remains;
    // for(auto kv: t_to_ds) {
    //     auto ds = kv.second;
    //     sort(ALL(ds));
    //     reverse(ALL(ds));
    //     REP(i, SIZE(ds)) {
    //         if (i == 0) bests.pb(ds[i]);
    //         else remains.pb(ds[i]);
    //     }
    // }

    // auto mx_kind = SIZE(t_to_ds);
    // FOR(i, 1, mx_kind + 1) {
        
    // }


    return 0;
}
