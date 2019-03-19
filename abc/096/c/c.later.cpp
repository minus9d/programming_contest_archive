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
    REP(h, H) {
        cin >> cells[h];
    }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    bool ans = true;
    REP(h, H) {
        REP(w, W) {
            if (cells[h][w] == '#') {
                bool ok = false;
                REP(d, 4) {
                    int h2 = h + dy[d];
                    int w2 = w + dx[d];
                    if (0 <= h2 && h2 < H && 0 <= w2 && w2 < W) {
                        ok |= cells[h2][w2] == '#';
                    }
                }
                if (!ok) ans = false;
            }
        }
    }
    if (ans) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
