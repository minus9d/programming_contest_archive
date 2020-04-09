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

int main(void)
{
    cin.sync_with_stdio(false);
    int N, K, C;
    cin >> N >> K >> C;
    string S;
    cin >> S;

    vector<int> left(N);
    vector<int> right(N);

    vector<int> indexes;
    int last = 1e9;
    int cnt = 0; // 置いた個数
    REP(i, N) {
        if (S[i] == 'o') {
            indexes.pb(i);

            // 置ける?
            if (last == 1e9 || i - last - 1 >= C) {
                last = i;
                ++cnt;
            }

            left[i] = cnt - 1;
        }
    }

    last = 1e9;
    cnt = 0;
    for(int i = N - 1; i >= 0; --i) {
        if (S[i] == 'o') {

            // 置ける?
            if (last == 1e9 || abs(i - last) - 1 >= C) {
                last = i;
                ++cnt;
            }

            right[i] = cnt - 1;
        }
    }
    for (auto e : left) cerr << e << " ";
    cerr << endl;
    for (auto e : right) cerr << e << " ";
    cerr << endl;


    REP(k, SIZE(indexes)) {
        auto i = indexes[k];

        if (left[i] + right[i] + 1 != K) continue;

        bool ok = true;
        if (k != 0) {
            int j = indexes[k - 1];
            if (left[i] == left[j] && right[i] == right[j]) ok = false;
        }
        if (k != SIZE(indexes) - 1) {
            int j = indexes[k + 1];
            if (left[i] == left[j] && right[i] == right[j]) ok = false;
        }
        if (ok) {
            cout << (i + 1) << endl;
        }
    }

    return 0;
}
