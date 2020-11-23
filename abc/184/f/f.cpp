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

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, T;
    cin >> N >> T;

    if (N == 1) {
        ll A; cin >> A;
        if (A <= T) cout << A << endl;
        else cout << 0 << endl;
        return 0;
    }

    int N1 = N / 2;
    int N2 = N - N1;

    vector<ll> As(N1);
    REP(n, N1) cin >> As[n];
    vector<ll> Bs(N2);
    REP(n, N2) cin >> Bs[n];

    vector<ll> sums;
    REP(i, (1 << N1)) {
        ll sum = 0;
        REP(j, N1) {
            if (i & (1 << j)) {
                sum += As[j];
            }
        }
        sums.pb(sum);
    }
    sort(ALL(sums));

    ll ans = 0;
    REP(i, (1 << N2)) {
        ll sum = 0;
        REP(j, N2) {
            if (i & (1 << j)) {
                sum += Bs[j];
            }
        }

        if (sum > T) continue;

        ll remain = T - sum;
        auto it = lower_bound(ALL(sums), remain);

        if (it == sums.end()) {
            ll val = *(--it);
            ll local_ans = sum + val;
            chmax(ans, local_ans);
        }
        else if (*it == remain) {
            ans = T;
        }
        else if (it == sums.begin()) {
            continue;
        }
        else {
            ll val = *(--it);
            ll local_ans = sum + val;
            chmax(ans, local_ans);
        }
    }
    cout << ans << endl;

    return 0;
}
