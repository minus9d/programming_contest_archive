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

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, x;
    cin >> N >> x;
    vector<ll> As(N);
    REP(n,N) cin >> As[n];
    
    vector<ll> costs = As;
    ll ans = accumulate(ALL(costs), 0LL);
    REP(k,N) { // 魔法を唱える回数
        vector<ll> new_costs(N);
        REP(n,N) {
            new_costs[n] = min(costs[n], As[(n - k + N) % N]);
        }
        costs = new_costs;
        ans = min(ans, accumulate(ALL(costs), 0LL) + k * x);
    }
    cout << ans << endl;
    return 0;
}
