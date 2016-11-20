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

int H, W;

bool is_valid(int x, int y) {
    return 0 <= x && x <= W-1 && 0 <= y && y <= H-1;
}

int solve(const vector<vector<int>>& cells, int ini_x, int ini_y, int dx, int dy) {
    int x = ini_x;
    int y = ini_y;
    // int x1 = -1;
    // int y1 = -1;

    int ans = 0;
    bool found = false;
    while(is_valid(x, y)) {
        if(cells[y][x] == 1) {
            found = true;
            // x1 = x; y1 = y; break;
        }
        else {
            if (found) {
                ++ans;
            }
        }
        x += dx; y += dy;
    }
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> H >> W;
    vector<vector<int>> cells(H, vector<int>(W));
    REP(h,H) REP(w,W) cin >> cells[h][w];

    int ans = 0;
    REP(h,H) {
        ans += solve(cells, 0, h, 1, 0);
        ans += solve(cells, W-1, h, -1, 0);
    }
    REP(w,W) {
        ans += solve(cells, w, 0, 0, 1);
        ans += solve(cells, w, H-1, 0, -1);
    }
    cout << ans << endl;
    return 0;
}
