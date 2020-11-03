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

ll solve(ll N, ll K, vector<ll> As) {
    vector<ll> minus;
    vector<ll> plus;
    vector<ll> zero;
    for(auto a: As) {
        if (a > 0) plus.pb(a);
        else if (a < 0) minus.pb(a);
        else zero.pb(a);
    }

    // if (SIZE(plus) + SIZE(minus) < K) {
    //     return 0;
    // }

    vector<ll> absminus;
    for(auto m: minus) absminus.pb(abs(m));

    sort(ALL(plus));
    sort(ALL(absminus));
    reverse(ALL(plus));
    reverse(ALL(absminus));

    mint tmp = 1;
    vector<mint> minusmul{tmp};
    vector<long double> minusmullog{0};
    for(auto m: absminus) {
        tmp *= m;
        minusmul.pb(tmp);
        minusmullog.pb(minusmullog.back() + log(m));
    }

    tmp = 1;
    vector<mint> plusmul{1};
    vector<long double> plusmullog{0};
    for(auto m: plus) {
        tmp *= m;
        plusmul.pb(tmp);
        plusmullog.pb(plusmullog.back() + log(m));
    }

    // (i) ans is plus
    mint ans = 0;
    bool pos_found = false;
    long double anslog = -1e18;
    for(int i = 0; i < SIZE(minusmul); i += 2) {
        int j = K - i;
        if (SIZE(plus) < j || SIZE(minus) < i) continue;
        if (j < 0) continue;

        pos_found = true;

        mint val1 = minusmul[i];
        mint val2 = plusmul[K - i];

        auto vallog1 = minusmullog[i];
        auto vallog2 = plusmullog[K - i];
        if (vallog1 + vallog2 > anslog) {
            anslog = vallog1 + vallog2;
            ans = val1 * val2;
            //cout << "!ans = " << ans << endl;
        }
    }
    if (pos_found) return ans.val;

    // (ii) ans is zero
    if (SIZE(zero) > 0) return 0;

    // (iii) ans is nega
    {
        sort(ALL(plus));
        sort(ALL(absminus));
        
        mint tmp = 1;
        vector<mint> minusmul{ tmp };
        vector<long double> minusmullog{ 0 };
        for (auto m : absminus) {
            tmp *= m;
            minusmul.pb(tmp);
            minusmullog.pb(minusmullog.back() + log(m));
        }

        tmp = 1;
        vector<mint> plusmul{ 1 };
        vector<long double> plusmullog{ 0 };
        for (auto m : plus) {
            tmp *= m;
            plusmul.pb(tmp);
            plusmullog.pb(plusmullog.back() + log(m));
        }

        mint ans = 0;
        bool pos_found = false;
        long double anslog = 1e18;
        for (int i = 1; i < SIZE(minusmul); i += 2) {
            int j = K - i;
            if (SIZE(plus) < j || SIZE(minus) < i) continue;

            pos_found = true;

            mint val1 = minusmul[i];
            mint val2 = plusmul[K - i];

            auto vallog1 = minusmullog[i];
            auto vallog2 = plusmullog[K - i];
            if (vallog1 + vallog2 < anslog) {
                anslog = vallog1 + vallog2;
                ans = -val1 * val2;
                //cout << "!ans = " << ans << endl;
            }
        }
        return ans.val;
    }
    
    

    return 777;
    
    
    
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N, K;
    cin >> N >> K;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];
    cout << solve(N, K, As) << endl;

    return 0;
}
