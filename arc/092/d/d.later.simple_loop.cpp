// 愚直に2重ループ
//
//   https://kimiyuki.net/writeup/algo/atcoder/arc-092-d/
// で紹介されている
//   https://atcoder.jp/contests/arc092/submissions/2242270
//   https://atcoder.jp/contests/arc092/submissions/2251371
// を参考に、
//   #pragma GCC optimize ("-O3", "unroll-loops")
//   __attribute__((target("avx")))
// を指定した。これで3秒以内に間に合った (2907ms)。
// ("avx2"の指定だとRE)
//
// さらに追加で、アラインメントを保証してメモリ確保した（このコード）。しかし2952msと逆に遅くなった
// (参考: https://stackoverflow.com/questions/15067119/how-can-i-use-simd-to-accelerate-xor-two-blocks-of-memory)

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


#pragma GCC optimize ("-O3", "unroll-loops")

__attribute__((target("avx"))) int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    scanf("%d", &N);

    int* As = (int*)aligned_alloc(128, N * 4);
    int* Bs = (int*)aligned_alloc(128, N * 4);

    REP(n, N) scanf("%d", &As[n]);
    REP(n, N) scanf("%d", &Bs[n]);

    int ans = 0;
    int i = 0;
    for( ; i < (N / 8) * 8; i += 8) {
        int a0 = As[i];
        int a1 = As[i + 1];
        int a2 = As[i + 2];
        int a3 = As[i + 3];
        int a4 = As[i + 4];
        int a5 = As[i + 5];
        int a6 = As[i + 6];
        int a7 = As[i + 7];
        for(int j = 0; j < N; j++) {
            int b = Bs[j];
            ans ^= a0 + b;
            ans ^= a1 + b;
            ans ^= a2 + b;
            ans ^= a3 + b;
            ans ^= a4 + b;
            ans ^= a5 + b;
            ans ^= a6 + b;
            ans ^= a7 + b;
        }
    }
    for( ; i < N; i++) {
        int a = As[i];
        for(int j = 0; j < N; j++) {
            ans ^= a + Bs[j];
        }
    }
    cout << ans << endl;
    free(As);
    free(Bs);
    return 0;
}
