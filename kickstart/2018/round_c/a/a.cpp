// 本番で解けた
// まず閉路を見つけ、閉路に属する点を列挙する
// あとはBFSで、各点から閉路までの距離を計算するだけ
// 閉路を見つけるのに苦労した。もっとよい書き方がありそう

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


void dfs(int v, int from, set<int>& seen, const vector<vector<int>>& edges, vector<int>& backtrace, int& v1, int &v2) {
    for (auto nei: edges[v]) {
        if (nei == from) continue;
        if (seen.count(nei)) {
            v1 = v;
            v2 = nei;
            break;
        }
        else {
            backtrace[nei] = v;
            seen.insert(nei);
            dfs(nei, v, seen, edges, backtrace, v1, v2);
        }
    }
}

set<int> find_loop(int N, const vector<vector<int>>& edges) {
    set<int> seen;
    vector<int> backtrace(N);
    backtrace[0] = -1;
    seen.insert(0);
    int v1 = -1, v2 = -1;
    dfs(0, -1, seen, edges, backtrace, v1, v2);

    set<int> loop;
    loop.insert(v1);
    int v = v2;
    while(!loop.count(v)) {
        loop.insert(v);
        v = backtrace[v];
    }

    //cerr << "loop: ";
    //for(auto v: loop) cerr << v << " ";
    //cerr << endl;

    vector<int> ans(N);
    set<int> used;
    set<int> vs;
    for (auto v : loop) {
        ans[v] = 0;
        used.insert(v);
        vs.insert(v);
    }

    int dist = 1;
    while (!vs.empty()) {
        set<int> next_vs;
        for (auto v : vs) {
            for (auto nei : edges[v]) {
                if (!used.count(nei)) {
                    next_vs.insert(nei);
                    used.insert(nei);
                    ans[nei] = dist;
                }
            }
        }
        vs = next_vs;
        ++dist;
    }

    REP(v, N) {
        cout << " " << ans[v];
    }

    return loop;
}

void solve() {
    int N;
    cin >> N;
    vector<vector<int>> edges(N);
    REP(n, N) {
        int a, b;
        cin >> a >> b; --a; --b;
        edges[a].pb(b);
        edges[b].pb(a);
    }

    auto loop = find_loop(N, edges);
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ":";
        solve();
        cout << endl;
    }
    return 0;
}
