// 本番中に正しい考え方に辿り着けたがバグが取れず
// 本番後に自力AC
//
// AとBのbitが異なる数が奇数のときのみかならず経路が存在しそうな気がする
// ググって見つけた https://en.wikipedia.org/wiki/Hypercube_graph の
// Hamiltonicityの項でそれを確認
// ここの"reduction"という言葉をヒントに、以下のような操作を考えた
//
// 例: 0000 -> 0111 と移動する場合
//     ビットが異なる位置に着目。例えば下から3ビット目は
//        0[0]00 -> 0[1]11 とビットが異なる。
//     
//     0[0]00からはじまり、下から3ビット目が0であるような数字を全部
//     通って、適当な数字、例えば 0[0]01 にたどり着くことを考える。
//     （ただし、都合上、適当な数字は 0[0]11 以外であるものとする）
//
//     ここで、0[0]00から0[0]01にすべての頂点を使ってたどり着く問題は、
//     000から001にすべての頂点を使ってたどり着く問題と全く同じ。
//     よって分割統治により解ける。
//
//     そして、0[0]01 から 0[1]01へと移動したあと、
//     下から3ビット目が1であるようなパスを全部通って、
//     0[1]11へとたどり着く。
//
//     これもさきほどと同様。0[1]01から0[1]11へとたどり着く問題は、
//     001から011にすべての頂点を使ってたどり着く問題と全く同じで、
//     分割統治により解ける。



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


const int BIT_MAX = 17;

bool nth_bit_differs(int a, int b, int n) {
    return (a & (1 << n)) != (b & (1 << n));
}

void insert_bit(vector<int>& arr, int idx, int num) {
    int mul = 1;
    while (idx > 0) {
        mul *= 2;
        --idx;
    }
    for(auto& e: arr) {
        e = ((e / mul) * mul * 2) + (num * mul) + (e % mul);
    }
}

vector<int> solve(int from, int to, int N) {
    if (N == 1) {
        vector<int> ret{from, to};
        return ret;
    } else {


        // from(e.g. 0000)  と to (e.g. 0111) のうち
        // 値が異なる桁の位置を n とする
        // (例えば n = 2のとき 0[0]00 ,  0[1]11)
        int n = -1;
        REP(n_, N) {
            if (nth_bit_differs(from, to, n_)) {
                n = n_;
            }
        }

        // fromから桁nを飛ばした値を new_from ( e.g. 000 )、
        //   toから桁nを飛ばした値を new_to   ( e.g. 011 )と呼ぶ
        int new_from = 0;
        int new_to = 0;
        int cnt = 0;
        REP(n2, N) {
            if (n != n2) {
                new_from += (1 << cnt) * ((from & (1 << n2)) > 0);
                new_to += (1 << cnt) * ((to & (1 << n2)) > 0);
                ++cnt;
            }
        }

        // from(0[0]00) から to(0[1]11)に行く問題を、
        // new_from(000)からmid(100)に行く小問題と
        // mid(100)からnew_to(011)に行く小問題とに分割してそれぞれ解く
        // ここで mid は new_toと同じにならないように適当に決める必要がある
        //
        // 小問題が解けたあとは、もともとのnビット目から抜いた0と1とを再び戻す
        REP(n2, N) {
            int mid = new_from;
            mid ^= (1 << n2);
            if (mid != new_to) {
                auto ret1 = solve(new_from, mid, N - 1);
                auto ret2 = solve(mid, new_to, N - 1);
                insert_bit(ret1, n, (from & (1 << n)) > 0  );
                insert_bit(ret2, n, (to & (1 << n)) > 0 );

                for(auto e: ret2) ret1.push_back(e);
                return ret1;
            }
        }
    }
}

// デバッグ用
void print_vec(vector<int> vec) {
    auto size = SIZE(vec);
    REP(n, size) {
        if (n == 0) cout << vec[n];
        else cout << " " << vec[n];
    }
    cout << endl;
}

// デバッグ用
bool check(vector<int>& ans, int from, int to, int N) {
    auto size = SIZE(ans);
    REP(i, size - 1) {
        int n1 = ans[i];
        int n2 = ans[i + 1];
        int diff = 0;
        REP(n, N) {
            diff += (n1 & (1 << n)) != (n2 & (1 << n));
        }
        if (diff != 1) return false;
    }
    if (ans[0] != from) return false;
    if (ans.back() != to) return false;

    return true;
}

int main(void)
{
    cin.sync_with_stdio(false);

    // デバッグ用
    //print_vec(solve(0, 1, 1));
    //print_vec(solve(1, 0, 1));
    //print_vec(solve(0, 1, 2));
    //print_vec(solve(1, 0, 2));
    //print_vec(solve(0, 2, 2));
    //print_vec(solve(2, 0, 2));
    //print_vec(solve(1, 3, 2));
    //print_vec(solve(3, 1, 2));
    //print_vec(solve(2, 3, 2));
    //print_vec(solve(3, 2, 2));
    //print_vec(solve(0, 1, 3));
    //print_vec(solve(0, 2, 3));0
    //print_vec(solve(0, 7, 4));
    //// 途中まで0スタートの全通りを確かめる
    //FOR(N, 2, 10) {
    //    FOR(to, 1, (1 << N)) {
    //        int differ = 0;
    //        int A = 0;
    //        int B = to;
    //        REP(n, N) {
    //            differ += (A & (1 << n)) != (B & (1 << n));
    //        }
    //        if (differ % 2 == 0) {
    //            continue;
    //        }
    //        auto ans = solve(0, to, N);
    //        auto res = check(ans, 0, to, N);
    //        if (!res) {
    //            cout << "error!" << endl;
    //        }
    //    }
    //}

    ll N, A, B;
    cin >> N >> A >> B;

    int differ = 0;
    REP(n, N) {
        differ += (A & (1 << n)) != (B & (1 << n));
    }
    if (differ % 2 == 0) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        print_vec(solve(A, B, N));
    }

    return 0;
}
