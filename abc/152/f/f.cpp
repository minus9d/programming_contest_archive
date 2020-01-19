// 本番中にAC
// 制約を満たさない個数のほうがかんたんに数えられることに着目
// 制約を満たさない個数は、
//   (ルール1が制約を満たさない数
//     + ...
//     + ルールMが制約を満たさない数)
//  - (ルール1とルール2両方が制約を満たさない数
//     + ...
//     ルールM-1とルールM両方が制約を満たさない数)
//  ...
// などとして求められる
//


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

map<pair<int, int>, int> edge_index_dict;
vector<vector<int>> edges;

vector<int> backtrace;
void dfs(int v, int prev) {
    for(auto nei: edges[v]) {
        if (nei == prev) continue;
        backtrace[nei] = v;
        dfs(nei, v);
    }
}

ll powll(ll a, ll n) {
    ll ans = 1;
    REP(i, n) ans *= a;
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    backtrace.resize(N);
    edges.resize(N);
    REP(n, N-1) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[a].pb(b);
        edges[b].pb(a);
        edge_index_dict[mp(a, b)] = n;
        edge_index_dict[mp(b, a)] = n;
    }
    
    int M;
    cin >> M;

    // 各ルールが使う辺
    vector<vector<int>> rule_to_route(M);

    REP(m, M) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        // uからvまでで辿る辺
        vector<int> route;
        dfs(u, -1);
        int curr = v;
        while(true) {
            auto prev = backtrace[curr];
            route.pb(edge_index_dict[mp(prev, curr)]);
            if (prev == u) break;
            curr = prev;
        }
        // cerr << "m route:"; for(auto r: route) cerr << r << " "; cerr << endl;
        rule_to_route[m] = route;
    }

    // 包除原理で、条件を満たさないものを数える
    ll ans = 0;
    ll sign = 1;
    // 0b00..00 から 0b 11..11までループして
    // ビット数に応じて和か差かを決めたほうが効率がよかった
    FOR(size, 1, M + 1) {
        vector<int> shff(M);
        REP(i, size) shff[i] = 1;
        sort(ALL(shff));

        ll local_num = 0;
        do {
            // size個のルールで使う辺の集合を求める
            vector<int> edge_union(N-1);
            REP(r, M) {
                // r番目のルールで使う辺
                if (shff[r]) {
                    for (auto edge_idx: rule_to_route[r]) {
                        edge_union[edge_idx] += 1;
                    }
                }
            }
            int free_edge_num = 0;
            REP(n, N-1) free_edge_num += (edge_union[n] == 0);
            local_num += powll(2, free_edge_num);
            // cerr << "free_edge:" << free_edge_num << endl;

        }while(next_permutation(ALL(shff)));
        ans += local_num * sign;
        sign *= -1;
    }

    // 条件を満たすものの個数に変換
    cout << (powll(2, N - 1) - ans) << endl;
    return 0;
}
