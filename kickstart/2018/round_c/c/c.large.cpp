// 本番中に解けた
//
// まず、与えられた関係式から数列Aを作る
// 例としてN=3の場合を考える。
// 数列の最初の要素から始まる部分文字列は、
//   A1 * f(1)
//   A1 * f(1)  +  A2 * f(2)
//   A1 * f(1)  +  A2 * f(2)  +  A3 * f(3)
// 2番目の要素から始まる部分文字列は、
//                 A2 * f(1)
//                 A2 * f(1)  +  A3 * f(2)
// 3番目の要素から始まる部分文字列は、
//                               A3 * f(1)
//
// ここで, f(x) = x^1 + x^2 + x^3 + ... + x^K であり、前計算しておける。具体的には
//   x == 1の場合は f(x) = K
//   それ以外の場合は  f(x) = a * (a^K - 1) / (a - 1)
// である。
//
// 次に、各Aに着目する。
//   A1の係数は、3 * f(1)
//   A2の係数は、2 * (f(1) + f(2))
//   A3の係数は、1 * (f(1) + f(2) + f(3))
// と法則性があるので、これに従い係数を計算する



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

const ll MOD = 1000000007;

ll pow(ll n, ll k, ll MOD) {
    ll ret = 1;
    while(k > 0) {
        ret *= n;
        ret %= MOD;
        --k;
    }
    return ret;
}

// Calculates x raised to the y-th power modulo MOD
// xのy乗を、繰り返し二乗法というのを使って求める
ll modPow(ll x, ll y)
{
    ll r = 1, a = x;
    while (y > 0) {
        if ((y & 1) == 1) {
            r = (r * a) % MOD;
        }
        a = (a * a) % MOD;
        y /= 2;
    }

    return r;
}
// Modular multiplicative inverse through Fermat's little theorem:
// フェルマーの小定理より, a^-1 ≡ a^(p-2) (mod p) というのを使うらしい
// ただし、pが素数の時しか成り立たない
ll modInverse(ll x)
{
    return modPow(x, MOD - 2);
}

// Modular division x / y, find modular multiplicative inverse of y
// and multiply by x.
ll modDivision(ll p, ll q)
{
    return (p * modInverse(q)) % MOD;
}

ll get_sum(ll n, ll k) {
    // n^1 + n^2 + n^3 + ... + n^k
    if (n == 1) {
        return k % MOD;
    }
    else {
        ll n_k = modPow(n, k);
        ll tmp = n_k - 1;
        if (tmp < 0) tmp += MOD;
        tmp *= n;
        tmp %= MOD;
        return modDivision(tmp, (n - 1));
    }
}

void solve() {
    ll N, K, x, y, C, D, E1, E2, F;
    cin >> N >> K >> x >> y >> C >> D >> E1 >> E2 >> F;

    vector<ll> As(N);
    As[0] = (x + y) % F;
    FOR(n, 1, N) {
        auto new_x = (C * x + D * y + E1) % F;
        auto new_y = (D * x + C * y + E2) % F;
        As[n] = (new_x + new_y) % F;
        x = new_x;
        y = new_y;
    }

    vector<ll> table(N + 1);
    FOR(n, 1, N + 1) {
        table[n] = get_sum(n, K);
    }

    ll ans = 0;

    vector<ll> sum_of_table(N + 1);
    ll tmp = 0;
    FOR(loc, 1, N + 1) {
        tmp += table[loc];
        tmp %= MOD;
        sum_of_table[loc] = tmp;
    }

    REP(i, N) {

        ll cnt = N - i;
        //int loc = 1;
        //REP(j, i + 1) {
        //    coeff += table[loc];
        //    coeff %= MOD;

        //    ++loc;
        //}
        auto coeff = sum_of_table[i + 1];

        coeff *= cnt;
        coeff %= MOD;

        ans += As[i] * coeff;
        ans %= MOD;
    }

    cout << ans;
}

int main(void)
{
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
