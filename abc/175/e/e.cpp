// 本番中にAC
//
// あらかじめ各列の爆破対象を数えて、もっとも爆破対象が多くなる列と、その爆破対象Nを特定。
// どの爆破対象Nの列を選んだとしても絶対に爆弾をおかないといけない行を調べておく。
// 行iにおける処理可能な爆破対象の最大値は、
// その行にある爆破対象 + NまたはN-1（その行に爆弾を置かないと、列の爆破対象をNにできないとき）になる

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

    int H, W, M;
    cin >> H >> W >> M;

    vector<pair<int, int>> hws(M);
    map<int, int> rows;
    map<int, int> cols;

    map<int, vector<int>> col_idxes;

    REP(m, M) {
        int h, w;
        cin >> h >> w;
        h--; w--;
        hws[m] = mp(h, w);
        rows[h]++;
        cols[w]++;
        col_idxes[w].pb(h);
    }

    int mx_num = 0;
    for(auto kv: cols) {
        chmax(mx_num, kv.second);
    }

    int fail_max = 0;
    vector<int> fails(H);
    for(auto kv: cols) {
        if (kv.second == mx_num) {
            for(auto idx: col_idxes[kv.first]) {
                fails[idx]++;
            }
            fail_max++;
        }
    }

    vector<int> fail_row(H);
    REP(h, H) {
        if (fail_max == fails[h]) fail_row[h] = 1;
    }

    int ans = 0;
    for(auto kv: rows) {
        int h = kv.first;
        int tmp = kv.second;
        if (fail_row[h]) tmp += mx_num - 1;
        else tmp += mx_num;
        chmax(ans, tmp);
    }
    cout << ans << endl;
    

    return 0;
}
