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
 
int same_chars(string& s1, string& s2) {
    int ret = 0;
    auto mn = min(SIZE(s1), SIZE(s2));
    REP(i, mn) ret += (s1[i] == s2[i]);
    return ret;
}
 
 
map<pair<int, int>, int> cache;
 
int calc_cost(const vector<string>& cells, int w1, int w2, int h1, int h2)
{
    //if (cache.count(mp(h1, h2))) {
    //    return cache[mp(h1, h2)];
    //}
 
    int score = 0;
    while (h1 > 0 && h2 > 0) {
        score += cells[w1][h1 - 1] == cells[w2][h2 - 1];
        --h1; --h2;
    }
    //cache[mp(h1, h2)] = score;
    return score;
 
    //auto col1 = cells[w1].substr(0, h1);
    //auto col2 = cells[w2].substr(0, h2);
    //reverse(ALL(col1));
    //reverse(ALL(col2));
    //return same_chars(col1, col2);
}
 
int main(void)
{
    cin.sync_with_stdio(false);
    cin >> H >> W;
    vector<string> cells_ini(H);
    REP(h, H) cin >> cells_ini[h];
 
    vector<string> cells(W);
    REP(h, H) REP(w, W) {
        //cells[w] = cells_ini[h][w] + cells[w];
        cells[w] += cells_ini[h][w];
    }
 
    int ret = 0;
    REP(i, W - 1) {
        cache.clear();
        auto j = i + 1;
        int MAX = 1e9;
        vector<vector<int>> dp(H + 1, vector<int>(H + 1, MAX));
        dp[H][H] = 0;
        int remain = H * 2;
        while (remain >= 0) {
            REP(h1, remain + 1) {
                auto h2 = remain - h1;
                if (h1 > H || h2 > H) continue;
 
                // cand1
                if (h1 != H) {
                    auto prev_h1 = h1 + 1;
                    auto prev_h2 = h2;
                    auto score = dp[prev_h1][prev_h2] + calc_cost(cells, i, j, prev_h1, prev_h2);
                    dp[h1][h2] = min(dp[h1][h2], score);
                }
                if (h2 != H) {
                    auto prev_h1 = h1;
                    auto prev_h2 = h2 + 1;
                    auto score = dp[prev_h1][prev_h2] + calc_cost(cells, i, j, prev_h1, prev_h2);
                    dp[h1][h2] = min(dp[h1][h2], score);
                }
                //printf("dp[%d][%d] = %d\n", h1, h2, dp[h1][h2]);
            }
            --remain;
        }
        ret += dp[0][0];
        //cout << "----" << endl;
    }
    cout << ret << endl;
    return 0;
}
