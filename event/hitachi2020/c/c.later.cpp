// 本番後にAC
//
// 本番中、頂点からの距離が偶数なら1 mod 3, 奇数なら2 mod 3にすると、
// かならず距離3のペアの和を0 mod 3にできることには気づけた。
// そこから適当なノードを0 mod 3にすることを考えたが、どうしてよいか分からなかった。
// 
// 解説PDFを読み納得。そのとおりに実装。
// 本番中は木の直径が2以下の場合を場合分けしたが、不要だった

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

vector<int> solve(const int N, const vector<pair<int, int>>& ABs) {
    vector<int> ans(N + 1);

    vector<vector<int>> edges(N + 1);
    for(auto ab: ABs) {
        auto a = ab.first;
        auto b = ab.second;
        edges[a].pb(b);
        edges[b].pb(a);
    }

    vector<int> nodes;
    nodes.pb(1);
    // rootからの距離が奇数である点をred, 偶数である点をblueとする
    vector<int> blues;
    vector<int> reds;

    vector<int> seen(N + 1);
    bool one_flag = true;
    seen[1] = 1;
    while(!nodes.empty()) {
        vector<int> next_nodes;
        for(auto node: nodes) {
            if (one_flag) {
                blues.pb(node);
            } else {
                reds.pb(node);
            }
            for(auto nei: edges[node]) {
                if (!seen[nei]) {
                    next_nodes.pb(nei);
                    seen[nei] = true;
                }
            }
        }
        one_flag = !one_flag;
        nodes = next_nodes;
    }

    // 赤色の頂点が N/3 個以下のとき
    // 赤色の頂点に3, 6, 9, ...を割り当てていく
    if (SIZE(reds) <= N / 3) {
        vector<int> used(N + 1);
        int i = 3;
        for (auto red : reds) {
            ans[red] = i;
            used[i] = 1;
            i += 3;
        }
        i = 1;
        for (auto blue : blues) {
            while (used[i]) i++;
            ans[blue] = i;
            used[i] = 1;
        }
        return ans;
    }
    // 青色の頂点が N/3 個以下のとき
    // 青色の頂点に3, 6, 9, ...を割り当てていく
    else if (SIZE(blues) <= N / 3) {
        vector<int> used(N + 1);
        int i = 3;
        for (auto blue : blues) {
            ans[blue] = i;
            used[i] = 1;
            i += 3;
        }
        i = 1;
        for (auto red : reds) {
            while (used[i]) i++;
            ans[red] = i;
            used[i] = 1;
        }
        return ans;
    }
    // 赤色の頂点も青色の頂点も N/3 個より多いとき
    else {
        // 赤色の頂点に 3 で割って 2 余る整数を、
        // 青色の頂点に 3 で割って 1 余る整数を順に割り当てていき、
        // 残った頂点に 3 の倍数を割り当てる

        int mod0 = 0;
        int mod1 = 0;
        int mod2 = 0;
        FOR(i, 1, N + 1) {
            if (i % 3 == 0) ++mod0;
            else if (i % 3 == 1) ++mod1;
            else ++mod2;
        }

        vector<int> zeros;
        while (SIZE(blues) > mod1) {
            zeros.pb(blues.back());
            blues.pop_back();
        }
        while (SIZE(reds) > mod2) {
            zeros.pb(reds.back());
            reds.pop_back();

        }

        int i = 3;
        for (auto z : zeros) {
            ans[z] = i;
            i += 3;
        }
        i = 1;
        for (auto o : blues) {
            ans[o] = i;
            i += 3;
        }
        i = 2;
        for (auto t : reds) {
            ans[t] = i;
            i += 3;
        }
        return ans;
    }
}

int main(void)
{
     //// for debug
     //{
     //    while(1) {
     //        int N = rand() % 10 + 2;
     //        vector<pair<int, int>> ABs;
     //        Dijkstra<int> dij(N);
     //        FOR(n, 2, N + 1) {
     //            int v = (rand() % (n - 1)) + 1;
     //            ABs.pb(mp(n, v));
     //            cout << "edge: " << n << " " << v << endl;
     //            dij.add_undir_edge(n - 1, v - 1, 1);
     //        }
     //        auto ans = solve(N, ABs);

     //        //// 検算
     //        //cout << "ans: ";
     //        //FOR(i, 1, N + 1) {
     //        //    cout << " " << ans[i];
     //        //}
     //        //cout << endl;

     //        REP(a, N) {
     //            auto dist = dij.shortest_path(a);
     //            REP(b, N) {
     //                if (a == b) continue;
     //                if (dist[b] == 3) {
     //                    if (ans.empty()) {
     //                        cout << "error! ans = -1" << endl;
     //                        return 0;
     //                        break;
     //                    }

     //                    int val1 = ans[a + 1];
     //                    int val2 = ans[b + 1];
     //                    if ((val1 + val2) % 3 == 0 || (val1 * val2) % 3 == 0) continue;

     //                    cout << "error!" << endl;
     //                    cout << "v" << (a + 1) << " and v" << (b + 1) << " fail" << endl;
     //                    return 0;
     //                }
     //            }
     //        }

     //        cout << endl;
     //    }
     //}

    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<pair<int, int>> ABs(N-1);

    REP(n, N - 1) {
        int a, b;
        cin >> a >> b;
        ABs[n] = mp(a, b);
    }

    auto ans = solve(N, ABs);
    if (SIZE(ans) == 0) {
        cout << -1 << endl;
    }
    else {
        FOR(i, 1, N + 1) {
            if (i != 1) cout << " ";
            cout << ans[i];
        }
        cout << endl;
    }

    
    return 0;
}
