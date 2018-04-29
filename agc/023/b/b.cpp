#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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

int N;
vector<vector<char>> cells;

char convert(int w, int h) {

    //while (w >= N) w -= N;
    //while (h >= N) h -= N;
    //while (w <= -N) w += N;
    //while (h <= -N) h += N;

    auto x = (h + w) / 2;
    auto y = (h - w) / 2;

    while (x >= N) x-= N;
    while (y >= N) y -= N;
    while (x <= -N) x += N;
    while (y <= -N) y += N;

    // cout << "x, y = " << x << "," << y << endl;
    return cells[y][x];
}


ll faster() {
    int ans = 0;
    FOR(w, -N + 1, N) {
        auto h_start = abs(w);
        int diff = 0;

        REP(h_offset, N - abs(w)) {

            auto w1 = w;
            auto h1 = h_start + h_offset * 2;

            //cout << "=== w1, h1 = " << w1 << "," << h1 << endl;
            //cout << "  initialize" << endl;
            // 非対称性を崩す要素の数を数える
            if (h_offset == 0) {
                // (w, h_start)
                // 軸を中心とした左右
                FOR(i, 1, N) {
                    REP(j, N - i) {
                        diff += convert(w1 - i, h1 + i + 2 * j) != convert(w1 + i, h1 + i + 2 * j);
                    }
                }
            }

            ans += (diff == 0);

            //cout << "  for next" << endl;

            // 次のために要素を入れ替える
            if (h_offset != N - abs(w) - 1) {
                FOR(i, 1, N) {
                    diff -= convert(w1 - i, h1 + i) != convert(w1 + i, h1 + i);
                    diff += convert(w1 - i, h1 + i + 2 * N) != convert(w1 + i, h1 + i + 2 * N);
                }
            }
        }
    }
    return ans;
}


int main(void) {
    cin >> N;
    cells.resize(N);
    REP(n, N) cells[n].resize(N);
    REP(n1, N) REP(n2, N) cin >> cells[n1][n2];

    auto ans = faster();
    cout << ans << endl;

    return 0;
}
