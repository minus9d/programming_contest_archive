#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
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

ll H, W, N_st, N_ele, V;
ll calc_ans(string type, ll x1, ll y1, ll x2, ll y2, ll y_loc) {
    ll ans = 0;
    auto x_diff = abs(x2 - x1);
    if (type == "stairs") {
        ans += x_diff;
    }
    else {
        ans += (x_diff + (V - 1)) / V;
    }

    ans += abs(y1 - y_loc) + abs(y_loc - y2);
    return ans;
}


int main(void)
{
    cin.sync_with_stdio(false);
    cin >> H >> W >> N_st >> N_ele >> V;

    vector<int> stairs(N_st);
    vector<int> elevs(N_ele);

    REP(n, N_st) cin >> stairs[n];
    REP(n, N_ele) cin >> elevs[n];

    int Q;
    cin >> Q;
    REP(q, Q) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) {
            cout << abs(y1 - y2) << endl;
        }
        else {
            ll ans = 1e18;

            for (auto y_loc: {y1, y2})  {
                auto it = lower_bound(ALL(stairs), y_loc);
                if (it != stairs.begin()) {
                    ans = min(ans, calc_ans("stairs", x1, y1, x2, y2, *(it - 1)));
                }
                if (it != stairs.end()) {
                    ans = min(ans, calc_ans("stairs", x1, y1, x2, y2, *it));
                }
            }

            for (auto y_loc: {y1, y2})  {
                auto it2 = lower_bound(ALL(elevs), y_loc);
                if (it2 != elevs.begin()) {
                    ans = min(ans, calc_ans("elevs", x1, y1, x2, y2, *(it2 - 1)));
                }
                if (it2 != elevs.end()) {
                    ans = min(ans, calc_ans("elevs", x1, y1, x2, y2, *it2));
                }
            }

            cout << ans << endl;
        }
    }
    return 0;
}


