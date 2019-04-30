// 本番中に解いた
//
// dp[位置][好意をほのめかした日数][最後に好意をほのめかしてからの経過日数] で解く。
// ただし、MLEになる。
// 
// M >= 183 && K >= 183のときはどのように日を選んでも必ず条件を満たせるので、
// greedyに簡単に解ける。
// このときを除くとdpのメモリ量が制限に収まるので、MLEを防げる。
//
// 解説PDFは別の解き方をしている

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

ll slow(ll N, ll M, ll K, vector<ll>& As_orig) {

    vector<int> shff(N);
    REP(m, M) shff[m] = 1;
    sort(ALL(shff));

    ll ans = -1;
    int prev = -1;
    do {
        bool ok = true;
        ll local = 0;
        REP(n, N) {
            if (shff[n] == 1) {
                local += As_orig[n];
                prev = n;
            } else {
                if (n - prev == K) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) ans = max(ans, local);
    }while(next_permutation(ALL(shff)));
    return ans;
}

ll fast(ll N, ll M, ll K, vector<ll>& As_orig) {

    // MLE対策としてdpのメモリが大きくなるものを別処理
    // このときは最大のものを順に選べばよい
    if (M >= 183 && K >= 183) {
        auto As = As_orig;
        sort(ALL(As));
        reverse(ALL(As));
        ll ans = 0;
        REP(m, M) ans += As[m];
        return ans;
    }

    vector<ll> As(N+1);
    REP(n, N) As[n+1] = As_orig[n];

    // [位置][好意をほのめかした日数][最後に好意をほのめかしてからの経過日数]
    vector<vector<vector<ll>>> dp((N+1), vector<vector<ll>>((M+1), vector<ll>((K+1), -1)));
    
    // memset(dp, -1, sizeof(dp));
    dp[0][0][0] = 0;
    FOR(n, 1, N + 1) {
        // 使う
        REP(m, M) {
            ll tmp = 0;
            REP(k, K) {
                if (dp[n - 1][m][k] != -1) {
                    tmp = max(tmp, dp[n - 1][m][k] + As[n]);
                }
            }
            if (tmp != 0) {
                dp[n][m + 1][0] = max(dp[n][m + 1][0], tmp);
            }
        }
        // 使わない
        REP(m, M + 1) {
            REP(k, K - 1) {
                dp[n][m][k + 1] = dp[n - 1][m][k];
            }
        }

        // cout << "=====" << endl;
        // REP(m, M + 1) {
        //     REP(k, K) {
        //         cout << "dp[" << n << "][" << m << "][" << k << "] =" << dp[n][m][k] << endl;
        //     }
        // }
    }

    ll ans = 0;
    REP(k, K) {
        ans = max(ans, dp[N][M][k]);
    }
    if (ans == 0) {
        return -1;
    } else {
        return ans;
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, M, K;
    cin >> N >> M >> K;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];

    // while(1) {
    //     ll N = rand() % 30 + 1;
    //     ll M = rand() % N + 1;
    //     ll K = rand() % N + 1;
    //     vector<ll> As(N);
    //     REP(n, N) As[n] = (rand() % 1000) + 1;
    //     auto ans1 = fast(N, M, K, As);
    //     auto ans2 = slow(N, M, K, As);
    //     if (ans1 != ans2) {
    //         cout << "error" << endl;
    //         cout << N << " " << M << " " << K << endl;
    //         for(auto a: As) cout << a << " "; cout << endl;
    //         cout << "expected:" << ans2 << endl;
    //         cout << "mine:" << ans1 << endl;
    //         return 0;
    //     }
    // }

    auto ans1 = fast(N, M, K, As);
    cout << ans1 << endl;
    // auto ans2 = slow(N, M, K, As);
    // cout << ans2 << endl;

    return 0;
}
