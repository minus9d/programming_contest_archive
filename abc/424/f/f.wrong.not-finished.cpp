// 本番中に考えていた回答
//
// 以下のパターンでNG
// 8 4
// 4 5
// 7 8 
// 2 3
// 1 6
//

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

// pから時計回りで最初にある点
int find_cw(set<int>& points, int p) {

    auto it = points.lower_bound(p);
    ++it;
    if (it == points.end()) {
        return *points.begin();
    } else {
        return *it;
    }
}

// pから反時計回りで最初にある点
int find_ccw(set<int>& points, int p) {

    auto it = points.lower_bound(p);
    if (it == points.begin()) {
        return *points.rbegin();
    } else {
        --it;
        return *it;
    }
}


// https://atcoder.jp/contests/abc424/submissions/69461365

struct SegTreeMax {
    int n;
    vector<int> seg;
    SegTreeMax(int sz=0){ init(sz); }
    void init(int sz){
        n = 1;
        while(n < sz) n <<= 1;
        seg.assign(2*n, 0);
    }
    // point update: set position p (1-indexed) to value v
    void setval(int p, int v){
        p += n - 1;
        seg[p] = v;
        for(p >>= 1; p; p >>= 1) seg[p] = max(seg[p<<1], seg[p<<1|1]);
    }
    // query max on [l, r] (1-indexed, inclusive)
    int query(int l, int r){
        if(l > r) return 0;
        l += n - 1; r += n - 1;
        int res = 0;
        while(l <= r){
            if(l & 1) res = max(res, seg[l++]);
            if(!(r & 1)) res = max(res, seg[r--]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

struct SegTreeMin {
    int n;
    vector<int> seg;
    const int INF = 1e9;
    SegTreeMin(int sz=0){ init(sz); }
    void init(int sz){
        n = 1;
        while(n < sz) n <<= 1;
        seg.assign(2*n, INF);
    }
    // point update: set position p (1-indexed) to value v
    void setval(int p, int v){
        p += n - 1;
        seg[p] = v;
        for(p >>= 1; p; p >>= 1) seg[p] = min(seg[p<<1], seg[p<<1|1]);
    }
    // query min on [l, r] (1-indexed, inclusive)
    int query(int l, int r){
        if(l > r) return INF;
        l += n - 1; r += n - 1;
        int res = INF;
        while(l <= r){
            if(l & 1) res = min(res, seg[l++]);
            if(!(r & 1)) res = min(res, seg[r--]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

vector<string> solve_gt(int N, int Q, vector<pair<int, int>>& qs) {

    SegTreeMax segMax(N+2);
    SegTreeMin segMin(N+2);

    vector<string> ans;
    for(auto &p : qs){
        int a = p.first, b = p.second;
        // check inside interval (a,b): positions a+1 .. b-1
        int l = a + 1, r = b - 1;
        bool intersects = false;
        if(l <= r){
            int max_right = segMax.query(l, r);
            if(max_right > b) intersects = true;
            int min_left = segMin.query(l, r);
            if(min_left < a) intersects = true;
        }
        if(intersects){
            ans.push_back("No");
            cout << "here..." << endl;
        }else{
            ans.push_back("Yes");
            // insert this chord: left at a stores right b; right at b stores left a
            segMax.setval(a, b);
            segMin.setval(b, a);
        }
    }    
    return ans;
}


vector<string> solve(int N, int Q, vector<pair<int, int>>& AB) {
    set<int> points;
    vector<pair<int, int>> point2pair(N + 1);

    set<pair<int, int>> edge;

    vector<string> ans;
    REP(q, Q) {

        // cout << "[q == " << q << endl;
        auto [a, b] = AB[q];

        if (q == 0) {
            ans.push_back("Yes");

            points.insert(a);
            point2pair[a] = {a, b};

            points.insert(b);
            point2pair[b] = {a, b};

            edge.insert({a, b});


        } else {
            // 仮に入れてみる
            points.insert(a);
            points.insert(b);

            // // for debug
            // for(auto p:  points) {
            //     cout << p << ",";
            // }
            // cout<< endl;

            // cout << "a, b = " << a << "," << b << endl;
            // cout << "find_cw(points, a) = " << find_cw(points, a) << endl;
            // cout << "find_cw(points, b) = " << find_cw(points, b) << endl;
            // cout << "find_ccw(points, a) = " << find_ccw(points, a) << endl;
            // cout << "find_ccw(points, b) = " << find_ccw(points, b) << endl;

            // 連番だったらOK
            if (find_cw(points, a) == b or find_cw(points, b) == a) {
                ans.push_back("Yes");
                point2pair[a] = {a, b};
                point2pair[b] = {a, b};
                edge.insert({a, b});
                continue;
            }

            // 並走している辺が同じならOK
            int p1 = find_cw(points, a);
            int p2 = find_ccw(points, b);

            int p3 = find_ccw(points, a);
            int p4 = find_cw(points, b);

            if (edge.count({min({p1, p2}), max({p1, p2})}) and
                edge.count({min({p3, p4}), max({p3, p4})}))
            {
                ans.push_back("Yes");
                point2pair[a] = {a, b};
                point2pair[b] = {a, b};
                edge.insert({a, b});
                continue;
            }

            // NGの場合は消す
            ans.push_back("No");
            points.erase(a);
            points.erase(b);
        }
    }    
    return ans;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; int Q;
    cin >> N >> Q;

    // for debug
    N = 8; Q = 4;
    vector<int> nums;
    REP(n, N) nums.push_back(n + 1);
    while(1) {
        random_shuffle(ALL(nums));
        vector<pair<int, int>> AB(Q);
        REP(q, Q) {
            auto mn = min({nums[q * 2], nums[q * 2 + 1]});
            auto mx = max({nums[q * 2], nums[q * 2 + 1]});
            AB[q] = {mn, mx};
        }

        auto mine = solve(N, Q, AB);
        auto gt = solve_gt(N, Q, AB);

        if (mine != gt) {

            for(auto [a, b]: AB) {
                cout << "(" << a << "," << b << "), ";
            }
            cout << endl;
    
            cout << "mine: ";
            for(auto r: mine) {
                cout << r << ", ";
            }
            cout << endl;

            cout << "  gt: ";
            for(auto r: gt) {
                cout << r << ", ";
            }
            cout << endl;
            cout << endl;
        }
    }


    vector<pair<int, int>> AB(Q);
    REP(q, Q) {
        int a, b; cin >> a >> b;
        AB[q] = {a, b};
    }

    auto ret = solve(N, Q, AB);
    for(auto r: ret) {
        cout << r << endl;
    }

    return 0;
}
