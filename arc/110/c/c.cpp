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

vector<int> solve(int N, vector<int>& Ps) {
    vector<int> pos(N);
    REP(n, N) {
        pos[Ps[n]] = n;
    }

    vector<int> manip;

    bool ok = true;
    vector<int> used_swap(N - 1);
    REP(n, N - 1) {
        int p = pos[n];
        
        while(p != n) {
            int m = Ps[p - 1];
            if(used_swap[p - 1]) {
                ok = false;
                break;
            }
            swap(Ps[p], Ps[p - 1]);
            pos[n] = p - 1;
            pos[m] = p;
            used_swap[p - 1] = 1;
            manip.pb(p);

            // for(auto e: Ps) cout << e << " ";
            // cout << endl;

            p -= 1;
        }
        if (!ok) break;
    }

    // ちょうど1回?
    for(auto e: used_swap) {
        if (e == 0) {
            ok = false;
        }
    }
    // 昇順? (ありえないはず)
    REP(n, N) {
        if (Ps[n] != n) ok = false;
    }

    if (!ok) {
        manip.clear();
        manip.pb(-1);
    } 
    return manip;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    vector<int> Ps(N);
    REP(n, N) {
        cin >> Ps[n]; --Ps[n];
    }


    // while(1) {
    //     int N = 10;
    //     vector<int> Qs;
    //     REP(n, N) Qs.pb(n);
    //     vector<int> shff;
    //     REP(i, N - 1) shff.pb(i);
    //     random_shuffle(ALL(shff));

    //     for(auto e: shff) {
    //         swap(Qs[e], Qs[e+1]);
    //     }
    //     auto res = solve(N, Qs);
    //     for(auto e: res) cout << e << " ";

    //     cout << endl;
    //     if (SIZE(res) == 1) {
    //         cout << "error!" << endl;
    //         for(auto q: Qs) cout << q << " ";
    //         cout << endl;
    //         for(auto q: shff) cout << q << " ";
    //         cout << endl;
    //         return -1;
    //     }
    // }


    auto res = solve(N, Ps);
    for(auto e: res) cout << e << endl;

    return 0;
}
