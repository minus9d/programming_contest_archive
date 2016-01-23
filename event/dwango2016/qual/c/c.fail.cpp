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
#define mt make_tuple

int seen[30000];

// cur, line
int d_straight[300][300];
int d_sleep[300][300];


using info = tuple<int,int,int,int>;

// [from, [to, cost, line]]
map<int, vector<info>> roads;
vector< vector<int> > railways;
vector< vector<int> > costs;



int best = 1e9;

int getcost(int src, int dst, int line)
{
    auto& railway = railways[line];
    auto len = SIZE(railway);
    REP(i, len - 1) {
        if (railway[i] == src && railway[i + 1] == dst) {
            int ans = 0;
            FOR(j, i + 1, len - 1) {
                ans += costs[line][j];
            }
            ans = ans * 2 + costs[line][i];
            return ans;
        }
        else if (railway[i] == dst && railway[i + 1] == src) {
            int ans = 0;
            REP(j, i) ans += costs[line][j];
            ans = ans * 2 + costs[line][i];
            return ans;
        }
    }
}

int check(vector<info>& route) {
    //for(auto r: route) {
    //    cout << std::get<0>(r) << "->" << get<1>(r) << ",";
    //}
    //cout << endl;

    int len = SIZE(route);
    REP(sleep, len) {
        int ans = 0;
        REP(i, len) {
            int from = get<0>(route[i]);
            int to = get<1>(route[i]);


            if (i == sleep) {
                int line = get<3>(route[i]);
                ans += getcost(from, to, line);
            }
            else {
                ans += get<2>(route[i]);
            }
        }

        best = min(best, ans);
    }

    return 1;
}


int route[500];
void f(int cur, int prev, int dst, vector<info> route)
{
    if (cur == dst) {
        check(route);
    }
    else {
        for(auto nei: roads[cur]) {
            auto to = get<1>(nei);

            if (to == prev) continue;
            if (find(ALL(route), nei) == route.end()) {
                vector<info> route2(route);
                route2.pb(nei);
                f(to, cur, dst, route2);
            }
        }
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M, src, dst;
    cin >> N >> M >> src >> dst;

    railways.resize(M);
    costs.resize(M);

    REP(m,M) {
        int L;
        cin >> L;
        vector<int> ss(L);
        vector<int> ws(L-1);
        REP(l,L) cin >> ss[l];
        REP(l,L-1) cin >> ws[l];

        REP(l,L-1) {
            auto from = ss[l];
            auto to = ss[l+1];
            auto w = ws[l];
            roads[from].pb( mt(from, to, w, m) );
            roads[to].pb( mt(from, to, w, m) );
        }
    }

    vector<info> dummy;
    f(src, -1, dst, dummy);
    
    cout << best << endl;

    return 0;
}
