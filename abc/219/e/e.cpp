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


    int N = 4;
    vector<vector<int>> cells(N, vector<int>(N));
    REP(y, N) {
        REP(x, N) {
            cin >> cells[y][x];
        }
    }


    set<vector<vector<int>>> seen;

    REP(i, (1 << (N * N))) {
        bool ok = true;
        REP(j, N * N) {
            bool col = ((1 << j) & i);
            int y = j / 4;
            int x = j % 4;
            // cout << "y, x = " << y << "," << x << endl;
            // cout << "col - " << col << endl; // 
            if (cells[y][x] == 1 && !col) {
                ok = false;
                break;
            }
        }

        // REP(j, 16) {
        //     bool col = ((1 << j) & i);
        //     cout << int(col);
        //     if (j % 4 == 3) cout << endl;
        // }
        // cout << endl;

        // debug
        if (ok) {
            // cout << "i = " << i << endl;
            // REP(j, 16) {
            //     bool col = ((1 << j) & i);
            //     cout << int(col);
            //     if (j % 4 == 3) cout << endl;
            // }
            // cout << endl;

            vector<vector<int>> cells2(N, vector<int>(N));
            UnionFind uf(N * N);
            REP(j, 16) {
                int y = j / 4;
                int x = j % 4;
                bool col = ((1 << j) & i);
                if (col) {
                    cells2[y][x] = 1;
                }
                
                if (x != 0 && cells2[y][x] == 1 && cells2[y][x - 1] == 1) {
                    uf.unite(y * N + x, y * N + x - 1);
                }
                if (y != 0 && cells2[y][x] == 1 && cells2[y - 1][x] == 1) {
                    uf.unite(y * N + x, (y - 1) * N + x);
                }
            }

            int prev_id = -1;
            REP(j, 16) {
                bool col = ((1 << j) & i);
                if (!col) continue;
                auto id = uf.find(j);
                if (prev_id == -1) {
                    prev_id = id;
                } else {
                    if (prev_id != id) {
                        ok = false;
                        break;
                    }
                }
            }

            if (!ok) {
                continue;
            }

            // ここまでくれば連結性は保証される

            // 6x6の真ん中に4x4を貼ることで
            // 内部の穴を無視する
            vector<vector<int>> cells3(N + 2, vector<int>(N + 2));
            UnionFind uf3(6 * 6);
            REP(y, N) {
                REP(x, N) {
                    if (cells2[y][x]) {
                        cells3[y + 1][x + 1] = 1;
                    }
                }
            }
            // 白で連結
            REP(y, N + 2) {
                REP(x, N + 2) {
                    if (x != 0 && cells3[y][x] == 0 && cells3[y][x - 1] == 0) {
                        uf3.unite(y * (N + 2) + x, y * (N + 2) + x - 1);
                    }
                    if (y != 0 && cells3[y][x] == 0 && cells3[y - 1][x] == 0) {
                        uf3.unite(y * (N + 2) + x, (y - 1) * (N + 2) + x);
                    }
                }
            }
            // 空洞を塗りつぶしたのを作成
            int id_outside = uf3.find(0);
            vector<vector<int>> cells4(N, vector<int>(N));
            REP(y, N) {
                REP(x, N) {
                    int y2 = y + 1;
                    int x2 = x + 1;
                    int idx = y2 * (N + 2) + x2;
                    if (!(uf3.find(idx) == id_outside)) {
                        cells4[y][x] = 1;
                    }
                }
            }
            seen.insert(cells4);

            // cout << "before" << endl;
            // cout << "i = " << i << endl;
            // REP(j, 16) {
            //     bool col = ((1 << j) & i);
            //     cout << int(col);
            //     if (j % 4 == 3) cout << endl;
            // }
            // cout << endl;
            // cout << "after" << endl;
            // cout << "i = " << i << endl;
            // REP(y, 4) {
            //     REP(x, 4) {
            //         cout << cells4[y][x];
            //     }
            //     cout << endl;
            // }
            // cout << endl;
        }
    }

    cout << SIZE(seen) << endl;

    return 0;
}
