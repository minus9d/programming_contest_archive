#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
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

vector<vector<int>> edges;
vector<int> path;
set<int> used;

void dfs(int cur) {
    while(1) {
        bool found = false;
        for(auto nei: edges[cur]) {
            if (used.count(nei)) continue;
            else {
                cur = nei;
                path.pb(nei);
                used.insert(nei);
                found = true;
                break;
            }
        }
        if (!found) break;
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    edges.resize(N);
    REP(m, M) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        edges[a].pb(b);
        edges[b].pb(a);
    }
    vector<int> deg_ones;
    vector<int> degs(N);
    REP(n,N) {
        if (SIZE(edges[n]) == 1) deg_ones.pb(n);
        degs[n] = SIZE(edges[n]);
    }

    // if (SIZE(deg_ones) > 0) {
    //     path.pb(deg_ones[0]);
    // } else {
    //     path.pb(0);
    // }
    path.pb(0);
    auto cur = path[0];
    used.insert(cur);
    dfs(cur);
    auto path_saved = path;

    path.clear();
    path.pb(0);
    dfs(cur);

    reverse(ALL(path));
    FOR(i, 1, SIZE(path_saved)) {
        path.pb(path_saved[i]);
    }

    cout << SIZE(path) << endl;
    REP(i, SIZE(path)) {
        if (i != 0) cout << " ";
        cout << (path[i] + 1);
    }
    cout << endl;

    return 0;
}
