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

int H, W;
vector<string> cells;

// ll func2(int x, int y, int dx, int dy) {
//     int x2 = x;
//     int y2 = y;
//     ll cnt = 0;
//     while(1) {
//         x2 += dx;
//         y2 += dy;
//         if (x2 < 0 || x2 >= W || y2 < 0 || y2 >= H || cells[y2][x2] == '#') break;
//         ++cnt;
//     }
//     return cnt;
// }


// ll func(int x, int y, int dx1, int dy1,
//          int dx2, int dy2) {
//     return func2(x, y, dx1, dy1) * func2(x, y, dx2, dy2);
// }

vector<vector<int>> to_l;
vector<vector<int>> to_r;
vector<vector<int>> to_u;
vector<vector<int>> to_d;

void fillup(vector<vector<int>> &to_dir, int y, int x, int dx, int dy) {
    int x2 = x;
    int y2 = y;
    ll cnt = 0;
    while(1) {
        x2 += dx;
        y2 += dy;
        if (x2 < 0 || x2 >= W || y2 < 0 || y2 >= H || cells[y2][x2] == '#') break;
        to_dir[y2][x2] = cnt;
        ++cnt;
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> H >> W;

    vector<string> tmp_cells(H);
    REP(h, H) cin >> tmp_cells[h];

    // 盤の周りを壁に
    cells.resize(H + 2);
    REP(h, H + 2) {
        if (h == 0 || h == H + 1) {
            cells[h] = string(W + 2, '#');
        }
        else {
            cells[h] = "#" + tmp_cells[h-1] + "#";
        }
    }
    H += 2;
    W += 2;
    //REP(h, H) cout << cells[h] << endl;

    to_l.resize(H, vector<int>(W));
    to_r.resize(H, vector<int>(W));
    to_u.resize(H, vector<int>(W));
    to_d.resize(H, vector<int>(W));

    REP(h, H) cin >> cells[h];

    REP(h, H) {
        REP(w, W) {
            if (cells[h][w] == '#') {
                fillup(to_l, h, w, 1, 0);
                fillup(to_r, h, w, -1, 0);
                fillup(to_u, h, w, 0, 1);
                fillup(to_d, h, w, 0, -1);
            }
        }
    }

    ll ans = 0;
    REP(h, H) {
        REP(w, W) {
            if (cells[h][w] == '.') {
                // ans += func(w, h, -1, 0, 0, 1);
                // ans += func(w, h, 0, -1, -1, 0);
                // ans += func(w, h, 1, 0, 0, -1);
                // ans += func(w, h, 0, 1, 1, 0);
                ans += to_l[h][w] * to_d[h][w];
                ans += to_u[h][w] * to_l[h][w];
                ans += to_r[h][w] * to_u[h][w];
                ans += to_d[h][w] * to_r[h][w];
            }
        }
    }
    cout << ans << endl;
    return 0;
}
