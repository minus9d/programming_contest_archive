#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <numeric>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>

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

struct EdgeTmp {
    ll to;
    ll color;
    ll cost;
};

struct Edge {
    ll to;
    ll cost;
};

vector<vector<EdgeTmp>> edgesTmp;

vector<vector<Edge>> edges;


map<ll, ll> to_newv;

ll idx = 0;
inline ll getNewV(ll v, ll color) {
    ll ret = -1;

    ll key = color * 50000 + v;

    auto found = to_newv.find(key);
    if (found == to_newv.end()) {
        to_newv[key] = idx;
        ret = idx;
        ++idx;
    }
    else
    {
        ret = found->second;
    }
    
    return ret;
}

ll getNextIdx() {
    return idx;
}

void addEdge(int v1, int v2, ll cost)
{
    edges[v1].push_back(Edge{ v2, cost });
    edges[v2].push_back(Edge{ v1, cost });
}

typedef pair<ll, ll> P; // minimum cost, vertex No.

int main(void)
{
    cin.sync_with_stdio(false);
    ll N,M;
    cin >> N >> M;

    edgesTmp.resize(N);

    REP(m,M) {
        ll a, b, c, t;
        cin >> a >> b >> c >> t;

        --a;
        --b;
        edgesTmp[a].pb( EdgeTmp{b, c, t} );
        edgesTmp[b].pb( EdgeTmp{a, c, t} );
    }

    edges.resize(80000 * 3);
    REP(v,N) {

        set<ll> colorsSet;
        for (auto e : edgesTmp[v]) {
            colorsSet.insert(e.color);
            ll fromNewV = getNewV(v, e.color);
            ll toNewV = getNewV(e.to, e.color);
            edges[fromNewV].push_back(Edge{ toNewV,e.cost });
        }

        vector<ll> colors(ALL(colorsSet));
        REP(i, SIZE(colors)-1)
        {
            FOR(j, i + 1, SIZE(colors))
            {
                ll v1 = getNewV(v, colors[i]);
                ll v2 = getNewV(v, colors[j]);
                addEdge(v1, v2, abs(colors[i] - colors[j]));
            }
        }
    }

    ll startV = getNextIdx();
    ll endV = startV + 1;

    // startV to ...
    set<ll> seenColor;
    for (auto e : edgesTmp[0]) {
        if (seenColor.count(e.color)) continue;
        ll toNewV = getNewV(0, e.color);
        addEdge(startV, toNewV, abs(1 - e.color));
        seenColor.insert(e.color);
    }
    seenColor.clear();

    // ... to endV
    for (auto e : edgesTmp[N-1]) {
        if (seenColor.count(e.color)) continue;
        ll toNewV = getNewV(N-1, e.color);
        addEdge(endV, toNewV, 0);
        seenColor.insert(e.color);
    }
    seenColor.clear();

    // dijkstra
    ll vNum = getNextIdx() + 2;
    vector<ll> shortest(vNum, LLONG_MAX);
    shortest[startV] = 0;
        
    priority_queue<P, vector<P>, greater<P> > que;
    que.push(P(0, startV));
    bool cont = true;
    while (!que.empty() && cont) {
        P p = que.top();
        que.pop();

        int v = p.second;
        if (shortest[v] < p.first) {
            continue;
        }

        for(auto& edge: edges[v])
        {
            if (shortest[edge.to] > shortest[v] + edge.cost) {
                shortest[edge.to] = shortest[v] + edge.cost;
                que.push(P(shortest[edge.to], edge.to));
                if (edge.to == endV) cont = false;
            }
        }
    }
    cout << shortest[endV] << endl;

    return 0;
}
