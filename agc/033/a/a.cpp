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

int main(void)
{
    cin.sync_with_stdio(false);
    int H, W;
    cin >> H >> W;
    vector<string> cells(H);
    REP(h, H) cin >> cells[h];
    
    // <x,y>
    vector<vector<int>> seen(H, vector<int>(W));
    vector<pair<int,int>> blacks;
    REP(h, H) {
        REP(w, W) {
            if (cells[h][w] == '#') {
                blacks.pb(mp(w, h));
                seen[h][w] = 1;
            }
        }
    }

    int dy[] = {0, 0, 1, -1};
    int dx[] = {1, -1, 0, 0};
    int ans = 1;
    while(1) {
        // cout << "====" << endl;
        // REP(h, H) {
        //     REP(w, W) cout << seen[h][w] << " ";
        //     cout << endl;
        // }
        // cout << endl;

        vector<pair<int,int>> next;
        for(auto xy: blacks) {
            auto x = xy.first;
            auto y = xy.second;
            REP(d, 4) {
                auto x2 = x + dx[d];
                auto y2 = y + dy[d];
                if (x2 < 0 || x2 >= W || y2 < 0 || y2 >= H) continue;
                if (seen[y2][x2]) continue;
                
                next.pb(mp(x2, y2));
                seen[y2][x2] = ans + 1;
            }
        }

        if (SIZE(next) == 0) break;
        blacks = next;
        
        ++ans;
    }
    cout << ans - 1 << endl;

    return 0;
}
