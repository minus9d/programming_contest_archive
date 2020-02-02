// 他の人の回答を参考に、より本質的にDPを書き直したもの

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

ll H, N;
vector<ll> As;
vector<ll> Bs;


ll solve_later(ll N, vector<ll>& As, vector<ll>& Bs) {

    // 両方ともin-place DPで実装可能

    // DP1: dp[何番目の魔法まで使うか][体力]
    //          = ちょうどその体力を削るのに必要な魔力の最小値
    // 本番中考えていたのはこちら
    // (削れる体力=10000, 魔力=1)という魔法のためにテーブルは長くとる
    // 参考: http://kmjp.hatenablog.jp/entry/2020/01/27/0900
    vector<ll> dp1(H + 10010, 1e18);

    // DP2: dp[何番目の魔法まで使うか][体力]
    //          = その体力を削るのに必要な魔力の最小値
    //            （その体力以上を削る場合も含む）
    // 参考: https://atcoder.jp/contests/abc153/submissions/9730947
    vector<ll> dp2(10001, 1e18);

    dp1[0] = 0;
    dp2[0] = 0;

    REP(i, N) {
        ll a = As[i];
        ll b = Bs[i];
        REP(j, H + 10000) {
            if (j - a >= 0) {
                dp1[j] = min(dp1[j],
                             dp1[j - a] + b);
            }
        }

        // 魔法(a, b)を1回撃つと魔力bで体力aが削れる
        // ということは魔力bで体力1, 2, ..., a-1も当然削れる
        FOR(j, 1, a) dp2[j] = min(dp2[j], b);
        FOR(j, a, H + 1) {
            dp2[j] = min(dp2[j],
                         dp2[j - a] + b);
        }
    }

    ll ans1 = 1e18;
    FOR(j, H, H + 10000) {
        ans1 = min(ans1, dp1[j]);
    }

    ll ans2 = dp2[H];

    assert(ans1 == ans2);

    return ans1;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> H >> N;
    As.resize(N);
    Bs.resize(N);
    REP(n, N) {
        cin >> As[n] >> Bs[n];
    }
    cout << solve_later(N, As, Bs) << endl;

    return 0;
}
