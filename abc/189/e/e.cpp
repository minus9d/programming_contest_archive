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


struct Val {
    ll x_mul;
    ll y_mul;
    ll n;
};

struct Coord {
    Val x;
    Val y;

    void print() {
        cout << "(" << x.x_mul << ","
             << x.y_mul << ","
             << x.n << "), ("
             << y.x_mul << ","
             << y.y_mul << ","
             << y.n << ")" << endl;
    }
};

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    vector<pair<ll, ll>> points(N);
    REP(n, N) {
        ll x, y;
        cin >> x >> y;
        points[n] = mp(x, y);
    }

    vector<Coord> coord_list;
    Coord init{{1, 0, 0}, {0, 1, 0}};
    coord_list.pb(init);

    int M; cin >> M;
    REP(m, M) {
        int kind; cin >> kind;
        Coord& last = coord_list.back();
        if (kind == 1) {
            Coord next{last.y, {-last.x.x_mul, -last.x.y_mul, -last.x.n}};
            coord_list.pb(next);
        }
        else if (kind == 2) {
            Coord next{{-last.y.x_mul, -last.y.y_mul, -last.y.n}, last.x};
            coord_list.pb(next);
        }
        else if (kind == 3) {
            ll p; cin >> p;
            Coord next{{-last.x.x_mul, -last.x.y_mul, -last.x.n + 2 * p}, last.y};
            coord_list.pb(next);
        }
        else if (kind == 4) {
            ll p; cin >> p;
            Coord next{last.x, {-last.y.x_mul, -last.y.y_mul, -last.y.n + 2 * p}};
            coord_list.pb(next);
        }
        // coord_list.back().print();
    }

    int Q; cin >> Q;
    REP(q, Q) {
        int a, b;
        cin >> a >> b;
        --b;
        
        Coord& loc = coord_list[a];
        ll x1 = points[b].first;
        ll y1 = points[b].second;
        // cout << "first:" << x1 << " " << y1 << endl;
        // cout << "loc:";
        // loc.print();
        // cout << endl;

        ll x = loc.x.x_mul * x1 + loc.x.y_mul * y1 + loc.x.n;
        ll y = loc.y.x_mul * x1 + loc.y.y_mul * y1 + loc.y.n;
        cout << x << " " << y << endl;
    }



    return 0;
}
