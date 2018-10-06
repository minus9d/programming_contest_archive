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

    vector<tuple<ll,ll,ll>> info;
    tuple<ll, ll, ll> non_zero;
    REP(n, N) {
        ll x, y, h;
        cin >> x >> y >> h;
        info.pb(mt(x, y, h));
        if (h != 0) {
            non_zero = mt(x, y, h);
        }
    }
    for(ll y_center = 0; y_center < 101; ++y_center) {
        for(ll x_center = 0; x_center < 101; ++x_center) {

            ll x, y, h;
            tie(x, y, h) = non_zero;
            ll h_expect = abs(y_center - y) + abs(x_center - x) + h;

            bool ok = true;
            REP(i, SIZE(info)) {
                tie(x, y, h) = info[i];
                // !!! maxをとるのを忘れてWA
                auto should_h = max(0LL, h_expect - (abs(y_center - y) + abs(x_center - x)));
                if (should_h != h) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                cout << x_center << " " << y_center << " " << h_expect << endl;
                return 0;
            }
        }
    }
    return 0;
}
