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

const ll INF = 1e18;

// edge生成用
struct edge_element { ll from, to, cost; };
struct edge { ll to, cost; };
typedef pair<ll, ll> P; // <最短距離, 頂点番号>

// 頂点sから各頂点までの距離を計算してdに格納
void dijkstra(ll s, vector<vector<edge> >& G, vector<ll>& d)
{
    priority_queue<P, vector<P>, greater<P> > que;
    fill(ALL(d), INF);
    d[s] = 0;
    que.push(P(0, s));

    while (!que.empty()) {
        P p = que.top();
        que.pop();

        ll dist = p.first;
        ll v = p.second;
        if (d[v] < dist) continue;
        REP(i, G[v].size()) {
            edge e = G[v][i];
            if (d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}


int main(void)
{
    cin.sync_with_stdio(false);
    ll N, M, T;
    cin >> N >> M >> T;
    vector<ll> As(N);
    REP(n,N) cin >> As[n];
    vector<ll> as(M);
    vector<ll> bs(M);
    vector<ll> cs(M);
    REP(m,M) cin >> as[m] >> bs[m] >> cs[m];
    
    ll V = N;

    vector<vector<edge>> G1(V);
    vector<vector<edge>> G2(V);
    REP(m, M) {
        G1[as[m] - 1].pb(edge{ bs[m] - 1, cs[m] });
        G2[bs[m] - 1].pb(edge{ as[m] - 1, cs[m] });
    }

    vector<ll> d1(V);
    vector<ll> d2(V);
    dijkstra(0, G1, d1);
    dijkstra(0, G2, d2);
    ll best = 0;
    REP(i, V) {
        auto time1 = d1[i];
        auto time2 = d2[i];
        if (time1 == INF || time2 == INF) continue;
        if (time1 + time2 < T) {
            best = max(best, (T - (time1 + time2)) * As[i]);
        }
    }

    cout << best << endl;
    return 0;
}
