// 本番中にぎりぎり解けた
//
// N個のブロックのうち、X個にA点、Y個にB点与えると考える。そうすると色のことは考えなくてよくなる
// (A点のブロックは赤、B点のブロックは青、A+B点のブロックは緑とできる）
// まず、以下の方程式を満たすX, Yを探す。
//   A * X + B * Y = K
//   0 <= X <= N
//   0 <= Y <= N
// Xを0から順にNまで動かしたとき、Yが他の方程式を満たすかをチェックするのは容易。
// 次に、あるX, Yのペアに対して、塗り方は、choose(N, X) * choose(N, Y)。
// choose(N, i)はあらかじめテーブルとして計算しておけばよい
//
// 本番では Y が正の値であるチェックなどを忘れて2WA

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

ll MOD = 998244353;

ll modPow(ll x, ll y)
{
    ll r=1, a=x;
    while (y > 0) {
        if ( (y&1)==1 ) {
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
    return modPow(x, MOD-2);
}

// Modular division x / y, find modular multiplicative inverse of y
// and multiply by x.
ll modDivision(ll p, ll q)
{
    return (p * modInverse(q)) % MOD;
}

// Binomial coifficient C(n,k) in O(k) time.
void makeCTable(ll n, ll k, vector<ll>& table)
{
    if (k > n) {
        return;
    }
    ll p = 1, q = 1;
    table[0] = 1;
    for (ll i=1; i<=k; i++) {
        q = ( q * i) % MOD;
        p = ( p * (n - i + 1) ) % MOD;
        table[i] = modDivision(p, q);
    }
}


ll solve(ll N, ll A, ll B, ll K) {
    vector<ll> nck_table(N+1);
    makeCTable(N, N, nck_table);

    ll ans = 0;
    // A * x + B * y == K
    REP(x, N + 1) {
        auto K2 = K - A * x;
        if (K2 % B == 0) {
            auto y = K2 / B;
            if (y > N) continue;
            if (y < 0) continue;
            // cerr << "x, y = " << x << "," << y << endl;
            ans += nck_table[x] * nck_table[y];
            ans %= MOD;
        }
    }
    return ans;


    // // ll gcd_num = gcd(A, B);
    // // cerr << "gcd(A,B):" << gcd_num << endl;

    // ll gcd_num = gcd(gcd(A, B), K);
    // cerr << "gcd(A,B,K):" << gcd_num << endl;

    // ll A2 = A / gcd_num;
    // ll B2 = B / gcd_num;
    // ll K2 = K / gcd_num;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, A, B, K;
    cin >> N >> A >> B >> K;
    cout << solve(N, A, B, K) << endl;

    //while(1) {
    //    ll N = rand() % 100000;
    //    ll A = rand() % 100000;
    //    ll B = rand() % 100000;
    //    ll K = abs((ll)rand() * rand() * rand()) % 18000000000;
    //    cout << N << " " << A << " " << B << " " << K << endl;
    //    solve(N, A, B, K);
    //}
    

        
    return 0;
}
