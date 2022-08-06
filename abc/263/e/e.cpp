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
constexpr ll MOD = 998244353;
using mint = Fp<MOD>;

#define pb push_back
#define mp make_pair
#define mt make_tuple

ll solve_slow(ll N, ll L, ll R, vector<ll>& A) {
    ll ans = 1e18;
    REP(i, N + 1) {
        auto B = A;
        REP(k, i) {
            B[k] = L;
        }
        REP(j, N + 1) {
            if (j != 0) {
                B[N - j] = R;
            }
            auto tmp = accumulate(ALL(B), 0LL);
            chmin(ans, tmp);
        }
    }
    return ans;
}

template <typename T>
class CumSum1D
{
public:
    CumSum1D(){};
    ~CumSum1D(){};
    void init(vector<T>& arr) {
        m_cum = arr;
        m_N = arr.size();
        FOR(i, 1, m_N) m_cum[i] += m_cum[i - 1];
    }
    // get sum of [l, r]. 0-based.
    T getSum(int l, int r) const {
        T ret = m_cum[r];
        if (l != 0) ret -= m_cum[l - 1];
        return ret;
    }
private:
    size_t m_N;
    vector<T> m_cum;
};

template <typename T>
class SegmentTreeMin
{
private:
    int m_n;
    vector<T> m_dat;
public:
    const T INF = std::numeric_limits<T>::max();
    SegmentTreeMin(int n) {
        m_n = 1;
        while  (m_n < n) m_n *= 2;
        m_dat.resize(2 * m_n - 1, INF);
    };
    void update(int k, T val) {
        k += m_n - 1;
        m_dat[k] = val;
        while (k > 0) {
            k = (k - 1) / 2;
            m_dat[k] = min(m_dat[k * 2 + 1], m_dat[k * 2 + 2]);
        }
    }
    // [a, b)の範囲で最小値を返す
    T query(int a, int b) {
        return queryInternal(a, b, 0, 0, m_n);
    }
private:
    T queryInternal(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return INF;
        if (a <= l && r <= b) return m_dat[k];
        else {
            T vl = queryInternal(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = queryInternal(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};

ll solve(ll N, ll L, ll R, vector<ll>& A) {
    vector<ll> all_l(N, L);
    vector<ll> all_r(N, R);
    vector<ll> rev_A = A;
    reverse(ALL(rev_A));

    auto left_cum = CumSum1D<ll>(); left_cum.init(A);
    auto l_cum = CumSum1D<ll>(); l_cum.init(all_l);
    auto right_cum = CumSum1D<ll>(); right_cum.init(rev_A);
    auto r_cum = CumSum1D<ll>(); r_cum.init(all_r);

    ll base_ans = accumulate(ALL(A), 0LL);
    // cout << "base = " << base_ans << endl;

    // 左側から、累積でどれだけ得かを計算
    SegmentTreeMin<ll> seg(N);
    REP(i, N) {
        auto tmp = l_cum.getSum(0, i) - left_cum.getSum(0, i);
        // cout << "change val = " << tmp << endl;
        seg.update(i, tmp);
    }

    ll min_change = 1e18;
    REP(r, N + 1) {
        ll change = 0;
        if (r != 0) {
            change = r_cum.getSum(0, r-1) - right_cum.getSum(0, r-1);
        }
        // cout << "r = " << r << ":" << endl;
        // cout << "  change = " << change << endl;

        if (r != N) {
            ll change_from_l = seg.query(0, N - r);
            chmin(change_from_l, 0LL);

            // cout << "  change_from_l = " << change_from_l << endl;
            change += change_from_l;
        }

        // cout << "  change = " << change << endl;
        chmin(min_change, change);
    }

    return base_ans + min_change;
}

// https://github.com/drken1215/algorithm/blob/master/DataStructure/binary_indexed_tree.cpp
// 区間加算にも対応した BIT (1-based)
// 参考: https://www.slideshare.net/hcpc_hokudai/binary-indexed-tree
template <class Abel> struct BIT {
    vector<Abel> dat[2];
    Abel UNITY_SUM = 0;                     // to be set
    
    /* [1, n] */
    BIT(int n) { init(n); }
    void init(int n) {
        REP(iter, 2) dat[iter].assign(n + 1, UNITY_SUM);
    }
    
    // 区間[a, b)に値xを加算
    inline void add(int a, int b, Abel x) {
        sub_add(0, a, x * -(a - 1)); sub_add(1, a, x); sub_add(0, b, x * (b - 1)); sub_add(1, b, x * (-1));
    }

    // 区間[a, b)の和を返す
    inline Abel sum(int a, int b) {
        return sub_sum(0, b - 1) + sub_sum(1, b - 1) * (b - 1) - sub_sum(0, a - 1) - sub_sum(1, a - 1) * (a - 1);
    }

    /* debug */
    void print() {
        for (int i = 1; i < (int)dat[0].size(); ++i) cout << sum(i, i + 1) << ",";
        cout << endl;
    }

private:
    inline void sub_add(int p, int a, Abel x) {
        for (int i = a; i < (int)dat[p].size(); i += i & -i)
            dat[p][i] = dat[p][i] + x;
    }

    inline Abel sub_sum(int p, int a) {
        Abel res = UNITY_SUM;
        for (int i = a; i > 0; i -= i & -i) res = res + dat[p][i];
        return res;
    }
};

// 区間加算にも対応した BIT (0-based)
// 0-basedにするだけのラッパークラス
template <class Abel> struct BIT0Based {
    BIT0Based(int n) : bit(n) {};
    void init(int n) {
        bit.init(n);
    }
    
    // 区間[a, b)に値xを加算
    inline void add(int a, int b, Abel x) {
        bit.add(a + 1, b + 1, x);
    }

    // 区間[a, b)の和を返す
    inline Abel sum(int a, int b) {
        return bit.sum(a + 1, b + 1);
    }

    /* debug */
    void print() {
        bit.print();
    }
private:
    BIT<Abel> bit;
};

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N; cin >> N;
    vector<ll> A(N);
    REP(n, N) cin >> A[n];

    vector<mint> exp(N);

    BIT0Based<mint> bit(N);

    exp[N - 1] = 0;
    for(int n = N - 2; n >= 0; --n) {
        ll denom = A[n];
        auto numer = bit.sum(n + 1, n + 1 + A[n]) + (A[n] + 1);
        exp[n] = numer / denom;
        bit.add(n, n + 1, exp[n]);
    }

    cout << exp[0] << endl;

    return 0;
}
