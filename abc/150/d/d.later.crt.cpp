// ネタバレを読んだ状態でAC
// ほぼ中国剰余定理を適用するだけでAC
// しかしよく考えると途中でオーバーフローしていた可能性がある？？

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

// 負の数にも対応した mod
// 例えば -17 を 5 で割った余りは本当は 3 (-17 ≡ 3 (mod. 5))
// しかし単に -17 % 5 では -2 になってしまう
inline ll mod(ll a, ll m) {
    return (a % m + m) % m;
}

// 拡張 Euclid の互除法
// ap + bq = gcd(a, b) となる (p, q) を求め、d = gcd(a, b) をリターンします
ll extGcd(ll a, ll b, ll &p, ll &q) {  
    if (b == 0) { p = 1; q = 0; return a; }  
    ll d = extGcd(b, a%b, q, p);  
    q -= a/b * p;  
    return d;  
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x ≡ r (mod. m)
// 解なしの場合は (0, -1) をリターン
// e.g. 3で割って2余り、5で割って3余る数を求めたいとき
//      すなわち x ≡ 2 (mod. 3) かつ x ≡ 3 (mod. 5) である xを求めたいとき
//      ChineseRem(2, 3, 3, 5) で (8, 15) が戻る。
//      これは、解が x ≡ 8 (mod. 15) であることを意味する
pair<ll, ll> chineseRemSimple(ll b1, ll m1, ll b2, ll m2) {
    ll p, q;
    ll d = extGcd(m1, m2, p, q); // p is inv of m1/d (mod. m2/d)
    if ((b2 - b1) % d != 0) return make_pair(0, -1);
    ll m = m1 * (m2/d); // lcm of (m1, m2)
    ll tmp = (b2 - b1) / d * p % (m2/d);
    ll r = mod(b1 + m1 * tmp, m);
    return make_pair(r, m);
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x ≡ r (mod. m)
// 解なしの場合は (0, -1) をリターン
pair<ll, ll> chineseRem(const vector<ll> &b, const vector<ll> &m) {
    ll r = 0, M = 1;
    for (int i = 0; i < (int)b.size(); ++i) {
        ll p, q;
        ll d = extGcd(M, m[i], p, q); // p is inv of M/d (mod. m[i]/d)
        if ((b[i] - r) % d != 0) return make_pair(0, -1);
        ll tmp = (b[i] - r) / d * p % (m[i]/d);
        r += M * tmp;
        M *= m[i]/d;
    }
    return make_pair(mod(r, M), M);
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, M;
    cin >> N >> M;

    vector<ll> Bs;
    vector<ll> Ms;
    REP(n, N) {
        ll a;
        cin >> a;
        // Xは、aで割るとあまりがa/2であるような数
        Ms.pb(a);
        Bs.pb(a / 2);
    }

    // 中国剰余定理でXの条件を求めると、
    // X ≡ r (mod. m) と分かる
    auto ret = chineseRem(Bs, Ms);
    auto r = ret.first;
    auto m = ret.second;
    cerr << "r, m = " << r << ", " << m << endl;

    if (r == 0 && m == -1) {
        cout << 0 << endl;
    }
    else {
        ll ans = M / m;
        // 端数分を考慮
        if (M % m != 0 && (M - (M / m) * m) >= r) ++ans;
        cout << ans << endl;
    }

    return 0;
}
