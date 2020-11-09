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

const int LIGHT = 1;
const int WALL = -1;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int H, W, N, M;
    cin >> H >> W >> N >> M;

    vector<vector<int>> cells(H, vector<int>(W));

    vector<vector<pair<int, int>>> rows(H);
    vector<vector<pair<int, int>>> cols(W);

    REP(h, H) {
        rows[h].pb(mp(-1, WALL));
        rows[h].pb(mp(W, WALL));
    }
    REP(w, W) {
        cols[w].pb(mp(-1, WALL));
        cols[w].pb(mp(H, WALL));
    }

    REP(n, N) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        cells[a][b] = LIGHT;
        
        rows[a].pb(mp(b, LIGHT));
        cols[b].pb(mp(a, LIGHT));
    }
    REP(m, M) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        cells[a][b] = WALL;

        rows[a].pb(mp(b, WALL));
        cols[b].pb(mp(a, WALL));
    }

    REP(h, H) {
        sort(ALL(rows[h]));
    }
    REP(w, W) {
        sort(ALL(cols[w]));
    }

    int ans = 0;
    REP(h, H) {
        REP(w, W) {
            if (cells[h][w] == LIGHT) {
                ++ans;
            } else if (cells[h][w] == WALL) {
                continue;
            } else {
                bool ok = false;

                pair<int, int> tmp{ w, 0 };
                auto it1 = lower_bound(ALL(rows[h]), tmp);
                if (it1->second == LIGHT) ok = true;
                if ((--it1)->second == LIGHT) ok = true;

                pair<int, int> tmp2{ h, 0 };
                auto it2 = lower_bound(ALL(cols[w]), tmp2);
                if (it2->second == LIGHT) ok = true;
                if ((--it2)->second == LIGHT) ok = true;

                ans += ok;
            }
        }
    }
    cout << ans << endl;

    
    


    return 0;
}
