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

// ありえる盤面をすべて作る
void dfs(int N, int h, int w, vector<vector<int>>& cells,
         vector<vector<vector<int>>>& legid) {
    if (h == N) {
        legid.pb(cells);
        return;
    }
    // 位置(h, w)に入りうる数を全探索
    FOR(n, 1, N + 1) {
        bool ok = true;
        REP(i, h) {
            if (cells[i][w] == n) {
                ok = false;
                break;
            }
        }
        REP(i, w) {
            if (cells[h][i] == n) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cells[h][w] = n;
            int next_w = w + 1;
            int next_h = h;
            if (next_w == N) {
                next_w = 0;
                next_h += 1;
            }
            dfs(N, next_h, next_w, cells, legid);
        }
    }
}

void solve_slow(int N, int K) {
    vector<vector<int>> cells(N, vector<int>(N));
    vector<vector<vector<int>>> legid;


    dfs(N, 0, 0, cells, legid);

    //for (auto l : legid) {
    //    for (auto line : l) {
    //        for (auto e : line) cout << e << " ";
    //        cout << endl;
    //    }
    //    cout << endl;
    //}

    for (auto l : legid) {
        int trace = 0;
        REP(n, N) trace += l[n][n];
        if (trace == K) {
            cout << "POSSIBLE" << endl;
            for (auto line : l) {
                for (auto e : line) cout << e << " ";
                cout << endl;
            }
            return;
        }
    }
    cout << "IMPOSSIBLE" << endl;

    return;
}

void solve() {
    int N, K;
    cin >> N >> K;
    if (N <= 5) {
        solve_slow(N, K);
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
    }
    return 0;
}
