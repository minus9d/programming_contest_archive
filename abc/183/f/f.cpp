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

class UnionFind
{
public:
    UnionFind(){};
    ~UnionFind(){};
    void init(int num_entries) {
        num_entries_ = num_entries;
        par_.resize(num_entries_);
        rank_.resize(num_entries_, 0);
        member_num_.resize(num_entries_, 1);
        REP(i, num_entries_) {
            par_[i] = i;
        }
    }
    int find(int x) {
        if (par_[x] == x) return x;
        else return par_[x] = find(par_[x]);
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (rank_[x] < rank_[y]) {
            par_[x] = y;
            member_num_[y] += member_num_[x];
            member_num_[x] = 0;
        } else {
            par_[y] = x;
            member_num_[x] += member_num_[y];
            member_num_[y] = 0;
            if (rank_[x] == rank_[y]) rank_[x]++;
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) {
        return member_num_[this->find(x)];
    }
private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
    std::vector<int> member_num_;
};

map<int, int> merge(map<int, int>& m1, map<int, int>& m2) {
    for(auto kv: m2) {
        m1[kv.first] += kv.second;
    }
    return move(m1);
}

vector<ll> solve_slow(int N, int Q, vector<int> Cs, vector<tuple<int, int, int>> queries) {
    vector<ll> ans;

    UnionFind uf;
    uf.init(N);

    REP(q, Q) {
        int type = get<0>(queries[q]);
        int i = get<1>(queries[q]);
        int j = get<2>(queries[q]);
        
        if (type == 1) {
            int id1 = uf.find(i);
            int id2 = uf.find(j);
            if (id1 == id2) continue;
            uf.unite(i, j);
        }
        else {
            int id_of_x = uf.find(i);

            int cnt = 0;
            REP(n, N) {
                int id_of_n = uf.find(n);
                if (id_of_n == id_of_x && Cs[n] == j) ++cnt;
            }
            ans.pb(cnt);
        }
    }
    return ans;
}    


vector<ll> solve_fast(int N, int Q, vector<int> Cs, vector<tuple<int, int, int>> queries) {

    vector<map<int, int>> id2map(N);
    vector<int> student2id(N);
    REP(n, N) {
        auto c = Cs[n];
        id2map[n][c] = 1;
        student2id[n] = n;
    }

    vector<ll> ans;

    UnionFind uf;
    uf.init(N);

    REP(q, Q) {
        int type = get<0>(queries[q]);
        int i = get<1>(queries[q]);
        int j = get<2>(queries[q]);
        

        if (type == 1) {
            int id1 = uf.find(i);
            int id2 = uf.find(j);

            if (id1 == id2) continue;

            uf.unite(i, j);

            int newid = uf.find(i);
            
            student2id[i] = newid;
            student2id[j] = newid;

            auto& m1 = id2map[id1];
            auto& m2 = id2map[id2];
            if (SIZE(m1) > SIZE(m2)) {
                id2map[newid] = move(merge(m1, m2));
            } else {
                id2map[newid] = move(merge(m2, m1));
            }
        }
        else {
            int id_of_x = uf.find(i);
            auto& m = id2map[id_of_x];
            ans.pb(m[j]);
        }
    }
    return ans;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, Q;
    cin >> N >> Q;

    vector<int> Cs(N);
    REP(n, N) {
        int c; cin >> c; --c;
        Cs[n] = c;
    }

    vector<tuple<int, int, int>> queries;
    REP(q, Q) {
        int a, b, c;
        cin >> a >> b >> c;
        --b; --c;
        queries.pb(mt(a, b, c));
    }

    auto ans_fast = solve_fast(N, Q, Cs, queries);
    for(auto a: ans_fast) {
        cout << a << endl;
    }

    // while(1) {
    //     int N = 1000;
    //     int Q = 1000;
    //     vector<int> Cs(N);
    //     REP(n, N) {
    //         Cs[n] = rand() % N;
    //     }
    //     vector<tuple<int, int, int>> queries;
    //     REP(q, Q) {
    //         int type = rand() % 2 + 1;
    //         int i = rand() % N;
    //         int j = rand() % N;
    //         queries.pb(mt(type, i, j));
    //     }

    //     auto ans_slow = solve_slow(N, Q, Cs, queries);
    //     auto ans_fast = solve_fast(N, Q, Cs, queries);
     
    //     if (ans_slow != ans_fast) {
    //         cout << "panic!" << endl;
    //         cout << N << " " << Q << endl;
    //         REP(n, N) cout << Cs[n] << " ";
    //         cout << endl;
    //         for(auto q: queries) {
    //             cout << get<0>(q) << " "
    //                  << get<1>(q) << " "
    //                  << get<2>(q) << endl;
    //         }
    //     } else {
    //         cout << "ok!" << endl;
    //     }
    // }


    return 0;
}
