// 最初Pythonで実装したが、再帰が深すぎてREやTLEになるのに気付かず...
// C++で書き直したら通った

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

vector<set<int>> child;
vector<int> parent;
vector<vector<int>> edges;
vector<ll> ans;
vector<ll> save;
ll s = 0;

void make_rooted (int v, int prev) {
    for (auto n: edges[v]) {
        if (n == prev) continue;
        child[v].insert(n);
        parent[n] = v;
        make_rooted(n, v);
    }
}

void dfs(int v) {
    ans[v] = s + save[v];
    for(auto c: child[v]) {
        save[c] += save[v];
        dfs(c);
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    child.resize(N);
    parent.resize(N);
    edges.resize(N);
    ans.resize(N);
    save.resize(N);
    vector<pair<int, int>> ABs;
    REP(n, N - 1) {
        int a, b; cin >> a >> b;
        --a; --b;
        edges[a].pb(b);
        edges[b].pb(a);
        ABs.pb(mp(a, b));
    }

    int root = 0;
    make_rooted(root, -1);

    int Q; cin >> Q;
    REP(q, Q) {
        int t, e, x;
        cin >> t >> e >> x;
        e -= 1;
        int a = ABs[e].first;
        int b = ABs[e].second;

        int add, block;
        if (t == 1) {
            add = a;
            block = b;
        } else {
            add = b;
            block = a;
        }
        if (child[add].count(block)) {
            s += x;
            save[block] -= x;
        }
        else {
            save[add] += x;
        }
    }

    dfs(root);
    REP(i, N) {
        cout << ans[i] << endl;
    }


    return 0;
}
