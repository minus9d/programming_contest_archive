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

vector<set<int>> edges;

bool can_reach(int from, int to, int prev){
    if (from == to) return true;

    bool ret = false;
    for(auto& v: edges[from]) {
        if (v == prev) continue;
        if (can_reach(v, to, from)) {
            ret = true;
            break;
        }
    }
    return ret;
}


int main(void)
{
    int N, M, S;
    cin >> N >> M >> S;
    --S;

    edges.resize(N);
    REP(m,M) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        edges[u].insert(v);
        edges[v].insert(u);
    }

    REP(n, N) {
        bool ret = can_reach(S, n, -1);
        if(ret) {
            cout << (n+1) << endl;
            for(auto& v: edges[n]) {
                edges[v].erase(n);
            }
            edges[n].clear();
        }
    }

    return 0;
}
