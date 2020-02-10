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
    ll N, K;
    cin >> N >> K;

    vector<ll> Ps(N);
    REP(n, N) cin >> Ps[n];

    double val = 0.0;
    REP(k, K) {
        ll p = Ps[k];
        val += (1.0 + p) / 2.0;
    }
    double ans = val;

    FOR(k, K, N) {
        ll p = Ps[k];
        val += (1.0 + p) / 2.0;
        val -= (1.0 + Ps[k - K]) / 2.0;
        ans = max(ans, val);
    }
    printf("%.20f\n", ans);

    return 0;
}
