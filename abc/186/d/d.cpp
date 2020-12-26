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
#define REP(i,n) for(ll i = 0; i < (ll)(n); ++i)
#define FOR(i,a,b) for(ll i = (a); i < (ll)(b); ++i)
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

// 1次元累積和
template <typename T>
class CumSum1D
{
public:
    CumSum1D(){};
    ~CumSum1D(){};
    void init(vector<T>& arr) {
        m_cum = arr;
        m_N = arr.size();
        FOR(i, 1, m_N) m_cum[i] += m_cum[i - 1];
    }
    // get sum of [l, r]. 0-based.
    T getSum(int l, int r) const {
        T ret = m_cum[r];
        if (l != 0) ret -= m_cum[l - 1];
        return ret;
    }
private:
    size_t m_N;
    vector<T> m_cum;
};

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    vector<ll> As(N);
    REP(n, N) cin >> As[n];

    auto Bs = As;
    sort(ALL(Bs));

    CumSum1D<ll> cum;
    cum.init(Bs);

    ll ans = 0;
    for(auto b: Bs) {
        auto it = lower_bound(ALL(Bs), b);
        auto idx = it - Bs.begin();

        // cout << "b, idx = " << b << "," << idx << endl;
        
        if (idx != 0) {
            ll tmp1 = (b * idx) - cum.getSum(0, idx - 1);
            // cout << "tmp1 = " << tmp1 << endl;
            ans += tmp1;
        }
        ll tmp2 = cum.getSum(idx, N - 1) - (b * (N - idx));
        // cout << "tmp2 = " << tmp2 << endl;
        ans += tmp2;
    }
    cout << (ans / 2) << endl;

    return 0;
}
