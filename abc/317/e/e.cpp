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

void fill(vector<string>& cells, vector<string>& cells2, int H, int W, int h, int w) {
    int dh = 0;
    int dw = 0;
    auto ch = cells[h][w];
    if (ch == '>') {
        dw = 1;
    } else if (ch == 'v') {
        dh = 1;
    } else if (ch == '<') {
        dw = -1;
    } else if (ch == '^') {
        dh = -1;
    }

    while(1) {
        w += dw; h += dh;
        if (w < 0 or h < 0 or w >= W or h >= H) {
            break;
        }
        if (cells[h][w] == '.') {
            cells2[h][w] = '!';
        } else {
            break;
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int H, W;
    cin >> H >> W;
    vector<string> cells(H);
    REP(h, H) cin >> cells[h];

    int start_w = -1;
    int start_h = -1;
    auto cells2 = cells;
    REP(h, H) {
        REP(w, W) {
            auto ch = cells[h][w];
            if (ch == '>' or ch == 'v' or ch == '<' or ch == '^') {
                fill(cells, cells2, H, W, h, w);
            }
            if (ch == 'S') {
                start_w = w;
                start_h = h;
            }
        }
    }

    // REP(h, H) {
    //     cout << cells2[h] << endl;
    // }

    vector<vector<int>> steps(H, vector<int>(W, -1));
    steps[start_h][start_w] = 0;

    queue<tuple<int, int, int>> q;
    q.push({start_w, start_h, 0});

    while(!q.empty()) {
        int dh[] = {0, 0, 1, -1};
        int dw[] = {1, -1, 0, 0};
        
        auto [w, h, step] = q.front(); q.pop();
        // cout << "w, h, step = " << w << "," << h << "," << step << endl;

        REP(d, 4) {
            auto w2 = w + dw[d];
            auto h2 = h + dh[d];

            // はみでる
            if (w2 < 0 or h2 < 0 or w2 >= W or h2 >= H) continue;
            // 訪問済
            if (steps[h2][w2] != -1) continue;
            // cout << "w2, h2, step = " << w2 << "," << h2 << "," << step << endl;

            // 行けない
            if (!(cells2[h2][w2] == '.' or cells2[h2][w2] == 'G')) {
                continue;
            }

            steps[h2][w2] = step + 1;
            q.push({w2, h2, step + 1});
            if (cells[h2][w2] == 'G') {
                cout << step + 1 << endl;
                return 0;
            }
        }
    }
    cout << -1 << endl;
    return 0;
}
