// 本番時、解説PDFと同様に考えられたが、オーバーフローでlargeがWA。
// 証明できていない箇所がある。
//
// [解法]
// 以下の場合を例にとって考える
//    |------*-----*-----*------*-----*------*-----*
//    0      a     b     c      d     e      f     g
// 原点から距離cの場所にあるゴミを、ゴミcと呼ぶことにする。
//
// ロボットがゴミ箱にゴミを捨てる回数をK回と固定して考える。例えばK=3とする。
// 
// このとき、
// 1回目のゴミ捨ては、「ゴミgまで行ってゴミgを拾い、ゴミa ~ dのどれかを拾いながら原点に戻る」
// 2回目のゴミ捨ては、「ゴミfまで行ってゴミgを拾い、ゴミa ~ dのどれかを拾いながら原点に戻る」
// 3回目のゴミ捨ては、「ゴミeまで行ってゴミgを拾い、ゴミa ~ dのどれかを拾いながら原点に戻る」
// のが最適となる。本番中も直感的にそう思ったが、証明できていない。解説pdfにも「明らか」としか書かれていない。
//
// 上記を信じると、ゴミを拾いに行く行きのコストは常に定数となる。
// したがって残りの問題は、「ゴミ捨てに行く3回のうち、ゴミa, b, c, dをどのタイミングで拾うか」
// を、帰りのコストが最小になるように決める問題となる。
//
// まずゴミa~cはないものとして、ゴミdについてついて考える。するとゴミdは3回のうち
// どのタイミングで拾っても、かかるコストは同じになることがわかる。よって1回目で拾うことにする。
//
// 次、ゴミcについて考える。選択肢として、1回目で拾うか、2回目で拾うかの2通りがある。
// (3回目に拾うのは、2回目に拾うのとコストが同じであるので考える必要がない)
// これは2回目に拾うのがよい。
// なぜなら、もし1回目で拾うと、ゴミbからゴミcまでの区間のコストが9になるのに対し、
// 2回目で拾うと、同区間のコストが4になるから。
//
// 同様に、遠くにあるゴミから順に、1回目のゴミ捨て、2回目のゴミ捨て、3回目のゴミ捨て、
// また最初に戻って1回目のゴミ捨て、...と拾うのが最適。
//
// この場合だと、
// 1回目のゴミ捨ては、「ゴミgまで行ってゴミgを拾い、ゴミd、ゴミaを拾いながら原点に戻る」
// 2回目のゴミ捨ては、「ゴミfまで行ってゴミgを拾い、ゴミcを拾いながら原点に戻る」
// 3回目のゴミ捨ては、「ゴミeまで行ってゴミgを拾い、ゴミbを拾いながら原点に戻る」
// が最適となる。
//
// 累積和を使うとこれを効率的に計算でき、largeが解ける。

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
    ll N, X;
    cin >> N >> X;
    vector<ll> Xs(N);
    REP(n, N) cin >> Xs[n];

    // 原点から遠い順に距離をソート
    auto Ys = Xs;
    reverse(ALL(Ys));

    // 累積和を計算
    vector<ll> Y_sum(N);
    Y_sum[0] = Ys[0];
    FOR(i, 1, N) Y_sum[i] = Y_sum[i - 1] + Ys[i];

    __int128 ans = 1e18;  // ★ 最終的な解は1e18以下に収まるのだが、他の解候補がlong long intの範囲を超えることが
                          // あるため、__int128を使う必要がある！！！
    FOR(k, 1, N + 1) { // ゴミ箱に行く回数をkとする

        // ★この変数がlong long intを超える!!
        // ゴミを捨てる回数に応じたコストをまず計算
        __int128 local_ans = X * k;

        // 距離dにあるゴミを取りに行くコストはd, 取ったあと帰るコストは2^2 * d = 4d。
        // よって足して5d。
        // k回のゴミ捨てで、原点から遠いゴミk個をそれぞれ取って帰るコストは、
        // 累積和を使って以下のように計算できる。
        local_ans += 5 * Y_sum[k-1];

        ll i = 2 * k - 1;
        ll n = 1;

        // まだ取っていないゴミのうち、遠くにあるゴミから順番にk個のゴミを、
        // k回のゴミ捨てでの帰路にそれぞれ1個ずつ取っていくところをシミュレート。
        // もともとn個のゴミを持って帰るところをn+1個のゴミを持って帰ることにすることで
        // 増えるコストは、((n+2)^2 - (n+1)^2 = 2n + 3)。
        while (i <= N - 1) {
            local_ans += (2LL * n + 3) * (Y_sum[i] - Y_sum[i - k]);
            n += 1;
            i += k;
        }
        // 端数処理
        local_ans += (2LL * n + 3) * (Y_sum[N - 1] - Y_sum[i - k]);

        ans = min(ans, local_ans);
    }

    // __int128は出力に失敗するのでllにキャストする
    ll ans2 = (ll)ans;
    // ゴミを拾うコストは常に定数なので最後に足す
    cout << (ans2 + N * X) << endl;

    return 0;
}
