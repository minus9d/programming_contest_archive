// 解説YouTube を見てそのまま実装
//
// Sを00..00に固定して答を求め、2^N倍すればよい
// 以下、Sは00..00固定とする
//
// コスト列Cは昇順にソートしておく
//
// 例として
//   C = {2, 3, 4, 5}
//   S: X□??
//   T: X□??
// で□の部分が寄与するコストの総和を求めることを考える
//
// コストは、3 * "□??"にある1の個数。
// "□??"が取りうるパターンは、以下の4つ。
//    100
//    101
//    110
//    111
// 1の個数で場合分けするのではなく、縦に足すのが賢い。
// 縦に足すと、各桁の1の個数は、それぞれ 2^r, 2^(r-1), 2^(r-1)
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

constexpr ll MOD = 1e9 + 7;

template<int MOD> struct Fp {
    ll val;
    constexpr Fp(ll v = 0) noexcept : val(v % MOD) {
        if (val < 0) val += MOD;
    }
    constexpr int getmod() { return MOD; }
    constexpr Fp operator - () const noexcept {
        return val ? MOD - val : 0;
    }
    constexpr Fp operator + (const Fp& r) const noexcept { return Fp(*this) += r; }
    constexpr Fp operator - (const Fp& r) const noexcept { return Fp(*this) -= r; }
    constexpr Fp operator * (const Fp& r) const noexcept { return Fp(*this) *= r; }
    constexpr Fp operator / (const Fp& r) const noexcept { return Fp(*this) /= r; }
    constexpr Fp& operator += (const Fp& r) noexcept {
        val += r.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    constexpr Fp& operator -= (const Fp& r) noexcept {
        val -= r.val;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr Fp& operator *= (const Fp& r) noexcept {
        val = val * r.val % MOD;
        return *this;
    }
    constexpr Fp& operator /= (const Fp& r) noexcept {
        ll a = r.val, b = MOD, u = 1, v = 0;
        while (b) {
            ll t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        val = val * u % MOD;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr bool operator == (const Fp& r) const noexcept {
        return this->val == r.val;
    }
    constexpr bool operator != (const Fp& r) const noexcept {
        return this->val != r.val;
    }
    friend constexpr ostream& operator << (ostream &os, const Fp<MOD>& x) noexcept {
        return os << x.val;
    }
    friend constexpr Fp<MOD> modpow(const Fp<MOD> &a, ll n) noexcept {
        if (n == 0) return 1;
        auto t = modpow(a, n / 2);
        t = t * t;
        if (n & 1) t = t * a;
        return t;
    }
};
using mint = Fp<MOD>;

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    vector<ll> Cs(N);
    REP(n, N) cin >> Cs[n];
    sort(ALL(Cs));

    // 2^nを前計算
    vector<mint> two(N + 1);
    two[0] = 1;
    REP(i, N) two[i+1] = two[i] * 2;

    mint ans;
    REP(i, N) {
        int l = i;
        int r = N - 1 - i;

        // X□?? の "□"の部分にくる1の数 
        mint now = two[r];

        // X□?? の "?"の部分にくる1の数
        if (r != 0) now += two[r - 1] * r;

        // X□?? の "X"の部分にくるパターン数
        now *= two[l];

        now *= Cs[i];
        ans += now;
    }
    ans *= two[N];
    cout << ans << endl;
    return 0;
}
