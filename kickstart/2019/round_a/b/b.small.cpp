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


int simulate(vector<string>& cells, int H, int W) {
    int ans = 0;
    REP(h, H) {
        REP(w, W) {
            int min_dist = 1e9;
            REP(h2, H) {
                REP(w2, W) {
                    if (cells[h2][w2] == '1') {
                        auto dist = abs(h2 - h) + abs(w2 - w);
                        min_dist = min(min_dist, dist);
                    }
                }
            }
            ans = max(ans, min_dist);
        }
    }
    return ans;
}

int solve_slow(vector<string>& cells, int H, int W) {
    int ans = 1e9;
    REP(h, H) {
        REP(w, W) {
            char old = cells[h][w];
            cells[h][w] = '1';
            ans = min(ans, simulate(cells, H, W));
            cells[h][w] = old;
        }
    }
    return ans;
}


void solve() {
    int H, W;
    cin >> H >> W;
    vector<string> cells(H);
    REP(h, H) cin >> cells[h];
    cout << solve_slow(cells, H, W);
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
