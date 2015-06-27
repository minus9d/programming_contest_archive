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

vector<vector<int>> Bs(2, vector<int>(3));
vector<vector<int>> Cs(3, vector<int>(2));

pair<int,int> calc_pts(vector<vector<int>>& cell)
{
    int c = 0;
    int n = 0;
    REP(j,2) REP(i,3)
        if (cell[j][i] == cell[j+1][i]) c += Bs[j][i];
        else n += Bs[j][i];
    REP(j,3) REP(i,2)
        if (cell[j][i] == cell[j][i+1]) c += Cs[j][i];
        else n += Cs[j][i];
    return mp(c,n);
}

pair<int,int> dfs(vector<vector<int>>& cell, int t)
{
    if (t == 9) {
        REP(j,3) REP(i,3) if (cell[j][i] == 0) {
            cell[j][i] = 1;
            auto pts = calc_pts(cell);
            cell[j][i] = 0;
            return pts;
        }
    }
    // chokudai
    else if (t % 2) {
        auto mx = -1;
        pair<int,int> mx_ret;
        REP(j,3) REP(i,3) if (cell[j][i] == 0) {
            cell[j][i] = 1;
            auto pts = dfs(cell, t + 1);
            if (pts.first > mx) {
                mx = pts.first;
                mx_ret = pts;
            }
            cell[j][i] = 0;
        }
        return mx_ret;
    }
    else {
        auto mx = -1;
        pair<int,int> mx_ret;
        REP(j,3) REP(i,3) if (cell[j][i] == 0) {
            cell[j][i] = -1;
            auto pts = dfs(cell, t + 1);
            if (pts.second > mx) {
                mx = pts.second;
                mx_ret = pts;
            }
            cell[j][i] = 0;
        }
        return mx_ret;
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    REP(j,2) REP(i,3) cin >> Bs[j][i];
    REP(j,3) REP(i,2) cin >> Cs[j][i];

    vector<vector<int>> cell(3, vector<int>(3));

    auto points = dfs(cell, 1);

    cout << points.first << endl << points.second << endl;
    
    return 0;
}
