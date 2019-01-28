// 本番中にAC
//
// rootは簡単に求まる。
// rootの行き先になっているノードのうち、rootからしかエッジが来ていないノードは
// rootの真の子であることが確定できる。
//
// トポロジカルソートでも解けるらしい

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
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> from_to(N - 1 + M);
    vector<int> not_root(N);
    vector<set<int>> children(N);
    vector<set<int>> from(N); // 自分をさしてるノード
    REP(i, N - 1 + M) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        from_to[i] = mp(a, b);
        not_root[b] = 1;
        children[a].insert(b);
        from[b].insert(a);
    }
    int root = -1;
    REP(n, N) {
        if (!not_root[n]) {
            root = n;
            break;
        }
    }

    vector<int> parent(N);
    parent[root] = -1;
    set<int> seen;
    set<int> queue({ root });
    while (!queue.empty()) {
        set<int> next_queue;
        for (auto v : queue) {
            for (auto child : children[v]) {
                from[child].erase(v);
                if (SIZE(from[child]) == 0) {
                    parent[child] = v;
                    next_queue.insert(child);
                }
            }
        }
        queue = next_queue;
    }

    for (auto p : parent) {
        cout << (p + 1) << endl;
    }

    return 0;
}
