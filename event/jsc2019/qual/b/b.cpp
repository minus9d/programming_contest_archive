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

const ll MOD = ll(1e9) + 7;
int main(void)
{
    cin.sync_with_stdio(false);
    ll N, K;
    cin >> N >> K;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];

    ll c = (K - 1) * K / 2;
    c %= MOD;

    vector<ll> num(N);
    vector<ll> seen;
    for(int i = N - 1; i >= 0; --i) {
        auto a = As[i];
        auto it = lower_bound(ALL(seen), a);
        num[i] = it - seen.begin();
        seen.insert(it, a);
    }

    vector<ll> num2(N);
    REP(i, N) {
        num2[i] = lower_bound(ALL(seen), As[i]) - seen.begin();
    }

    ll ans = 0;
    REP(i, N) {
        auto add1 = c * num2[i];
        auto add2 = num[i] * K;

        auto add = add1 + add2;
        add %= MOD;

        ans += add;
        ans %= MOD;
    }
    cout << ans << endl;

    return 0;
}
