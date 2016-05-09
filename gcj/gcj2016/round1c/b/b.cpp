// ビル1からビルBまでのルートがちょうどM個となるようにスライドを張る

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>
#include <complex>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

void solve(void)
{
    ll B, M;
    cin >> B >> M;

    // x->yのスライドは常にx < yとなるように設置すると約束する
    // （スライドが無限ループを作ってはいけないためこのように約束できる）

    // すべてのビル間にスライドを設置したときが考えられるmax
    // これより大きいMは実現できない
    ll B2 = B-2;
    ll poss_mx = 1;
    while (B2) {
        poss_mx *= 2;
        --B2;
    }

    if (M > poss_mx) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    // それ以外であれば解があることが保証される
    cout << "POSSIBLE" << endl;

    // M <= B - 1の場合は自明な解が存在
    // 例えばB = 5, M = 3の場合、
    // 1 -> 5
    // 1 -> 2 -> 5
    // 1 -> 2 -> 3 -> 5
    // の3通りのルートがあるように解を出力
    if (M <= B - 1) {
        REP(b, B) {
            string s(B, '0');
            if (M > 0) {
                s[B - 1] = '1';
                --M;
            } 
            if (M > 0) {
                s[b + 1] = '1';
            }
            cout << s << endl;
        }
        return;
    }

    // M > Bの場合
    // まず基本としてB-1通りのルートは必ず確保するものとする。
    // 例えばB = 6の場合、以下の5通りのルートは必ず確保する。
    //   1 -> 6
    //   1 -> 2 -> 6
    //   1 -> 2 -> 3 -> 6
    //   1 -> 2 -> 3 -> 4 -> 6
    //   1 -> 2 -> 3 -> 4 -> 5 -> 6
    //
    // 次に、ビル5からビル4, 3, ..., ビル1の順に、追加で張るスライドをgreedyに決めていく。
    // 追加で張るスライドは、最低2だけ離れている必要がある。
    // table[i]には、ビルiを起点として、ビル6にたどり着くルートの数を保存しておく。
    //
    // まずビル5。ビル5からさらに張れるスライドは存在しない。
    // table[5] = 1となる。(5 -> 6しか存在しない)
    //
    // 次にビル4。同様に、ビル4からさらに張れるスライドは存在しない。
    // table[4] = 2となる。(4 -> 5 -> 6に加えて4 -> 6が新たに加わる)
    //
    // 次にビル3。ビル3から張れる可能性のあるスライドは、ビル5へのスライド。
    // もし3 -> 5とスライドを張った場合、table[3] = 1 + table[4] + table[5]となる
    // さらに、ビル1からビル6までたどり着くルートの最小数は、table[3] + (3 - 1)となる。
    // この最小数が、Mを超えなければ、このスライドを張る。
    // Mを超えるならば、スライドを張らない。
    // スライドを張らない場合、table[3] = 1 + table[4]となる
    //
    // 次のビル2も、ビル4, ビル5にスライドを張るかどうかをgreedyに決める。以下繰り返し。

    ll curr = 0;
    vector<ll> table(B + 1);
    vector<vector<int>> slides(B + 1, vector<int>(B + 1));

    // 基本で張るスライド
    FOR(b, 1, B) {
        slides[b][b + 1] = 1;
        slides[b][B] = 1;
    }

    B2 = B - 1;
    while (B2 >= 1) {
        ++curr;
        FOR(i, B2 + 2, B) {
            // もしビルB2からビルiまでスライドを張った場合に、ビル1からビルBまでたどり着くルートの最小数をcurr2に計算
            ll curr2 = curr + table[i];
            curr2 += (B2 - 1);

            // もしcurr2がMを超えない場合は、ビルB2からビルiまでスライドを張ることにする
            if (curr2 <= M) {
                slides[B2][i] = 1;
                curr += table[i];
            }
        }
        table[B2] = curr;
        --B2;
    }

    FOR(b1, 1, B + 1) {
        FOR(b2, 1, B + 1) {
            cout << slides[b1][b2];
        }
        cout << endl;
    }
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": ";
        solve();
    }

    return 0;
}
