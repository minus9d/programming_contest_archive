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
    size_t m_N;
    vector<T> m_cum;
};

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N, M, K;
    cin >> N >> M >> K;
    vector<ll> As(N);
    vector<ll> Bs(M);

    REP(n, N) cin >> As[n];
    REP(m, M) cin >> Bs[m];

    CumSum1D<ll> aSum;
    aSum.init(As);
    CumSum1D<ll> bSum;
    bSum.init(Bs);

    int ans = 0;
    REP(n, N + 1) {
        ll sum_of_n = 0;
        if (n > 0) sum_of_n = aSum.getSum(0, n - 1);
        // cout << sum_of_n << endl;

        ll remain = K - sum_of_n;
        if (remain < 0) {
            continue;
        }
        else if (remain == 0) {
            // cout << "  " << n << endl;
            chmax(ans, n);
        }
        else {
            auto it = lower_bound(ALL(bSum.m_cum), remain + 1);
            int idx = it - bSum.m_cum.begin();
            chmax(ans, n + idx);
            // cout << "  " << n + idx << endl;
        }
    }
    cout << ans << endl;
    
    
    



    return 0;
}
