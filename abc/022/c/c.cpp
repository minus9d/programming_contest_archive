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

typedef pair<int, int> P;
    
int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;

    vector<map<int,int>> edges(N+1);

    REP(m, M) {
        int u, v, l;
        cin >> u >> v >> l;
        edges[u][v] = l;
        edges[v][u] = l;
    }

    // 家1と繋がる各家vでループ
    // 家vから、家1と家vを直接繋ぐ道を使わずに家1にたどり着けるか試す
    const int INF = 1e9;
    int ret = INF;
    for (auto nei : edges[1]) {
        auto start_v = nei.first;
        auto cost = nei.second;

        vector<int> shortest(N+1, INF);
        shortest[start_v] = cost;

        priority_queue<P, vector<P>, greater<P>> que;
        que.push(P(cost, start_v));
        int len = 0;
        while(!que.empty()) {
            auto p = que.top();
            que.pop();

            auto cost = p.first;
            auto v = p.second;

            //cout << "popped: cost, v = " << cost << ", " << v << endl;

            if (v == 1) {
                ret = min(ret, cost);
                break;
            }

            for(auto &to : edges[v]) {
                auto to_v = to.first;
                auto to_len = to.second;

                if (to_v == 1 && v == start_v) continue;
            
                if (shortest[to_v] > shortest[v] + to_len) {
                    shortest[to_v] = shortest[v] + to_len;
                    que.push(P(shortest[to_v], to_v));
                }
            }
        }
    }

    if (ret == INF) cout << -1 << endl;
    else cout << ret << endl;
    
    return 0;
}
