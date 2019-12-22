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

vector<vector<int>> edges;

void getDist(int v, int prev, vector<int> &dist) {
    for(auto nei: edges[v]) {
        if (nei == prev) continue;
        dist[nei] = dist[v] + 1;
        getDist(nei, v, dist);
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N, u, v;
    cin >> N >> u >> v;
    --u; --v;

    edges.resize(N);
    REP(n, N-1) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        edges[a].pb(b);
        edges[b].pb(a);
    }

    vector<int> from_u(N);
    vector<int> from_v(N);
    getDist(u, -1, from_u);
    getDist(v, -1, from_v);

    int ans = 0;
    REP(i, N) {
        auto du = from_u[i];
        auto dv = from_v[i];
        if (du < dv) {
            int local_ans = du + (dv - du - 1);
            ans = max(ans, local_ans);
        }
    }
    cout << ans << endl;

    return 0;
}
