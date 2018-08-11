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
    ll N, M;
    cin >> N >> M;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];

    // 累積
    ll s = 0;
    map<ll, ll> cnt;
    vector<ll> sums(N);
    REP(i, N) {
        auto a = As[i];
        s += a;
        ++cnt[s % M];
        sums[i] = s;
    }

    // for(auto s: sums) cout << s << " "; cout << endl;
    // for(auto s: sums) cout << (s % M) << " "; cout << endl;

    ll ans = 0;
    for(auto kv: cnt) {
        auto k = kv.first;
        auto v = kv.second;
        auto tmp = v * (v - 1) / 2;
        if (k == 0) {
            tmp += v;
        }
        // cout << k << ", " << v << ": " << tmp << endl;
        ans += tmp;
    }
    cout << ans << endl;
    return 0;
}
