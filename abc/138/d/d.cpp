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

void dfs(ll N, vector<ll>& op, vector<vector<ll>>& edges, int v, int prev) {
    for(auto nei: edges[v]) {
        if(nei == prev) continue;
        op[nei] += op[v];
        dfs(N, op, edges, nei, v);
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, Q;
    cin >> N >> Q;
    vector<vector<ll>> edges(N);

    REP(n, N-1) {
        ll a, b;
        cin >> a >> b;
        --a; --b;
        edges[a].pb(b);
        edges[b].pb(a);
    }
    vector<ll> op(N);
    REP(q, Q) {
        ll p, x;
        cin >> p >> x;
        --p;
        op[p] += x;
    }

    dfs(N, op, edges, 0, -1);

    REP(i, N) {
        if (i != 0) cout << " ";
        cout << op[i];
    }
    cout << endl;

    return 0;
}
