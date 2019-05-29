// 本番中に解けた
//
// 道路工事を、すべて、原点での時間に置き換えて考える
// 実装は冗長な可能性がある

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
    int N, Q;
    cin >> N >> Q;

    // time, index
    vector<tuple<ll, ll, ll>> ins;
    vector<tuple<ll, ll, ll>> outs;

    vector<tuple<ll, ll, ll>> STXs(N);
    REP(n, N) {
        int s, t, x;
        cin >> s >> t >> x;
        STXs[n] = mt(s, t, x);

        // 原点での時間に換算
        ins.pb(mt(s - x, x, n));
        outs.pb(mt(t - x, x, n));
    }
    sort(ALL(ins));
    sort(ALL(outs));

    vector<ll> Ds(Q);
    REP(q, Q) cin >> Ds[q];

    int pos1 = 0;
    int pos2 = 0;

    // 発生中の工事を保持
    // 原点に近い箇所で行われている工事のほうが先にくるようpairを持つ
    set<pair<ll, ll>> event;  // <座標, idx>

    // 時刻を進めていく
    for(auto d: Ds) {

        // 工事が発生したらeventを追加
        while(pos1 < N && get<0>(ins[pos1]) <= d) {
			auto t1 = get<1>(ins[pos1]);
			auto t2 = get<2>(ins[pos1]);
			event.insert(mp(t1, t2));
            ++pos1;
        }
        // 工事が終了したらeventを削除
        while(pos2 < N && get<0>(outs[pos2]) <= d) {
			auto t1 = get<1>(outs[pos2]);
			auto t2 = get<2>(outs[pos2]);
			event.erase(mp(t1, t2));
			++pos2;
        }
		//cerr << "event: "; for (auto e : event) cerr << e << " "; cerr << endl;
        if (event.empty()) cout << -1 << endl;
        else {
            auto itr = *event.begin();
			auto idx = itr.second;
            cout << get<2>(STXs[idx]) << endl;
        }
        
    }
    

    return 0;
}
