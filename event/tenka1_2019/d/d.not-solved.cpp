// 本番中に書いた、
// Nが大きくなるとTLEになるコード

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

const ll MOD = 998244353;

ll solve_slow(int N, vector<ll>& As) {
    map<pair<int, int>, ll> s;
    s[mp(As[0], 0)] = 1;
    s[mp(0, As[0])] = 1;
    s[mp(0, 0)] = 1;
    FOR(n, 1, N) {
        // cout << SIZE(s) << endl;
        // cout << " == " << endl;
        // for(auto kv: s) {
        //     cout << kv.first.first << "," << kv.first.second << " = " << kv.second << endl;
        // }

        auto a = As[n];
        map<pair<int, int>, ll> s_next;
        for(auto kv: s) {
            auto rg = kv.first;
            auto num = kv.second;
            s_next[mp(rg.first + a, rg.second)] += num;
            s_next[mp(rg.first + a, rg.second)] %= MOD;

            s_next[mp(rg.first, rg.second + a)] += num;
            s_next[mp(rg.first, rg.second + a)] %= MOD;

            s_next[mp(rg.first, rg.second)] += num;
        }
        s = s_next;
    }

    ll ans = 0;
    auto sum_of_len = accumulate(ALL(As), 0);
    for(auto kv: s) {
        auto r = kv.first.first;
        auto g = kv.first.second;
        auto b = sum_of_len - r - g;
        // cout << "r, g, b = " << r << "," << g << "," << b << endl;
        if (r + g > b && g + b > r && b + r > g) {
            ans += kv.second;
            ans %= MOD;
        }
    }
    return ans;
}
int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];

    auto ans = solve_slow(N, As);

    cout << ans << endl;
    return 0;
}
