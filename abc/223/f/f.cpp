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
#include <atcoder/all>

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

// (1) 区間加算・区間最小値取得

// 各要素の型
using S = ll;
// 操作（写像）を表す値の型
using F = ll;
const S INF = 8e18;
// 区間取得をどのような演算で行うかを定義
S op(S a, S b) { return std::min(a, b); }
// 区間取得演算 op の単位元。基本、定数を返す
// 単位元 e とは、全ての a に対して op(a, e) = op(e, a) = a を満たすもの、
// つまり∞
S e() { return INF; }
// 操作f（e.g. 区間内の全要素に整数fを加算）を、
// 各ノードのdataの値 x に対して作用させる関数
S mapping(F f, S x) { return x + f; }
// 既にこれまでの操作を溜めている lazy に対して、さらに新しい操作を追加する関数
// gがこれまでの操作、fが後に追加する操作
// 可換でない場合は順番に注意
F composition(F f, F g) { return f + g; }
// 区間操作演算 mapping における恒等写像を返す関数。基本、定数を返す
// 全ての a に対してmapping(id, a) = a となるもの
// 区間加算操作の場合は、足しても絶対に対象の値を変えないような値、
// つまり0
F id() { return 0; }



int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, Q;
    cin >> N >> Q;
    string str;
    cin >> str;

    vector<ll> parencount;
    ll cnt = 0;
    parencount.pb(0);
    for(auto ch: str) {
        if (ch == '(') cnt++;
        else cnt--;
        parencount.pb(cnt);
    }

    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(parencount);


    REP(q, Q) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            if (str[l - 1] == str[r - 1]) {
                // do nothing
            }
            else if (str[l - 1] == '(') {
                seg.apply(l, r, -2);
                swap(str[l - 1], str[r - 1]);
            }
            else if (str[l - 1] == ')') {
                seg.apply(l, r, 2);
                swap(str[l - 1], str[r - 1]);
            }

        } else if (type == 2) {
            auto base = seg.prod(l - 1, l);
            if (
                base == seg.prod(r, r + 1)
                && seg.prod(l, r + 1) >= base) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
    

    // // data[p]を返す
    // REP(i, SIZE(v)) {
    //     REQUIRE(seg.get(i) == v[i]);
    // }
    // // 区間最小値 (op(a[l] .. a[r-1]))を返す
    // REQUIRE(seg.prod(0, 5) == 0);
    // REQUIRE(seg.prod(2, 4) == 2);
    // // 全区間の最小値を返す
    // REQUIRE(seg.all_prod() == 0);

    // // data[p]にxをセット
    // // v = {10, 1, 2, 3, 4}
    // seg.set(0, 10);
    // // 値が変わったことを確認
    // REQUIRE(seg.all_prod() == 1);

    // // data[2]に操作(7を加算)
    // // v = {10, 1, 9, 3, 4}
    // seg.apply(2, 7);
    // // 値が変わったことを確認
    // REQUIRE(seg.prod(2, 3) == 9);

    // // data[1, 2, 3]に操作(10を加算)
    // // v = {10, 11, 19, 13, 4}
    // seg.apply(1, 4, 10);
    // // 値が変わったことを確認
    // REQUIRE(seg.prod(0, 1) == 10);
    // REQUIRE(seg.prod(1, 2) == 11);
    // REQUIRE(seg.prod(2, 3) == 19);
    // REQUIRE(seg.prod(3, 4) == 13);
    // REQUIRE(seg.prod(4, 5) == 4);
    // REQUIRE(seg.all_prod() == 4);

    
    


    return 0;
}
