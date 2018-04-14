// 問題
//   グリッド状にワッフルが配置される。そのうちのいくつかにはチョコチップが入っている。
//   水平カット、垂直カットの数が与えられる。チョコチップの数が均等になるよう
//   ワッフルを分割することはできるか。
// 解法
//   水平カット、垂直カットともに、空白行や空白列を除けば、切り方は一意に定まる。
//   切り方を決定したあと、各領域に、等しい数のチョコチップが入っているかを調べる


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

void solve() {
    int R, C, H, V;
    cin >> R >> C >> H >> V;
    vector<string> cells(R);

    int num = 0;
    REP(r, R) {
        cin >> cells[r];
        REP(c, C) {
            num += (cells[r][c] == '@');
        }
    }
    int div = (H + 1) * (V + 1);
    if (num % div) {
        cout << "IMPOSSIBLE";
        return;
    }

    // hor
    int cum = 0;
    int should = num / (H + 1);
    vector<int> uptoH;
    REP(r, R) {
        REP(c, C) cum += (cells[r][c] == '@');
        if (cum > should) {
            cout << "IMPOSSIBLE";
            return;
        }
        else if (cum == should) {
            cum = 0;
            uptoH.pb(r);
        }
    }

    // ver
    cum = 0;
    should = num / (V + 1);
    vector<int> uptoV;
    REP(c, C) {
        REP(r, R) cum += (cells[r][c] == '@');
        if (cum > should) {
            cout << "IMPOSSIBLE";
            return;
        }
        else if (cum == should) {
            cum = 0;
            uptoV.pb(c);
        }
    }

    should = num / ((H + 1) * (V + 1));
    int startH = 0;
    for (auto h : uptoH) {
        int startV = 0;
        for (auto v : uptoV) {
            int sum = 0;
            FOR(j, startH, h + 1) {
                FOR(i, startV, v + 1) {
                    sum += (cells[j][i] == '@');
                }
            }
            if (sum != should) {
                cout << "IMPOSSIBLE";
                return;
            }
            startV = v + 1;
        }
        startH = h + 1;
    }

    cout << "POSSIBLE";
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
