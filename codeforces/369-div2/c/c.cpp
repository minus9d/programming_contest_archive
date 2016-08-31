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

ll INF = ll(1e12);
// idx, last_color, beauty
ll dp[101][101][101];

int main(void)
{
    REP(i,101) REP(j,101) REP(k,101) dp[i][j][k] = INF;

    cin.sync_with_stdio(false);
    ll N,M,K;
    cin >> N >> M >> K;
    vector<ll> Cs(N);
    REP(n,N) cin >> Cs[n];

    vector<vector<ll>> Ps(N, vector<ll>(M+1));
    REP(n,N) REP(m,M) cin >> Ps[n][m+1];

    if (Cs[0] == 0) {
        FOR(m,1,M+1) {
            dp[0][m][1] = Ps[0][m];
        }
    }
    else {
        auto col = Cs[0];
        FOR(m,1,M+1) {
            if (m == col) {
                dp[0][m][1] = 0;
            }
            else {
                dp[0][m][1] = INF;
            }
        }
    }

    FOR(idx, 1, N) {
        auto cur_col = Cs[idx];
        if (cur_col == 0) {
            FOR(prv_col,1,M+1) {
                FOR(nxt_col,1,M+1) {
                    FOR(b,1,N+1) {
                        if (prv_col == nxt_col) {
                            dp[idx][nxt_col][b] = min(dp[idx][nxt_col][b],
                                                      dp[idx-1][nxt_col][b] + Ps[idx][nxt_col]);
                        }
                        else {
                            dp[idx][nxt_col][b] = min(dp[idx][nxt_col][b],
                                                      dp[idx-1][prv_col][b-1] + Ps[idx][nxt_col]);
                            
                        }
                    }
                }
            }
        }
        // already cur_colored
        else {
            FOR(prv_col,1,M+1) {
                FOR(nxt_col,1,M+1) {
                    FOR(b,1,N+1) {
                        if (nxt_col == cur_col) {
                            if (prv_col == cur_col) {
                                dp[idx][nxt_col][b] = min(dp[idx][nxt_col][b], dp[idx-1][nxt_col][b]);
                            }
                            else {
                                dp[idx][nxt_col][b] = min(dp[idx][nxt_col][b], dp[idx-1][prv_col][b-1]);
                            }
                        }
                        else {
                            dp[idx][nxt_col][b] = INF;
                        }
                    }
                }
            }
        }

    }
    
    // debug
    // REP(idx,N) {
    //     cout << "idx: " << idx << endl;
    //     FOR(col,1,M+1) {
    //         cout << "  col:" << col << endl;
    //         cout << "    ";
    //         FOR(b,1,N+1) cout << dp[idx][col][b] << ",";
    //         cout << endl;
    //     }
    // }

    ll ans = INF;
    FOR(col,1,M+1) {
        ans = min(ans, dp[N-1][col][K]);
    }
    if (ans == INF) {
        cout << -1 << endl;
    }
    else {
        cout << ans << endl;
    }
    

    

    return 0;
}
