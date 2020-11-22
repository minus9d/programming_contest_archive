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

ll slow(int N, string caa, string cab, string cba, string cbb) {
    set<string> curr_set;
    curr_set.insert("AB");

    REP(n, N - 2) {
        int size = 2 + n;
        set<string> next_set;
        for(auto& s: curr_set) {
            REP(i, size - 1) {
                char ch1 = s[i];
                char ch2 = s[i + 1];
                string next_s = s;
                if (ch1 == 'A' && ch2 == 'A') {
                    next_s.insert(i + 1, caa);
                }
                else if (ch1 == 'A' && ch2 == 'B') {
                    next_s.insert(i + 1, cab);
                }
                else if (ch1 == 'B' && ch2 == 'A') {
                    next_s.insert(i + 1, cba);
                }
                else if (ch1 == 'B' && ch2 == 'B') {
                    next_s.insert(i + 1, cbb);
                }
                    
                next_set.insert(next_s);
            }
        }
        curr_set = next_set;

        // cout << "set:" << endl;
        // for(auto s: curr_set) cout << "  " << s << endl;
        // cout << endl;
    }

    return SIZE(curr_set) % MOD;
}

ll func1(ll N) {
    mint ans = 1;
    N -= 3;
    REP(n, N) {
        ans *= 2;
    }
    return ans.val;
}

ll func2(ll N) {
    vector<mint> fib;
    fib.pb(1);
    fib.pb(1);

    REP(n, N) {
        int len = SIZE(fib);
        mint val = fib[len-1] + fib[len-2];
        fib.pb(val);
    }

    return fib[N - 2].val;
}

ll fast(int N, string caa, string cab, string cba, string cbb) {
    string s = caa + cab + cba + cbb;

    // 1,1,2,4,8,...
    set<string> pattern1 {"ABAA", "BABA", "BABB", "BBAA"};
    // 1,1,2,3,5,8,...
    set<string> pattern2 {"ABBA", "BAAA", "BAAB", "BBBA"};

    if (pattern1.count(s)) {
        return func1(N);
    } else if (pattern2.count(s)) {
        return func2(N);
    } else {
        return 1;
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // for (auto caa : vector<string>{"A", "B"}) {
    //     for (auto cab : vector<string>{"A", "B"}) {
    //         for (auto cba : vector<string>{"A", "B"}) {
    //             for (auto cbb : vector<string>{"A", "B"}) {
    //                 cout << caa << cab << cba << cbb << endl;
    //                 FOR(N, 2, 10) {
    //                     cout << slow(N, caa, cab, cba, cbb) << ",";
    //                     assert (slow(N, caa, cab, cba, cbb) 
    //                             == fast(N, caa, cab, cba, cbb));
    //                 }
    //                 cout << endl << endl;
    //             }
    //         }
    //     }
    // }

    ll N;
    cin >> N;
    string caa, cab, cba, cbb;
    cin >> caa >> cab >> cba >> cbb;

    cout << fast(N, caa, cab, cba, cbb) << endl;
    return 0;



}
