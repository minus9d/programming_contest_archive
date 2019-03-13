// 自力で回答
// (もしかすると大昔にSRMで類題を解いたかもしれない)
// 
// XORの性質からg(N) = 1 ^ 2 ^ ... ^ Nを計算できれば
// f(A, B) = g(B) - g(A - 1)であるので、g(x)を求めればよい
//
// 数値を書き下してみる
//　 10進   2進   xor累計
//     0  0000    0000
//     1  0001    0001
//     2  0010    0011
//     3  0011    0000
//     4  0100    0100
//     5  0101    0001
//     6  0110    0111
//     7  0111    0000
// 各桁の周期性を利用して1の数を数えることでxorの結果がわかる
// ただし、一番左の桁だけ特殊なので場合分けして特別扱いする

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

// 0からnまでのXORを取った結果を返す
ll xor_to_n(ll n) {
    ll digit = 0;
    ll v = 2;
    ll ret = 0;
    while (v <= n * 10) {
        if (v == 2) {
            auto n2 = n % 4;
            ret |= (n2 == 1 || n2 == 2);
        } else {
            auto mod_v = n % v;
            if (mod_v >= v / 2) {
                ll one_num = mod_v - (v / 2) + 1;
                if (one_num % 2) {
                    ret |= (1LL << digit);
                }
            }
        }
        v *= 2;
        ++digit;
    }
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll A, B;
    cin >> A >> B;
    cout << (xor_to_n(B) ^ xor_to_n(A - 1)) << endl;
    return 0;
}
