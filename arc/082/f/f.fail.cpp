#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

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
    ll X, K, Q;
    cin >> X >> K;
    vector<ll> Rs(K);
    REP(k,K) cin >> Rs[k];
    cin >> Q;

    // 便宜上
    ++K;
    Rs.pb(1e9 + 1000);

    vector<tuple<ll,ll, int>> queries(Q);
    REP(q, Q) {
        ll t, a;
        cin >> t >> a;
        queries[q] = mt(t,a,q);
    }

    sort(ALL(queries));

    vector<ll> ans(Q);
    bool down = true;

    ll mx = X;
    ll mn = 0;
    ll offset = 0;

    ll prev_r = 0;
    int q_idx = 0;
    ll cont = true;
    REP(i, K) {
        // cout << "i, mx, mn, offset = " << i << ","
        //      << mx << ","
        //      << mn << ","
        //      << offset << "," << endl;

        auto r = Rs[i];
        while(true) {
            auto t = get<0>(queries[q_idx]);
            auto a = get<1>(queries[q_idx]);
            auto q = get<2>(queries[q_idx]);
            if (t <= r) {
                a = min(a, mx);
                a = max(a, mn);
                a += offset;
                if (down) {
                    a -= t - prev_r;
                    a = max(a, 0LL);
                }
                else {
                    a += t - prev_r;
                    a = min(a, X);
                }
                ans[q] = a;
                
                ++q_idx;
                if(q_idx == Q) {
                    cont = false;
                    break;
                }
            }
            else {
                break;
            }
        }
        if (!cont) break;

        // 値の幅をかえる
        auto range = r - prev_r;
        auto mx_now = mx + offset;
        auto mn_now = mn + offset;

        // cout << "range: " << range << endl;
        if (down) {
            // offset = max(mx - range, 0LL) - mx;
            auto mx_after = max((mx + offset) - range, 0LL);
            offset = mx_after - mx;

            // cout << "  offset : " << offset << endl;
            mn_now = max(0LL, mn - range);
            mn = max(mn, mn_now - offset);
        }
        else {
            // offset = min(mn + range, X) - mn;
            auto mn_after = min((mn + offset) + range, X);
            offset = mn_after - mn;

            // cout << "  offset : " << offset << endl;
            mx_now = min(X, mx + range);
            mx = min(mx, mx_now - offset);
        }

        down = !down;
        prev_r = r;
    }

    REP(q,Q) {
        cout << ans[q] << endl;
    }

    return 0;
}

