// 本番中に解けた
// B, CとD, Eとの分割方法を全部試す
// 各分割方法にて、B, CとD, Eの分割場所は、二分探索により見つかる
// 不安なので二分探索で見つかった場所の前後も試したが、もっと簡単にできたかも

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
    int N;
    cin >> N;
    vector<ll> As(N);
    REP(n,N) cin >> As[n];
    ll S = accumulate(ALL(As), 0LL);

    vector<ll> l2r(N);
    REP(n,N){
        if (n == 0) l2r[n] = As[n];
        else l2r[n] = As[n] + l2r[n-1];
    }
    vector<ll> r2l(N);
    for(int n = N-1; n >= 0; --n) {
        if (n == N-1) r2l[n] = As[n];
        else r2l[n] = As[n] + r2l[n+1];
    }

    ll ans = 1e18;
    // 前後半に分ける
    FOR(spl, 2, N-1) {
        //cout << "spl:" << spl << endl;
        vector<pair<ll,ll>> PQs;
        vector<pair<ll,ll>> RSs;

        // 前半の合計
        {
            ll sum1 = l2r[spl-1];
            auto itr = lower_bound(ALL(l2r), sum1 / 2);
            auto idx = itr - l2r.begin();
            for(auto idx2: {idx-1,idx,idx+1}) {
                if (idx2<=0 || idx2>=spl) continue;
                auto P_cand = l2r[idx2-1];
                auto Q_cand = sum1 - P_cand;
                PQs.pb({P_cand,Q_cand});
            }
        }
        // 後半の合計
        {
            auto itr = lower_bound(ALL(l2r), (l2r[N-1] + l2r[spl-1]) / 2); // 最初spl-1でなくsplとしてWA
            auto idx = itr - l2r.begin();
            for(auto idx2: {idx-1,idx,idx+1}) {
                if (idx2<=spl || idx2>=N) continue;
                auto R_cand = l2r[idx2-1] - l2r[spl-1];
                auto S_cand = l2r[N-1] - l2r[idx2-1];
                RSs.pb({R_cand,S_cand});
            }
        }
        // オーバーキルかも
        for(auto pq: PQs) {
            for(auto rs: RSs) {
                //cout << "P, Q, R, S = " << pq.first << ", " << pq.second << ", " << rs.first << ", " << rs.second << endl;
                auto mn = min(min(min(pq.first, pq.second), rs.first), rs.second);
                auto mx = max(max(max(pq.first, pq.second), rs.first), rs.second);
                ans = min(ans, mx - mn);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
