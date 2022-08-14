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

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, E; cin >> N >> M >> E;
    vector<pair<int, int>> edges(E);
    REP(e, E) {
        int u, v; cin >> u >> v; --u; --v;
        edges[e] = {u, v};
    }

    int Q; cin >> Q;
    vector<int> X(Q);
    REP(q, Q) {
        int x; cin >> x; --x;
        X[q] = x;
    }
    set<int> X_set(ALL(X));

    // fakeのedgeを入れる
    REP(e, E) {
        if (X_set.count(e)) continue;
        X.pb(e);
    }

    // 発電所につながっているid
    set<int> connect_id;
    int connect_num = 0;
    vector<int> ans;

    UnionFind uf(N); // 都市だけ

    reverse(ALL(X));

    for(auto x: X) {
        auto[v1, v2] = edges[x];

        auto u = min(v1, v2);
        auto v = max(v1, v2);

        // 都市同士をつなぐ
        if (v < N) {
            auto u_id = uf.find(u);
            auto v_id = uf.find(v);

            // 両方通電済
            if (connect_id.count(u_id) && 
                connect_id.count(v_id)) {
                // pass
            }
            // 両方通電していない
            else if (!connect_id.count(u_id) && 
                     !connect_id.count(v_id)) {
                // pass
            }
            // 片方のみ通電
            else {
                // 通電してない方をa
                int a;
                if (connect_id.count(u_id)) {
                    a = v;
                } else {
                    a = u;
                }
                connect_num += uf.vertex_size(a);
                connect_id.insert(u_id);
                connect_id.insert(v_id);
            }

            // 結合は常にする
            uf.unite(u, v);
        }
        // 発電所同士をつなぐ
        else if (u >= N) {
            // pass
        }
        // 都市と発電所をつなぐ
        else {
            // assert (u < N);
            // assert (v >= N);
            auto u_id = uf.find(u);
            // すでに繋がってるなら何もしない
            if (connect_id.count(u_id)) {
                // pass
            } else {
                connect_id.insert(u_id);
                connect_num += uf.vertex_size(u_id);
            }
        }

        ans.pb(connect_num);
    }

    // for(auto a: ans ) cout << a << endl;
    // cout << endl;

    vector<int> ans2;
    int fake_num = E - Q;
    FOR(i, fake_num - 1, fake_num - 1 + Q) {
        ans2.pb(ans[i]);
    }

    reverse(ALL(ans2));
    for(auto a: ans2) cout << a << endl;

    return 0;
}
