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

ll dp[2][100005];
ll INF = ll(1e21);

int main(void)
{
    cin.sync_with_stdio(false);
    ll N;
    cin >> N;

    vector<pair<ll,ll>> LRs(N);
    REP(n,N) {
        ll l, r;
        cin >> l >> r;
        LRs[n] = mp(l,r);
    }

    bool turn = 0;
    REP(n,N) {
        auto cur_l = LRs[n].first;
        auto cur_r = LRs[n].second;
        turn = !turn;
        if (n == 0) {
            FOR(pos, 1, 405) {
                dp[turn][pos] = abs(cur_l - pos);
            }
        }
        else {
            auto prv_l = LRs[n-1].first;
            auto prv_r = LRs[n-1].second;

            FOR(pos_cur, 1, 405) {
                dp[turn][pos_cur] = INF;
                FOR(pos_prv, 1, 405) {
                    if (dp[!turn][pos_prv] == INF) continue;
                    if (prv_r < cur_l || cur_r < prv_l) {
                        dp[turn][pos_cur] = INF;
                    }
                    else {
                        dp[turn][pos_cur] = min(dp[turn][pos_cur],
                                                dp[!turn][pos_prv] + abs(cur_l - pos_cur));
                    }
                }
            }
        }
    }

    ll ans = INF;
    FOR(pos_cur, 1, 405) {
        ans = min(ans, dp[turn][pos_cur]);
    }
    cout << ans << endl;
    
    return 0;
}

