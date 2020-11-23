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



pair<int, int> find_warp(map<char, vector<pair<int, int>>>& warp, int y, int x, char ch) {
    auto& vec = warp[ch];
    for(auto p: vec) {
        if (p.first == y && p.second == x) continue;
        else return p;
    }
    assert(-1);
}

using P = pair<int, int>;
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int H, W;
    cin >> H >> W;

    vector<string> cells(H);
    REP(h, H) {
        cin >> cells[h];
    }

    P start;
    P goal;
    map<char, vector<P>> warp;

    REP(y, H) {
        REP(x, W) {
            char ch = cells[y][x];
            if (ch == 'S') start = mp(y, x);
            else if (ch == 'G') goal = mp(y, x);
            else if (ch != '#' && ch != '.') {
                warp[ch].pb(mp(y, x));
            }
        }
    }

    vector<vector<int>> seen(H, vector<int>(W));

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    vector<vector<int>> record(H, vector<int>(W, -1));

    // <<y, x>, time>
    queue<pair<P, int>> q;
    q.push(mp(start, 0));
    int ans = -1;
    while(!q.empty()) {
        auto p = q.front(); q.pop();

        int y = p.first.first;
        int x = p.first.second;
        int time = p.second;
        seen[y][x] = 1;

        record[y][x] = time;

        if (p.first == goal) {
            ans = time;
            break;
        }

        if (warp.count(cells[y][x])) {
            for(auto s: warp[cells[y][x]]) {
                if (!seen[s.first][s.second]) {
                    seen[s.first][s.second] = 1;
                    q.push(mp(s, time + 1));
                }
            }
            // もうこのワープは使う必要ないので消す!!
            warp.erase(cells[y][x]);
        }

        REP(d, 4) {
            int x2 = x + dx[d];
            int y2 = y + dy[d];
            if (x2 < 0 || x2 >= W || y2 < 0 || y2 >= H) continue;
            if (cells[y2][x2] == '#') continue;
            if (seen[y2][x2]) continue;

            seen[y2][x2] = 1;
            q.push(mp(mp(y2, x2), time + 1));
        }
    }
    cout << ans << endl;
   
    // REP(h, H) {
    //     REP(w, W) {
    //         cerr << record[h][w] << "\t";
    //     }
    //     cerr << endl;
    // }



    return 0;
}
