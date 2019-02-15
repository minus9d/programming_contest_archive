// 公式PDFと https://pitsbuffersolution.com/compro/atcoder/arc089d.php
// を見て回答
//
// まず白点, 黒点をmod 2Kで考えられるところまではわかる。
// 白点をちょうどK下にずらすとそこはかならずマス目の色が入れ替わるので、
// この位置に黒点があるのと等価にできる。
//
// 累積和は、盤面を縦・横2倍に広げて作成しておくと計算が簡単

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

#define pb push_back
#define mp make_pair
#define mt make_tuple

vector<vector<int>> make_2d_sum(vector<vector<int>>& cells) {
    int size = SIZE(cells);
    vector<vector<int>> ret(size, vector<int>(size));
    REP(j, size) {
        REP(i, size) {
            ret[j][i] += cells[j][i];
            if (i != 0) ret[j][i] += ret[j][i - 1];
        }
    }
    FOR(j, 1, size) {
        REP(i, size) {
            ret[j][i] += ret[j - 1][i];
        }
    }

    return ret;
}

int count(vector<vector<int>>& blacks, int y, int x, int y2, int x2) {
    return blacks[y2][x2] + blacks[y - 1][x - 1]
        - blacks[y - 1][x2] - blacks[y2][x - 1];
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N, K;
    cin >> N;
    cin >> K;

    // 計算を簡単にするため広めにとっておく
    vector<vector<int>> blacks(4 * K, vector<int>(4 * K));
    REP(n, N) {
        int x, y; char c;
        cin >> x >> y >> c;
        if (c == 'W') y += K;
        x %= (K * 2); y %= (K * 2);
        ++blacks[y][x];
        ++blacks[y][x + 2 * K];
        ++blacks[y + 2 * K][x];
        ++blacks[y + 2 * K][x + 2 * K];
    }
    // 2次元累積和
    auto black_sums = make_2d_sum(blacks);

    // auto s = SIZE(black_sums);
    // REP(j, s) {
    //     REP(i, s) {
    //         cout << blacks[j][i] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // REP(j, s) {
    //     REP(i, s) {
    //         cout << black_sums[j][i] << " ";
    //         // cout << blacks[j][i] << " ";
    //     }
    //     cout << endl;
    // }

    int ans = 0;
    FOR(y, 1, 2 * K + 1) {
        FOR(x, 1, 2 * K + 1) {
            int score = 0;
            score += count(black_sums, y, x, y + K - 1, x + K - 1);
            score += count(black_sums, y + K, x + K, y + 2 * K - 1, x + 2 * K - 1);
            ans = max(ans, score);
        }
    }
    cout << ans << endl;
    return 0;
}
