// URL: https://kotamanegi.com/Problems/view/?page=72
// 問題: 桁和がNとなる数の中でK番目に小さい数を求める
// 参考： https://kotamanegi.com/Submission/view/index.php?SubmissionID=1755

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

#define CMAX 1010
ll memo[CMAX][CMAX];
int vis[CMAX][CMAX];

// 桁の数がd、各桁の合計がsmであるような場合の数を求める。
// ただし先頭が0になるのを許容する。
// 例: cmb(3, 2) は 002, 011, 020, 101, 110, 200なので6
ll cmb(int d, int sm) {
    if (d < 0 || sm < 0) return 0;
    if (d == 0) {
        if (sm == 0) return 1;
        else return 0;
    }
    if (vis[d][sm]) return memo[d][sm];

    ll res = 0;
    REP(i, 10) res += cmb(d - 1, sm - i);
    vis[d][sm] = 1;
    return memo[d][sm] = res;
}

// 桁数がちょうどd桁、かつ、最初がnである整数のうち、
// 全桁の合計がNで、かつ、K+1番目(?)の整数を表示
void phase2(int d, int n, int N, int K) {
    // 最初の文字はnで確定
    printf("%d", n); N -= n;
    // 2文字目以降を上の桁から順に確定していく
    // nYXXX  のYの部分を決めたい場合、dd=4
    for(int dd = d - 1; dd >= 2; --dd) {
        // Yに何が入るかを0から順番に試す
        REP(nn, 10) {
            ll cnt = cmb(dd - 1, N - nn);
            if (cnt <= K) K -= cnt;
            // Yに入る数字がnnで確定
            else {
                printf("%d", nn);
                N -= nn;
                break;
            }
        }
    }
    // 最後に残った数字が最後の桁
    if(1 < d) printf("%d\n", N);
    else printf("\n");
}

void solve(int N, int K) {
    K--;  // 1引いておく

    // dは桁数
    FOR(d, 1, 1010) {
        // 例えばd=3のとき、"1xx", "2xx"と順にループ
        FOR(n, 1, 10) {
            // 上の"xx"の部分の桁和がN-nになる場合の数を計算
            ll cnt = cmb(d - 1, N - n);
            if (cnt <= K) K -= cnt;
            else {
                // d桁で、phase2
                phase2(d, n, N, K);
                return;
            }
        }
    }
}


int main() {
    int N, K;
    cin >> N >> K;
    solve(N, K);
}
