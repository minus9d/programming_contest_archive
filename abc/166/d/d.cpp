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

set<ll> getDivisorsSet(const ll n){
    set<ll> ret;
    for(ll i = 1; i*i <= n; ++i){
        if (!(n % i)){
            ret.insert(i);
            ret.insert(n/i);
        }
    }
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll X;
    cin >> X;

    auto nums = getDivisorsSet(X);
    for (auto num: nums) {
        cerr << "num:" << num << endl;
        for(ll a = -200; a <= 200; ++a) {
            {
                //(i) a - b == num
                ll b = a - num;
                if (a * a * a * a * a - b * b * b * b * b == X) {
                    cerr << "(i)" << endl;
                    cout << a << " " << b << endl;
                    return 0;
                }

                // ll a2 = a * a;
                // ll a3 = a2 * a;
                // ll a4 = a3 * a;
                // ll b2 = b * b;
                // ll b3 = b2 * b;
                // ll b4 = b3 * b;
                // ll tmp2 = a4 + a3 * b + a2 * b2 + a * b4 + b4;
                // if ((a - b) * tmp2 == X) {
                //     cerr << "(i)" << endl;
                //     cout << a << " " << b << endl;
                //     return 0;
                // }
            }
            {
                // (ii) a - b == -num
                ll b = a + num;
                if (a * a * a * a * a - b * b * b * b * b == X) {
                    cerr << "(i)" << endl;
                    cout << a << " " << b << endl;
                    return 0;
                }

                // ll a2 = a * a;
                // ll a3 = a2 * a;
                // ll a4 = a3 * a;
                // ll b2 = b * b;
                // ll b3 = b2 * b;
                // ll b4 = b3 * b;
                // ll tmp2 = a4 + a3 * b + a2 * b2 + a * b4 + b4;
                // if ((a - b) * tmp2 == X) {
                //     cerr << "(ii)" << endl;
                //     cout << a << " " << b << endl;
                //     return 0;
                // }
            }
        }
    }


    return 0;
}
