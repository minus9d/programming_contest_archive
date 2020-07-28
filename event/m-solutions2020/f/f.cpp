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

using P = pair<ll, ll>;


map<ll, vector<ll>> make_xy(vector<P> ups) {
    map<ll, vector<ll>> ret;
    for (auto p: ups) {
        auto x = p.first;
        auto y = p.second;
        ret[x].pb(y);
    }
    return ret;
}

map<ll, vector<ll>> make_yx(vector<P> lefts) {
    map<ll, vector<ll>> ret;
    for (auto p : lefts) {
        auto x = p.first;
        auto y = p.second;
        ret[y].pb(x);
    }
    return ret;
}

const ll MAX_ANS = 1e18;

ll solve_updown(map<ll, vector<ll>> ups_xy, map<ll, vector<ll>> downs_xy) {
    ll ans = MAX_ANS;
    for (auto xy : ups_xy) {
        auto x = xy.first;

        // 上に向かう
        auto up_ys = xy.second;
        sort(ALL(up_ys));

        if (!downs_xy.count(x)) continue;

        // 下に向かう
        auto down_ys = downs_xy[x];
        sort(ALL(down_ys));

        for (auto up_y : up_ys) {
            // 最初にぶつかるのは
            auto it = lower_bound(ALL(down_ys), up_y);
            if (it == down_ys.end()) continue;
            auto down_y = *it;
            chmin(ans, (down_y - up_y) * 5);
        }
    }
    return ans;
}

map<ll, vector<ll>> make_diag(vector<P> ups) {
    map<ll, vector<ll>> ret;
    for (auto p : ups) {
        auto x = p.first;
        auto y = p.second;
        auto key = x + y;
        ret[key].pb(x);
    }
    return ret;
}

ll solve_upright(vector<P> ups, vector<P> rights) {
    map<ll, vector<ll>> ups_kv = make_diag(ups);
    map<ll, vector<ll>> rights_kv = make_diag(rights);

    ll ans = MAX_ANS;
    for (auto kv : rights_kv) {
        auto k = kv.first;

        auto right_xs = kv.second;
        sort(ALL(right_xs));

        if (!ups_kv.count(k)) continue;

        auto ups_xs = ups_kv[k];
        sort(ALL(ups_xs));

        for (auto right_x : right_xs) {
            // 最初にぶつかるのは
            auto it = lower_bound(ALL(ups_xs), right_x);
            if (it == ups_xs.end()) continue;
            auto up_x = *it;
            chmin(ans, abs(right_x - up_x) * 10);
        }
    }

    //for (auto kv : ups_kv) {
    //    auto k = kv.first;

    //    // 上に向かう
    //    auto up_xs = kv.second;
    //    sort(ALL(up_xs));

    //    if (!rights_kv.count(k)) continue;

    //    // 右に向かう
    //    auto rights_xs = rights_kv[k];
    //    sort(ALL(rights_xs));

    //    for (auto up_x : up_xs) {
    //        // 最初にぶつかるのは
    //        auto it = lower_bound(ALL(rights_xs), up_x);
    //        if (it == rights_xs.end()) continue;
    //        auto right_x = *it;
    //        chmin(ans, abs(right_x - up_x) * 10);
    //    }
    //}
    return ans;
}

vector<P> xmirror(vector<P> points) {
    vector<P> ret;
    for (auto p : points) {
        ret.push_back(mp(-p.first, p.second));
    }
    return ret;
}

vector<P> ymirror(vector<P> points) {
    vector<P> ret;
    for (auto p : points) {
        ret.push_back(mp(p.first, -p.second));
    }
    return ret;
}


int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    vector<P> ups;
    vector<P> rights;
    vector<P> lefts;
    vector<P> downs;

    REP(n, N) {
        ll x, y;
        char u;
        cin >> x >> y >> u;
        if (u == 'U') ups.pb({x, y});
        else if (u == 'R') rights.pb({x, y});
        else if (u == 'D') downs.pb({x, y});
        else if (u == 'L') lefts.pb({x, y});
    }

    ll ans = MAX_ANS;

    // 下と上
    map<ll, vector<ll>> ups_xy = make_xy(ups);
    map<ll, vector<ll>> downs_xy = make_xy(downs);
    ll ans_updown = solve_updown(ups_xy, downs_xy);
    chmin(ans, ans_updown);

    // 右と左
    map<ll, vector<ll>> rights_yx = make_yx(rights);
    map<ll, vector<ll>> lefts_yx = make_yx(lefts);
    ll ans_rightleft = solve_updown(rights_yx, lefts_yx);
    chmin(ans, ans_rightleft);

    // UpとRight
    ll ans_upright = solve_upright(ups, rights);
    chmin(ans, ans_upright);

    // UpとLeft
    ll ans_upleft = solve_upright(xmirror(ups), xmirror(lefts));
    chmin(ans, ans_upleft);

    // DownとRight
    ll ans_downright = solve_upright(ymirror(downs), ymirror(rights));
    chmin(ans, ans_downright);

    // DownとLeft
    ll ans_downleft = solve_upright(
        xmirror(ymirror(downs)),
        xmirror(ymirror(lefts)));
    chmin(ans, ans_downleft);

    if (ans == MAX_ANS) {
        cout << "SAFE" << endl;
    }
    else {
        cout << ans << endl;

    }



    return 0;
}
