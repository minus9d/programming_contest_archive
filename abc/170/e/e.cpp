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

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, Q;
    cin >> N >> Q;

    vector<int> loc(N + 1);
    vector<int> smarts(N + 1);
    vector<multiset<int, greater<int>>> schools(200001);
    REP(n, N) {
        int a, b;
        cin >> a >> b;
        schools[b].insert(a);
        loc[n + 1] = b;
        smarts[n + 1] = a;
    }

    multiset<int> greats;
    for(auto school: schools) {
        if (!school.empty()) {
            greats.insert(*school.begin());
        }
    }

    REP(q, Q) {
        int c, next_loc;
        cin >> c >> next_loc;
        int cur_loc = loc[c];
        int smart = smarts[c];

        auto& cur_school = schools[cur_loc];
        auto& next_school = schools[next_loc];

        auto cur_best_smart = *cur_school.begin();
        cur_school.erase(cur_school.find(smart));

        if (cur_school.empty()) {
            greats.erase(greats.find(cur_best_smart));
        }
        else if (*cur_school.begin() != cur_best_smart) {
            greats.erase(greats.find(cur_best_smart));
            greats.insert(*cur_school.begin());
        }


        if (next_school.empty()) {
            next_school.insert(smart);
            greats.insert(smart);
        }
        else {
            auto next_best_smart = *next_school.begin();
            next_school.insert(smart);
            if (*next_school.begin() != next_best_smart) {
                greats.erase(greats.find(next_best_smart));
                greats.insert(*next_school.begin());
            }
        }

        loc[c] = next_loc;


        cout << *greats.begin() << endl;
    }


    return 0;
}
