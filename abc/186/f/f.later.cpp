// 公式解説と、https://drken1215.hatenablog.com/entry/2020/12/20/111600 を参考にして実装

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

// 区間加算に対応しないBIT
// 1 originなので注意!!
class BitSimple
{
private:
    int m_n;
    vector<int> m_bit;

public:
    void init(int n) {
        m_n = n;
        m_bit.resize(n + 1);
    }

    // 要素1から要素iまでの和
    int sum(int i) {
        int s = 0;
        while (i > 0) {
            s += m_bit[i];
            i -= i & -i;
        }
        return s;
    }

    void add(int i, int x) {
        while (i <= m_n) {
            m_bit[i] += x;
            i += i & -i;
        }
    }
};



ll slow(int H, int W, int M, vector<pair<int, int>> xys) {
    vector<vector<int>> cells(H, vector<int>(W));
    for (auto xy : xys) {
        auto h = xy.first;
        auto w = xy.second;
        cells[h][w] = -1;
    }
    REP(h, H) {
        if (cells[h][0] == -1) break;
        REP(w, W) {
            if (cells[h][w] == -1) break;
            cells[h][w] = 2;
        }
    }
    REP(w, W) {
        if (cells[0][w] == -1) break;
        REP(h, H) {
            if (cells[h][w] == -1) break;
            cells[h][w] = 2;
        }
    }
    ll ans = 0;
    REP(h, H) {
        REP(w, W) {
            ans += cells[h][w] == 2;
        }
    }
    return ans;
}

ll fast(int H, int W, int M, vector<pair<int, int>> xys) {
    // 最後に番兵を入れておく
    vector<vector<int>> row(H, {W});
    vector<vector<int>> col(W, {H});

    REP(m, M) {
        int x, y;
        tie(x, y) = xys[m];
        col[y].pb(x);
        row[x].pb(y);
    }
    REP(h, H) sort(ALL(row[h]));
    REP(w, W) sort(ALL(col[w]));

    ll ans = 0;
    // 横に行ってから縦
    REP(w, row[0][0])
    {
        ans += col[w][0];
    }

    BitSimple bit;
    bit.init(W + 1);

    // 縦に行ってから横
    REP(h, col[0][0]) {
        auto right_end = row[h][0];

        // ★0行目については、壁が右詰めされているものとみなす！★
        if (h == 0) {
            FOR(w2, right_end, W) {
                bit.add(w2 + 1, 1);
            }
        }
        else {
            ans += bit.sum(right_end);
            // ★まだ壁がないなら壁を足す！★
            for (auto w: row[h]) {
                if (bit.sum(w + 1) - bit.sum(w) == 0)
                {
                    bit.add(w + 1, 1);
                }
            }
        }
    }
    return ans;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // while (1) {
    //     int H = rand() % 10 + 1;
    //     int W = rand() % 10 + 1;
    //     set<pair<int, int>> seen;
    //     int M = min(rand() % 10 + 1, H * W - 1);
    //     while (SIZE(seen) < M) {
    //         int x = rand() % H;
    //         int y = rand() % W;
    //         if (x == 0 && y == 0) continue;
    //         seen.insert(mp(x, y));
    //     }
    //     auto xys = vector<pair<int, int>>(ALL(seen));
    //     auto f = fast(H, W, M, xys);
    //     auto s = slow(H, W, M, xys);
    //     if (f != s) {
    //         cout << "different!" << endl;
    //         cout << H << " " << W << " " << M << endl;
    //         for (auto xy : xys) {
    //             cout << xy.first << " " << xy.second << endl;
    //         }
    //         auto f2 = fast(H, W, M, xys);
    //         auto s2 = slow(H, W, M, xys);
    //         cout << "mine: " << f2 << ", gt: " << s2 << endl;
    //         return 0;
    //     }
    // }

    int H, W, M;
    cin >> H >> W >> M;

    vector<pair<int, int>> xys(M);
    REP(m, M) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        xys[m] = mp(x, y);
    }

    cout << fast(H, W, M, xys) << endl;

    return 0;
}
