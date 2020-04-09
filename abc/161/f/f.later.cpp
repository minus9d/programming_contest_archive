// 解説PDFの通り実装
// 「NをKで割れるだけ割ったあと、
//   NからKを引けるだけ引く。
//   いちどKを引くフェーズに入れば、
//   二度とKで割るフェーズには戻らない」ということにまず気付く必要があった
// そして「Nを一度でも割れるK」と「一度も割れないK」で場合分け
// することに気付く必要があった

#include <algorithm>
#include <array>
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
typedef long long ll;
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())
template<class T> inline bool chmin(T& a, T b) {
    if (a > b) {
        a = b; return true;
    }
    return false;
}
template<class T> inline bool chmax(T& a, T b) {
    if (a < b) {
        a = b; return true;
    }
    return false;
}
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
constexpr ll MOD = 1e9 + 7;
using mint = Fp<MOD>;

#define pb push_back
#define mp make_pair
#define mt make_tuple

bool judge(ll N, ll k) {
    if (k == 1) return false;

    // Nをkで割れるだけ割る
    while(N % k == 0) {
        N /= k;
    }
    return N % k == 1;
}

vector<ll> get_divisors(ll N) {
    vector<ll> ret;
    for(ll i = 1; i * i <= N; ++i) {
        if (N % i == 0) {
            ret.pb(i);
            if (i * i != N) ret.pb(N / i);
        }
    }
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N;
    cin >> N;

    ll ans = 0;

    // (i)KがNの約数
    for(ll k: get_divisors(N)) {
        ans += judge(N, k);
    }

    // (ii)KがNの約数でない
    //     <=> N % K = 1
    //     <=> N-1 % K == 0
    // つまりN-1の約数を列挙して、そこから1の分を引く
    ans += SIZE(get_divisors(N - 1)) - 1;

    cout << ans << endl;

    return 0;
}
