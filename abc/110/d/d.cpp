// 時間内に解けた
// 素因数分解して、各素因数ごとに考えればよい
// メモ化再帰だと再帰が深すぎるので、配列でDPする必要がある

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

ll MOD = 1000000007;

map<int, int> get_factors(ll M) {
    int n = 2;
    map<int, int> ret;
    while(M != 1) {
        int cnt = 0;
        while (M % n == 0) {
            M /= n;
            ++cnt;
        }
        if (cnt != 0) {
            ret[n] = cnt;
        }
        if (n == 2) n = 3;
        else n += 2;
    }
    return ret;
}

// N個の席に、stone_num個の石を並べる場合の数
// 再帰が深すぎてNG
map<pair<int,int>,ll> cache;
ll func(ll N, int stone_num, int idx) {
    cout << N << "," << stone_num << "," << idx << endl;
    if (cache.count({stone_num,idx})) return cache[{stone_num,idx}];
    ll ans = 0;

    if (idx == N-1) {
        ans = 1;
    }
    else {
        REP(i, stone_num+1) {
            ans += func(N, stone_num - i, idx + 1);
            ans %= MOD;
        }
    }
    return cache[{stone_num,idx}] = ans;
}



// N個の席に、stone_num個の石を並べる場合の数
// 以下のように再帰できる
//   ある桁
//   0個残ってる: a
//   1個残ってる: b
//   2個残ってる: c
//   3個残ってる: d
//   次の桁
//   0個残ってる: a + b + c + d
//   1個残ってる: b + c + d
//   2個残ってる: c + d
//   3個残ってる: d

ll func2(ll N, int stone_num) {
    // [桁位置][残りの石数]
    vector<vector<ll>> dp(N+1, vector<ll>(stone_num + 1));

    dp[0][stone_num] = 1;

    FOR(n, 1, N + 1) {
        ll v = 0;
        for(int s = stone_num; s >= 0; --s) {
            v += dp[n-1][s];
            v %= MOD;
            dp[n][s] = v;
        }
    }
    return dp[N][0];
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, M;
    cin >> N >> M;
    map<int, int> factors = get_factors(M);

    // for(auto kv: factors) {
    //     cout << kv.first << ": " << kv.second << endl;
    // }

    // M = 2^3 * 3^5 だとすると
    // 2はどこかに3つ、
    // 3はどこかに5つある
    ll ans = 1;
    for(auto kv: factors) {
        auto n = kv.first;
        auto cnt = kv.second;
        // ans *= func(N, cnt, 0);  // 再帰深すぎ
        ans *= func2(N, cnt);
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}
