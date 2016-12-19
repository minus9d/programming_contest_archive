// 解説pdfの方針に沿った解答
// 参考： http://agc005.contest.atcoder.jp/submissions/904878

#define _CRT_SECURE_NO_WARNINGS

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
#include <climits>
using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

const int N = 1234567;

int pr[N]; // 数列のi番目の数値から左に辿り、最初により小さい数値があるindex
int ne[N]; // 数列のi番目の数値から右に辿り、最初により小さい数値があるindex
int pos[N];  // 数値xがある数列のindexを保持

int main() {
    int N;
    cin >> N;
    FOR(i, 1, N + 1) {
        int a;
        cin >> a;
        pos[a] = i;
    }
    REP(i, N+2) {
        pr[i] = i - 1;
        ne[i] = i + 1;
    }

    long long ans = 0;
    for (int i = N; i >= 1; i--) {
        // j: 数値iがある数列のindex
        int j = pos[i];
        // 数値i * 数値iが最小値となるような部分配列の数
        ans += i * 1LL * (j - pr[j]) * (ne[j] - j);

        // 例えば以下の数列で、今 数値i = 4, j = 5とする。
        //  数列 .. 3 7 8 4 9 2
        //   idx    2 3 4 5 6 7
        //  このとき、pr[5] = 2, ne[5] = 7。
        // 数値4を処理し終わった後は、数値4にとってのne, prを使ってテーブルを更新。
        // この場合、数値3にとってのneは、数値4にとってのneと等しくなる。
        // また、    数値2にとってのprは、数値4にとってのneと等しくなる。
        // 式で書くと ne[2] = ne[7], pr[7] = pr[7]となる。

        pr[ne[j]] = pr[j];
        ne[pr[j]] = ne[j];
    }
    cout << ans << endl;
    return 0;
}

