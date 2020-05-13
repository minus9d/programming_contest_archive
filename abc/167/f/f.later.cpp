// 各文字列について'('を+1, ')'を-1と考える。
// 各文字列で(mi, si) = (累積和の最小値、全体の和)を求める。
//
// 全体の和がプラスのものは足せば足すほど得なので、
// 累積和の最小値が小さいものから順に足していく。
//
// 全体の和がマイナスのものは、si - miが大きいものから順番に足していく。
// 証明は https://betrue12.hateblo.jp/entry/2020/05/10/224429 
// の証明2を参照。

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

void get_result(string s, int& mn, int& result) {
    mn = 0;
    result = 0;
    for(auto ch: s) {
        if (ch == '(') {
            ++result;
        } else {
            --result;
            chmin(mn, result);
        }
    }
}

bool asc1( const pair<int, int>& left, const pair<int, int>& right ) {
    return left.first > right.first;
}

bool asc2( const pair<int, int>& left, const pair<int, int>& right ) {
    return (left.second - left.first) > (right.second - right.first);
}

string solve_slow(int N, vector<string> parens) {
    sort(ALL(parens));
    do {
        string s;
        for(auto p: parens) s += p;
        int mn, result;
        get_result(s, mn, result);
        if (mn == 0 && result == 0) return "Yes";
    }while(next_permutation(ALL(parens)));
    return "No";
}

string solve_fast(int N, vector<string> &parens) {
    vector<pair<int, int>> plus;
    vector<pair<int, int>> minus;

    ll remain = 0;
    REP(n, N) {
        string s = parens[n];
        int mn, result;
        get_result(s, mn, result);
        if (mn >= 0) {
            remain += result;
        }
        else {
            if (result >= 0) {
                plus.push_back({mn, result});
            }
            else {
                minus.push_back({mn, result});
            }
        }
    }

    bool ok = true;
    sort(ALL(plus), asc1);
    for(auto p: plus) {
        if (remain + p.first < 0) {
            ok = false;
            break;
        } else {
            remain += p.second;
        }
    }

    sort(ALL(minus), asc2);
    for(auto m: minus) {
        if (remain + m.first < 0) {
            ok = false;
            break;
        } else {
            remain += m.second;
        }
    }

    if (ok && remain == 0) {
        return "Yes";
    } else {
        return "No";
    }
}

string make_random(int len) {
    string ret;
    REP(i, len) {
        if (rand() % 2) ret += "(";
        else ret += ")";
    }
    return ret;
}

int main(void)
{
    //while(1) {
    //    int N = rand() % 6 + 1;
    //    vector<string> strs;
    //    REP(n, N) {
    //        strs.pb(make_random(rand() % 6 + 1));
    //    }
    //    auto ans1 = solve_slow(N, strs);
    //    auto mine = solve_fast(N, strs);
    //    if (ans1 != mine) {
    //        cout << "error!" << endl;
    //        cout << N << endl;
    //        for (auto s : strs) cout << s << endl;
    //        return 0;
    //    }
    //    else {
    //        cout << ans1 << endl;
    //    }
    //}


    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<string> parens(N);
    REP(n, N) {
        cin >> parens[n];
    }

    auto fast = solve_fast(N, parens);
    cout << fast << endl;

    return 0;
}
