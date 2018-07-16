// 問題： https://agc026.contest.atcoder.jp/tasks/agc026_c
//
// 解説pdfを読んで実装
// 文字列を半分に分割して、前半と後半それぞれで出現する可能性のある文字列をbrute force
// わかってしまえば実装は一瞬
//
// 今回のように、配列を半分に分けてbrute forceを可能にするアルゴリズムのことを
// meet in the middleと呼ぶ
// ( https://www.quora.com/What-is-meet-in-the-middle-algorithm-w-r-t-competitive-programming )

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

map<pair<string, string>, ll> brute_force(int N, string S) {
    map<pair<string, string>, ll> counter; // <l2r, r2l>
    REP(i, (1 << N)) {
        string l2r;
        string r2l;
        REP(j, N) {
            if ((1 << j) & i) l2r += S[j];
            else r2l += S[j];
        }
        reverse(ALL(r2l));
        ++counter[mp(l2r, r2l)];
    }
    return counter;
}


int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    string S;
    cin >> N;
    cin >> S;
    string revS(S);
    reverse(ALL(revS));

    // 前半、後半でbrute force
    auto former = brute_force(N, S);
    auto latter = brute_force(N, revS);

    ll ans = 0;
    for(auto kv: former) {
        auto l2r = kv.first.first;
        auto r2l = kv.first.second;
        auto cnt = kv.second;
        ans += cnt * latter[{l2r,r2l}];
    }
    cout << ans << endl;
    return 0;
}
