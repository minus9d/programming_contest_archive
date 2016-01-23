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

// [loc]
ll dp[2010];

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, L;
    cin >> N >> L;
    // vector<ll> Ts(N);
    // vector<ll> Ps(N);

    if (N > 2010) return 0;

    map<ll, vector<ll>> fires;

    REP(n,N) {
        ll t, p;
        cin >> t >> p;
        fires[t].pb(p);
        // cin >> Ts[n] >> Ps[n];
    }

    for(auto fire: fires) {
        auto fireposes = fire.second;

        ll best_so_far = 1e18;
        REP(p, L+1) {
            ll added = 0;
            for(auto firepos: fireposes) {
                added += abs(ll(p) - firepos);
            }
            
            ll best = dp[p] + added;
            dp[p] = min(best, best_so_far);

            best_so_far = min(best, best_so_far);
        }
    }

    cout << dp[L] << endl;

    return 0;
}
