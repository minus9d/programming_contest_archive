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

class UnionFind
{
public:
    UnionFind(int num_entries)
    {
        num_entries_ = num_entries;
        par_.resize(num_entries_);
        rank_.resize(num_entries_, 0);
        member_num_.resize(num_entries_, 1);
        edge_num_.resize(num_entries, 0);
        REP(i, num_entries_)
        {
            par_[i] = i;
        }
    }
    ~UnionFind(){};
    int find(int x)
    {
        if (par_[x] == x)
            return x;
        else
            return par_[x] = find(par_[x]);
    }
    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
        {
            edge_num_[x]++;
            return;
        }
        if (rank_[x] < rank_[y])
        {
            par_[x] = y;
            member_num_[y] += member_num_[x];
            member_num_[x] = 0;
            edge_num_[y] += edge_num_[x] + 1;
        }
        else
        {
            par_[y] = x;
            member_num_[x] += member_num_[y];
            member_num_[y] = 0;
            edge_num_[x] += edge_num_[y] + 1;
            if (rank_[x] == rank_[y])
                rank_[x]++;
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int vertex_size(int x)
    {
        return member_num_[this->find(x)];
    }
    int edge_size(int x)
    {
        return edge_num_[this->find(x)];
    }

private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
    std::vector<int> member_num_;
    std::vector<int> edge_num_;
};


ll N, M;

ll func(ll gcd_val1, ll gcd_val2, ll cost1, ll cost2) {
    ll group_num = gcd_val1;
    ll group_size = N / group_num;

    ll ret = group_num * (group_size - 1) * cost1;
    ret += (group_num - 1) * cost2;

    return ret;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;

    vector<pair<ll, ll>> CAs(M);
    REP(m, M) {
        ll a, c; cin >> a >> c;
        CAs[m] = {c, a};
    }
    sort(ALL(CAs));

    ll MAX = 1e18 + 100;
    ll ans = MAX;
    map<ll, ll> gcd_to_cost;
    for(auto [c, a]: CAs) {
        auto gcd_val = gcd(a, N);

        if (gcd_val == 1) {
            // 互いに素なら１個でいける
            chmin(ans, c * (N - 1));
        }

        if (gcd_to_cost.count(gcd_val)) {
            chmin(gcd_to_cost[gcd_val], c);
        } else {
            gcd_to_cost[gcd_val] = c;
        }
    }

    vector<pair<ll, ll>> cost_and_gcd_vals;
    for(auto [gcd_val, cost] : gcd_to_cost) {
        cost_and_gcd_vals.pb({cost, gcd_val});
    }
    sort(ALL(cost_and_gcd_vals));

    ll group_num = N;
    ll group_size = 1;
    ll curr_gcd = N;
    ll ans2 = 0;
    for(auto [cost, gcd_val]: cost_and_gcd_vals) {
        ll next_gcd = gcd(curr_gcd, gcd_val);
        if (next_gcd == curr_gcd) continue;

        // group_sizeが curr_gcd(12) / next_gcd(6) 倍
        // group_numが  next_gcd(6) / curr_gcd(12) 倍
        
        ll after_group_num = group_num * next_gcd / curr_gcd;
        ll after_group_size = group_size * curr_gcd / next_gcd;

        ans2 += (group_num - after_group_num) * cost;

        group_num = after_group_num;
        group_size = after_group_size;
        curr_gcd = next_gcd;

        // cout << "group_num = " << group_num << endl;
        // cout << "group_size = " << group_size << endl; 
        // cout << "curr_gcd = " << curr_gcd << endl;
        // cout << "curr ans = " << ans2 << endl;
        // cout << endl;
    }

    if (group_size == N) {
        chmin(ans, ans2);
    }
    
    if (ans == MAX) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
