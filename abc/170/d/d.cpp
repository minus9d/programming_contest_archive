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

int solve_fast(int N, vector<int> As) {
    sort(ALL(As));

    vector<int> used(1e6 + 1);

    // corner
    REP(i, N - 1) {
        auto a = As[i];
        if (used[a]) continue;

        if (As[i] == As[i + 1]) {
            used[As[i]] = 1;

            ll j = 1;
            while ((ll)a * j <= (ll)1e6) {
                used[a * j]++;
                j += 1;
            }

        }
    }

    int ans = 0;

    for(auto a: As) {
        if (used[a]) continue;
        else {
            ++ans;
            ll i = 1;
            while((ll)a * i <= (ll)1e6) {
                used[a * i]++;
                i += 1;
            }
        }
    }
    return ans;
}

int solve_slow(int N, vector<int> As) {
    sort(ALL(As));

    int ans = 0;
    REP(i, N) {
        bool ok = true;
        REP(j, N) {
            if (i == j) continue;
            if (As[i] % As[j] == 0) {
                ok = false;
                break;
            }
        }
        ans += ok;
    }
    return ans;
}

 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    //while(1){
    //    int N = 5;
    //    vector<int> As(N);
    //    REP(n, N) As[n] = (rand() % 30) + 1;
    //    auto slow = solve_slow(N, As);
    //    auto fast = solve_fast(N, As);
    //    if (slow != fast) {
    //        cout << N << endl;
    //        for(auto a: As) cout << a << " ";
    //        cout << endl;

    //        cout << "fast:" << solve_fast(N, As) << endl;
    //        cout << "slow:" << slow << endl;
    //        return 0;
    //    }
    //}

    int N;
    cin >> N;

    vector<int> As(N);
    REP(n, N) cin >> As[n];
    cout << solve_fast(N, As) << endl;

    return 0;
}
