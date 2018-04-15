// 問題: H*Wのタイルが与えられる。タイルは綺麗か汚れているかのいずれか。
//       綺麗なタイルのみでできる最大の正方形の最大値を求める
// 解法: http://prdc.hatenablog.com/entry/2017/09/11/105211
//       dp[i][j]: 位置(i,j)から見て、左上に向かってできる最大の正方形の数

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

int largest_square(const int H, const int W, const vector<vector<int>>& cells) {
    vector<vector<int>> dp(H, vector<int>(W));
    REP(h, H) {
        REP(w, W) {
            auto val = cells[h][w];
            if (h == 0 || w == 0) {
                dp[h][w] = (val == 0);
            }
            else {
                if (val == 0) {
                    dp[h][w] = min(dp[h][w-1], min(dp[h-1][w], dp[h-1][w-1])) + 1;
                }
                else {
                    dp[h][w] = 0;
                }
            }
        }
    }
    int size = 0;
    REP(h, H) {
        REP(w, W) {
            size = max(size, dp[h][w]);
            // cout << dp[h][w] << " ";
        }
        // cout << endl;
    }
    return size * size;
}


int main() {
    int H, W;
    cin >> H >> W;

    vector<vector<int>> cells(H, vector<int>(W));
    REP(h, H) {
        REP(w, W) {
            cin >> cells[h][w];
        }
    }
    cout << largest_square(H, W, cells) << endl;
    return 0;
}
