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
vector<int> col;

void coloring(int v, int d, int c) {
    col[v] = c;
    set<int> seen;
    seen.insert(v);

    set<int> targets;
    for(auto nei: edges[v]) {
        targets.insert(nei);
    }
    while(d > 0) {
        set<int> next_targets;
        for(auto t: targets) {
            seen.insert(t);
            col[t] = c;
            for(auto n: edges[t]) {
                if (!seen.count(n)) next_targets.insert(n);
            }
        }
        targets = next_targets;
        --d;
    }
}
 
int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    edges.resize(N);
    col.resize(N);

    REP(m, M) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        edges[a].insert(b);
        edges[b].insert(a);
    }
    int Q;
    cin >> Q;
    
    REP(q, Q) {
        int v, d, c;
        cin >> v >> d >> c;
        --v;
        coloring(v, d, c);
    }
    for(auto c : col) cout << c << endl;
    return 0;
}
