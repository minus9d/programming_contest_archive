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

int main(void)
{
    cin.sync_with_stdio(false);
    int H,W;
    cin >> H >> W;

    vector<vector<int>> cell(H, vector<int>(W));
    REP(h,H) REP(w,W) {
        char ch;
        cin >> ch;
        cell[h][w] = ch - '0';
    }

    vector<vector<int>> ans(H, vector<int>(W));
    REP(h,H) {
        if (h == 0 || h == H-1) continue;
        if (h == 1) {
            FOR(w,1,W-1) ans[h][w] = cell[h-1][w];
        }
        else {
            FOR(w,1,W-1) ans[h][w] = cell[h-1][w] - ans[h-1][w-1] - ans[h-1][w+1] - ans[h-2][w];
        }
    }

    REP(h,H) {
        REP(w,W) cout << ans[h][w];
        cout << endl;
    }
    

    return 0;
}
