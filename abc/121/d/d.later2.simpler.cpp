// 解説PDFを実装
// 自力で実装したd.later1.cppより大幅に簡単化
//
// nを偶数として n ^ (n + 1)は必ず1になることを利用すると
// 0からNまでのxorのうち序盤はほとんど1になり大幅に簡単化
//
// この性質に気付けなくても、実験すればmod4で法則があることには
// 気付けたはず

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
    auto mod4 = n % 4;
    if (mod4 == 1) {
        return 1;
    } else if (mod4 == 3) {
        return 0;
    } else if (mod4 == 2) {
        return n ^ 1;
    } else {
        return n;
    }
}


int main(void)
{
    cin.sync_with_stdio(false);
    ll A, B;
    cin >> A >> B;

    if (A == 0) {
        cout << xor_to_n(B) << endl;
    } else {
        cout << (xor_to_n(B) ^ xor_to_n(A - 1)) << endl;
    }

    return 0;
}
