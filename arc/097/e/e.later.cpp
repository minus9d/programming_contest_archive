// DP
// dp[i][j] で、黒のiまではソート済、白のjまではソート済というふうにしてDP
//
// 最初
//       B1 W2 B3 W1 W3 B2
// である。ここから左の方に数字の小さいボールを寄せていく。
// 以下、ソート済みの領域と、それ以外の領域とを '|' で分ける。
//
// dp[1][0] は、B1を左に持ってくる最低スワップ数。ここでは0。
//       B1 | W2 B3 W1 W3 B2
//
// dp[0][1] は、W1を左に持ってくる最低スワップ数。ここでは3。
//       W1 | B1 W2 B3 W3 B2
//
// dp[1][1] は、dp[1][0]からW1を左に持ってくるか、
//              dp[0][1]からB1を左に持ってくるか、のうち、良い方。
// 前者の場合、
//       B1 | W2 B3 W1 W3 B2
// からW1を
//       B1 W1 | W2 B3 W3 B2
// とするのが最短。
//
// このとき、W1を左に寄せる手数は、あらかじめテーブルを作ることで
// 高速に計算する。例えば以下の状態でB3を左に持っていく場合の手数を考える。
//       B1 W1 B2 | W2 B3 W3
// まず、初期状態でB3を左端に持っていく手数は、初期状態のB3の位置から2とわかる。
// ただし、ソート済のボール{B1, W1, B2}のうち、初期状態でB3よりも左にあったボールの分だけ、
// 必要な手数が少なくなるので、その分を引く。この場合、初期状態でB3より左にあったのはB1の1個なので、
// 2から1を引いて、1。
//
//
// 本番でも考え方は合っていたが時間が足りなかった



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

ll dp[2010][2010];
ll INF = 1e18;

// ボールiのある位置
int white_pos[2010];
int black_pos[2010];

// [i][j]: 位置jより左側にある、i以下の小さいボールの数
int white_table[2001][4000];
int black_table[2001][4000];

int main(void)
{
    cin.sync_with_stdio(false);
    int N; cin >> N;

    REP(n, 2*N) {
        char c; int a;   // a は 1-based   座標 は 0-based
        cin >> c >> a;
        if (c == 'B') {
            black_pos[a] = n;
            FOR(m, n + 1, 2 * N) {
                black_table[a][m] = 1;
            }
        }
        else {
            white_pos[a] = n;
            FOR(m, n + 1, 2 * N) {
                white_table[a][m] = 1;
            }
        }
    }

    FOR(a, 2, N + 1) {
        REP(n, 2 * N) {
            black_table[a][n] += black_table[a - 1][n];
            white_table[a][n] += white_table[a - 1][n];
        }
    }

    // dp[black][white]
    FOR(sum, 1, N*2+1) {
        REP(black, sum + 1) {
            if (black > N) break;
            auto white = sum - black;
            if (white > N) continue;

            dp[black][white] = INF;

            if (white > 0) {
                dp[black][white] =
                    min(dp[black][white],
                        // 白 white を先頭にもってくる。
                        dp[black][white - 1]
                        + white_pos[white]
                        - white_table[white - 1][white_pos[white]]
                        - black_table[black][white_pos[white]]
                    );
            }
            if (black > 0) {
                dp[black][white] =
                    min(dp[black][white],
                        // 黒 black を先頭にもってくる。
                        dp[black - 1][white]
                        + black_pos[black]
                        - black_table[black - 1][black_pos[black]]
                        - white_table[white][black_pos[black]]
                    );
            }
        }
    }
    cout << dp[N][N] << endl;
    return 0;
}
