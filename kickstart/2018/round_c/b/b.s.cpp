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

void solve() {
    int N;
    cin >> N;
    vector<vector<int>> cells(N);
    REP(n, N) {
        cells[n].resize(N);
        REP(m, N) {
            cin >> cells[n][m];
        }
    }
    vector<pair<int,int>> edges;
    REP(n1, N-1) {
        FOR(n2, n1+1, N) {
            edges.pb(mp(n1, n2));
        }
    }
    int len = SIZE(edges);

    vector<int> shff(len);
    REP(i, 3) shff[i] = 1;
    sort(ALL(shff));

    int ans = 0;
    do {
        vector<int> used(len);
        bool ok = true;
        vector<int> triangle_edges;
        REP(i, len) {
            if (shff[i]) {
                auto edge = edges[i];
                auto x = edge.first;
                auto y = edge.second;
                if (cells[x][y] == 0 || used[x] || used[y]) {
                    ok = false;
                    break;
                }
                used[x] = 1;
                used[y] = 1;
                triangle_edges.pb(cells[x][y]);
            }
        }
        if (ok) {
            sort(ALL(triangle_edges));
            if (triangle_edges[0] + triangle_edges[1] > triangle_edges[2]) {
                ++ans;
            }
        }
    }while(next_permutation(ALL(shff)));
    cout << ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
