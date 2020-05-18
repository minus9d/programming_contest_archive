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

ll getGcdSimple(const ll a, const ll b)
{
    if (b == 0) return a;
    return getGcdSimple(b, a % b);
}

mint pow2(ll base, ll cnt) {
    mint ans = 1;
    REP(i, cnt) ans *= base;
    return ans;
}

ll solve_slow(int N, vector<P> XYs) {
    ll ans = 0;
    REP(i, (1 << N)) {
        vector<P> v;
        REP(j, N) {
            if (i & (1 << j)) v.push_back(XYs[j]);
        }

        int len = SIZE(v);
        bool ok = true;
        REP(s, len - 1) {
            FOR(t, s + 1, len) {
                auto& pt1 = v[s];
                auto& pt2 = v[t];
                if (pt1.first * pt2.first + pt1.second * pt2.second == 0) {
                    ok = false;
                    break;
                }
            }
        }
        ans += ok;
    }
    return ans - 1;
}

ll solve_fast(int N, vector<P> XYs) {

    map<P, int> cnt;

    ll zerozero_num = 0;

    REP(n, N) {
        auto x = XYs[n].first;
        auto y = XYs[n].second;

        if (x < 0) {
            x *= -1;
            y *= -1;
        }
        if (x == 0 && y == 0) {
            zerozero_num++;
            continue;
            // do nothing
        }
        else if (x == 0) {
            y = 1;
        }
        else if (y == 0) {
            x = 1;
        }
        else {
            ll gcd = getGcdSimple(abs(x), abs(y));
            x /= gcd;
            y /= gcd;
        }
        cnt[{x, y}]++;
    }

    vector<P> keys;
    for (auto kv : cnt) {
        keys.pb(kv.first);
    }

    mint ans = 1;
    set<P> seen;
    for (auto xy : keys) {
        auto c = cnt[xy];

        if (seen.count(xy)) continue;
        seen.insert(xy);

        // 例外 （(1, 0) に 直交するのは (0, 1)） を考慮
        ll c2 = 0;
        {
            P xy2{ xy.second, -xy.first };
            chmax(c2, (ll)cnt[xy2]);
            seen.insert(xy2);

            xy2.first *= -1;
            xy2.second *= -1;
            chmax(c2, (ll)cnt[xy2]);
            seen.insert(xy2);
        }


        mint tmp = (pow2(2, c) - 1) + (pow2(2, c2) - 1) + 1;
        ans *= tmp;

        //cout << xy.first << "," << xy.second << ":" << c << endl;
    }
    ans -= 1;

    // 原点にいるやつは単独でOK
    ans += zerozero_num;


    return ans.val;
}


int main(void)
{
    while (true) {
        int N = 10;
        vector<P> vec;
        REP(n, N) {
            vec.push_back({ rand() % 10 - 5, rand() % 10 - 5 });
        }
        auto gt = solve_slow(N, vec);
        auto mine = solve_fast(N, vec);
        if (gt != mine) {
            cout << N << endl;
            for (auto v : vec) cout << v.first << " " << v.second << endl;
            cout << endl;
            cout << solve_slow(N, vec) << endl;
            cout << solve_fast(N, vec) << endl;
            return 0;
        }
    }

    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    vector<P> XYs(N);
    REP(n, N) {
        ll x, y;
        cin >> x >> y;
        XYs[n] = mp(x, y);
    }
    cout << solve_fast(N, XYs) << endl;
    return 0;
}
