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

ll div2_num(ll n) {
    ll ret = 0;
    while (n > 0) {
        if (n % 2 == 0) {
            ret++;
            n /= 2;
        }
        else {
            break;
        }
    }
    return ret;
}

string change_if(ll &val, ll step, bool EW_flag) {
    ll next_step = step * 2;

    ll val2 = val + step;
    ll val3 = val - step;

    ll value2 = div2_num(abs(val2));
    ll value3 = div2_num(abs(val3));

    bool flag = true;
    if (val2 == 0) {
        flag = true;
    }
    else if (val3 == 0) {
        flag = false;
    }
    else if (value2 > value3) {
        flag = true;
    }
    else {
        flag = false;
    }

 
    if (flag) {
        val = val2;
        if (EW_flag) {
            return "E";
        }
        else {
            return "N";
        }
    }
    else {
        val = val3;
        if (EW_flag) {
            return "W";
        }
        else {
            return "S";
        }
    }

    // fail
    return "";
}

const string IMP = "IMPOSSIBLE";

string solve_large(ll X, ll Y, ll step) {

    string ret = "";

    if (X == 0 && Y == 0) {
        return "";
    }

    if (abs(X) % step != 0 || abs(Y) % step != 0) {
        return IMP;
    };

    if (X == 0) {
        if (Y == step) {
            return "S";
        }
        else if (-Y == step) {
            return "N";
        }
    }
    else if (Y == 0) {
        if (X == step) {
            return "W";
        }
        else if (-Y == step) {
            return "E";
        }
    }

    //cout << "X, Y = " << X << " " << Y << endl;


    ll next_step = step * 2;
    if (abs(X) % next_step != 0) {
        if (abs(X + step) % (step * 2) == 0) {
            auto res = solve_large(X + step, Y, step * 2);
            if (res != IMP) {
                return "E" + res;
            }
        }
        if (abs(X - step) % (step * 2) == 0) {
            auto res = solve_large(X - step, Y, step * 2);
            if (res != IMP) {
                return "W" + res;
            }
        }
    }
    else {
        if (abs(Y + step) % (step * 2) == 0) {
            auto res = solve_large(X, Y + step, step * 2);
            if (res != IMP) {
                return "N" + res;
            }
        }
        if (abs(Y - step) % (step * 2) == 0) {
            auto res = solve_large(X, Y - step, step * 2);
            if (res != IMP) {
                return "S" + res;
            }
        }
    }
    return IMP;
}

string solve_100(ll X, ll Y) {
    vector<ll> steps;
    ll tmp = 1;
    REP(n, 10) {
        steps.pb(tmp);
        tmp *= 2;
    }

    vector<tuple<ll, ll, string>> cands;
    cands.pb(mt(0, 0, ""));
    ll step = 1;
    REP(rep, 10) {
        //cout << "cands:" << endl;
        //for (auto c : cands) {
        //    cout << "  (x, y) = " << get<0>(c) << ", " << get<1>(c) << " " << get<2>(c) << endl;
        //}

        vector<tuple<ll, ll, string>> new_cands;
        for (auto c : cands) {
            auto x = get<0>(c);
            auto y = get<1>(c);
            auto s = get<2>(c);

            if (x == X && y == Y) {
                return s;
            }

            new_cands.push_back(mt(x + step, y, s + "E"));
            new_cands.push_back(mt(x - step, y, s + "W"));
            new_cands.push_back(mt(x, y + step, s + "N"));
            new_cands.push_back(mt(x, y - step, s + "S"));
        }
        cands = new_cands;
        step *= 2;
    }

    return "IMPOSSIBLE";
}

void solve() {
    ll X, Y;
    cin >> X >> Y;

    auto res = solve_large(X, Y, 1);
    if (res == IMP) cout << IMP;
    else {
        string res2;
        for (auto ch : res) {
            if (ch == 'W') res2 += "E";
            if (ch == 'E') res2 += "W";
            if (ch == 'N') res2 += "S";
            if (ch == 'S') res2 += "N";
        }
        cout << res2;
    }



    //if (abs(X) <= 100 && abs(Y) <= 100) {
    //    cout << solve_100(X, Y);
    //}
    //else {
    //    cout << solve_large(X, Y);
    //}


}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
