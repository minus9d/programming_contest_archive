// 入力例3の K = 20, A = [2 3 4 10 10 25]の場合を考える
//
// 4 は、他のカードの組み合わせで16, 17, 18, 19が作れてしまう場合、
// 必要。それ以外の場合、不必要。
//
// この判定を高速に行うためには以下を行う
// 1. 4 以外のカードの組み合わせで作成可能な数字のリストの作成。K <= 5000なのでこれは簡単。
// 2. 累積和やセグメントツリーを使い、
//    「A以上B以下の数字を作成可能か」をO(1)で答えられるようにする
//
// ここまででsmallは解けたはず。
// largeの解き方がわからなかったので解説PDFを見る。
//
// 4がno needな場合3, 2もno needという単調性を利用して二分探索。



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

bool is_i_needed(ll N, ll K, vector<ll>& As, int i) {
    // 任意のカードの組み合わせで作成可能な数を列挙
    // ただしK未満
    bool flip = true;
    vector<vector<int>> possible(K, vector<int>(2));
    possible[0][flip] = 1;
    REP(j, N) {
        if (i == j) continue;
        flip = !flip;
        auto a = As[j];
        vector<int> added(K);
        REP(j, K) {
            if (possible[j][!flip]) {
                possible[j][flip] = 1;
            }
            if (possible[j][!flip] && (j + a) < K) {
                possible[j + a][flip] = 1;
            }
        }
    }

    FOR(j, max(0LL, K - As[i]), K) {
        if (possible[j][flip]) {
            return true;
        }
    }
    return false;
}


int main(void)
{
    cin.sync_with_stdio(false);
    ll N, K;
    cin >> N >> K;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];
    sort(ALL(As));

    // 単調性を利用
    // x: no need
    // o: need
    //
    // 1 3 4, K = 6
    // x o o
    //
    // 1 1 3 4 5, K = 400
    // x x x x x
    // この場合例外なので別途処理が必要
    //
    // 2 3 4 10 10 25, K = 6
    // x x x o  o  o
    //

    if (!is_i_needed(N, K, As, N - 1)) {
        cout << N << endl;
        return 0;
    }

    int lo = 0;
    int hi = N - 1;
    while (lo < hi) {
        auto k = (lo + hi) / 2;
        if (is_i_needed(N, K, As, k)) {
            hi = k;
        } else {
            lo = k + 1;
        }
    }

    cout << lo << endl;
    return 0;
}
