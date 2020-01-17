// 解説pdf & http://drken1215.hatenablog.com/entry/2020/01/12/135000 を読んで実装
//
// 問題文より、Xは以下を満たす 
//   X = a_i * (p + 0.5)
// ここで a_i = 2b_i (b_iは整数) と置き直すと
//   X = 2b_i * (p + 0.5)
//     = b_i * (2p + 1)
// つまり
//   X = b_i, 3b_i, 5b_i, ...
//
// 各b_iが2で割り切れる数は同じであることが必要条件
// 各b_iが2で割り切った数の数をc_iとする
// 各c_iの最小公倍数をlcmとする
// lcm, 3*lcm, 5*lcm, ...についてそれぞれ条件を満たすか調べる
//
// lcmを求めるところで、途中でオーバーフローしそうになったら終了する必要あり
//

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


ll div2(ll a) {
    ll ans = 1;
    while(a % 2 == 0) {
        ans *= 2;
        a /= 2;
    }
    return ans;
}

// Nを素因数分解して、<素因数, 登場回数>のペアを得る
// N=12に対して <2, 2>, <3, 1>を得る
map<ll, int> getFactorsMap(ll N){
    map<ll, int> ret;
    while(!(N % 2)){
        N /= 2;
        ++ret[2];
    }
    for (ll p = 3; p*p <= N; p += 2) {
        while (N % p == 0) {
            N /= p;
            ++ret[p];
        }
    }
    if (N > 1) ++ret[N];
    return ret;
}

// 2数の最大公約数
ll getGcdSimple(const ll a, const ll b)
{
    if (b == 0) return a;
    return getGcdSimple(b, a % b);
}

// 2数の最小公倍数
ll getLcmSimple(const ll a, const ll b)
{
    return a / getGcdSimple(a, b) * b;
}

// 数のリストから最大公約数を求める
ll getGcd(const vector<ll>& n){
    auto size = SIZE(n);
    assert(size > 0);
    ll ans = n[0];
    FOR(i, 1, size) ans = getGcdSimple(ans, n[i]);
    return ans;
}

// 数のリストからleast common multiple(最小公倍数)を求める
ll getLcm(const vector<ll>& n){
    set<ll> s(ALL(n));

    if (SIZE(s) == 1) return n[0];
    ll prev = -1;
    for(auto e: s) {
        if (prev == -1) {
            prev = e;
        } else {
            prev = getLcmSimple(e, prev);
        }
        // オーバーフロー対策
        if (prev > 1e10) return prev;
    }
    return prev;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, M;
    cin >> N >> M;

    int two = -1;
    bool fail = false;
    vector<ll> As;
    REP(n, N) {
        ll a;
        cin >> a;
        As.pb(a);
        if (two == -1) {
            two = div2(a);
        } else {
            auto tmp = div2(a);
            // a_iが2で割り切れる数が一致しない場合は解なし
            if (tmp != two) {
                fail = true;
                break;
            }
        }
    }
    if (fail) {
        cout << 0 << endl;
        return 0;
    }

    // 各aを2で割る
    vector<ll> Bs;
    for(auto a: As) Bs.pb(a / 2);

    // 最小公倍数
    auto T = getLcm(Bs);
    cerr << "lcm = " << T << endl;

    // M以下の整数のうち、
    // lcm, 3*lcm, 5*lcm, ...を満たす整数の数が答

    // 愚直版　これだとTLE
    // ll ans = 0;
    // ll num = T;
    // // cerr << "two = "<< two << endl;
    // // cerr << "N / tow * 2 = " << (N / two * 2) << endl;
    // while(num <= M) {
    //     ++ans;
    //     num += T * 2;
    // }

    // 高速化版
    ll ans = ((M / T) + 1) / 2;

    cout << ans << endl;


    return 0;
}

