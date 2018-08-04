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


int N, K;
#define CMAX 1010
ll memo[CMAX][CMAX];
int vis[CMAX][CMAX];
ll cmb(int d, int sm) {
    if (d < 0 or sm < 0) return 0;
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
void phase2(int d, int n) {
    printf("%d", n); N -= n;
    for(int dd = d - 1; dd >= 2; --dd) REP(nn, 10) {
        ll cnt = cmb(dd - 1, N - nn);
        if (cnt <= K) K -= cnt;
        else {
            printf("%d", nn);
            N -= nn;
            break;
        }
    }
    if(1 < d) printf("%d\n", N);
    else printf("\n");
}

int main() {
    cin >> N >> K;
    K--;

    FOR(d, 1, 1010) FOR(n, 1, 10) {
        ll cnt = cmb(d - 1, N - n);
        if (cnt <= K) K -= cnt;
        else {
            phase2(d, n);
            return 0;
        }
    }
}
