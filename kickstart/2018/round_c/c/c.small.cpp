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

const ll MOD = 1000000007;

ll pow(ll n, ll k, ll MOD) {
    ll ret = 1;
    while(k > 0) {
        ret *= n;
        ret %= MOD;
        --k;
    }
    return ret;
}

void solve() {
    ll N, K, x, y, C, D, E1, E2, F;
    cin >> N >> K >> x >> y >> C >> D >> E1 >> E2 >> F;

    vector<ll> As(N);
    As[0] = (x + y) % F;
    FOR(n, 1, N) {
        auto new_x = (C * x + D * y + E1) % F;
        auto new_y = (D * x + C * y + E2) % F;
        As[n] = (new_x + new_y) % F;
        x = new_x;
        y = new_y;
    }

    ll ans = 0;
    FOR(k, 1, K+1) {
        REP(i, N) {
            int pos = 0;
            ll sum = 0;
            FOR(j, i, N) {
                ++pos;

                sum += As[j] * pow(pos, k, MOD);
                sum %= MOD;
                //cerr << "sum: " << sum << endl;

                ans += sum;
                ans %= MOD;
            }
        }
    }
    cout << ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
