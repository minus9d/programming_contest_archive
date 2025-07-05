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

// 多重vector
// e.g. auto vec = make_v<ll>(2, 3, 4);
template <typename T>
vector<T> make_v(size_t a) { return vector<T>(a); }
template <typename T, typename... Ts>
auto make_v(size_t a, Ts... ts)
{
    return vector<decltype(make_v<T>(ts...))>(a, make_v<T>(ts...));
}

// 多重vectorのfill その1
// 組み込み型の多重vectorに使う
// e.g. fill_v(vec, 777);
template <typename T, typename V>
typename enable_if<is_class<T>::value == 0>::type
fill_v(T &t, const V &v) { t = v; }
template <typename T, typename V>
typename enable_if<is_class<T>::value != 0>::type
fill_v(T &t, const V &v)
{
    for (auto &e : t)
        fill_v(e, v);
}

// 多重vectorのfill その2
// 非組み込み型の多重vectorに使う
// e.g. fill_v2<mint>(vec, 777);
template <typename T, typename U, typename... V>
typename enable_if<is_same<T, U>::value != 0>::type
fill_v2(U &u, const V... v) { u = U(v...); }
template <typename T, typename U, typename... V>
typename enable_if<is_same<T, U>::value == 0>::type
fill_v2(U &u, const V... v)
{
    for (auto &e : u)
        fill_v2<T>(e, v...);
}

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

    int H, W, K;
    cin >> H >> W >> K;

    ll INF = 1e9;
    vector<vector<ll>> cells(H, vector<ll>(W, INF));

    vector<pair<int, int>> seen;
    REP(k, K) {
        int r, c; cin >> r >> c; --r; --c;
        cells[r][c] = 0;
        seen.push_back({r, c});
    }

    // REP(r, H) {
    //     REP(c, W) {
    //         cout << cells[r][c] << " ";
    //     }
    //     cout << endl;
    // }

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0}; 

    while (1) {

        vector<pair<int, int>> next;
        vector<tuple<int, int, int>> record;
        set<ll> checked;

        for(auto s: seen) {

            int r = s.first;
            int c = s.second;
            // cout << "here. seen = (" << r << "," << c << ")" << endl;
    
            REP(d, 4) {
                int r2 = r + dr[d];
                int c2 = c + dc[d];
    
                if (r2 < 0 or r2 >= H or c2 < 0 or c2 >= W) continue;
                if (checked.count(r2 * 10000 + c2)) continue;
                if (cells[r2][c2] != INF) continue;

                // cout << "here. r2 = (" << r2 << "," << c2 << ")" << endl;
                checked.insert(r2 * 10000 + c2);
                
                vector<int> neigh;
                REP(d2, 4) {
                    int r3 = r2 + dr[d2];
                    int c3 = c2 + dc[d2];
                    if (r3 < 0 or r3 >= H or c3 < 0 or c3 >= W) continue;
                    neigh.push_back(cells[r3][c3]);
                }
                sort(ALL(neigh));

                // cout << "neigh:" << endl;
                // for(auto n: neigh) cout << n << " ";
                // cout << endl;

                if (neigh[1] != INF) {
                    next.push_back({r2, c2});
                    record.push_back({r2, c2, neigh[1] + 1});
                }
            }
        }
        // cout << "here. next size = " << SIZE(next) << endl;

        if (SIZE(next)) {
            seen = move(next);
            for(auto& [r, c, score]: record) {
                cells[r][c] = score;
            }
        } else {
            break;
        }
    }

    ll ans = 0;
    REP(r, H) {
        REP(c, W) {
            if (cells[r][c] != INF) {
                ans += cells[r][c];
            }
        }
    }
    cout << ans << endl;
    
    return 0;
}
