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
#include <cassert>

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

map<pair<int, int>, ll> cache;

ll dfs(vector<int>& Ws, int b, int e, int depth) {
    if (cache.count(mp(b, e))) return cache[mp(b, e)] + (depth * accumulate(Ws.begin() + b, Ws.begin() + e, 0LL));

    ll ans = 0;
    if (e - b == 1) {
        ans = Ws[b] * depth;
    }
    else {
        ll best = ll(1e18);
        FOR(i, b + 1, e) {
            auto val1 = dfs(Ws, b, i, depth + 1);
            auto val2 = dfs(Ws, i, e, depth + 1);
            auto val = val1 + val2;
            best = min(best, val);
        }
        ans = best;
    }

    cache[mp(b, e)] = ans - (depth * accumulate(Ws.begin() + b, Ws.begin() + e, 0LL));
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    vector<int> Ws(N);
    REP(n, N) cin >> Ws[n];

    auto ret = dfs(Ws, 0, N, 0);
    cout << ret << endl;

    return 0;
}
