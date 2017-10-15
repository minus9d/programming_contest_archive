#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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

const int INF = 1e9;

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<pair<int,int>> edges(M);
    REP(m, M) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        edges[m] = mp(a, b);
    }
    
    int ans = 0;
    REP(m, M) {
        vector<vector<int>> d(N, vector<int>(N, INF));
        REP(i, N) d[i][i] = 0;

        REP(m2, M) {
            if (m == m2) continue;
            int a, b;
            tie(a, b) = edges[m2];
            d[a][b] = d[b][a] = 1;
        }

        // Warshall Floyd
        REP(k, N){
            REP(i, N){
                REP(j, N){
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }

        bool bridge = false;
        REP(i, N){
            REP(j, N){
                if (d[i][j] == INF) {
                    bridge = true;
                }
            }
        }

        ans += bridge;
    }

    cout << ans << endl;

    return 0;
}
