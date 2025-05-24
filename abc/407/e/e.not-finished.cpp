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

vector<ll> do_dp_first_half(vector<ll>& B) {
    int n = SIZE(B);

    ll offset = 0;
    
    vector<ll> tmp;
    REP(i, n) {

        auto b = B[i];
        // cout << "i = " << i << endl;

        if (i == 0) {
            // (
            tmp.push_back(b);
        }

        else if (i % 2) {

            
            vector<ll> tmp2;

            // )
            for(auto t: tmp) {
                tmp2.push_back(t);
            }

            // (
            tmp2.push_back(tmp.back() + b);

            // (
            REP(j, SIZE(tmp) - 1) {
                chmax(tmp2[j + 1], tmp[j] + b);
            }
            // tmp = move(tmp2);

            // (
            tmp.push_back(tmp.back() + b);

            auto len = SIZE(tmp);
            REP(j, len - 2) {
                chmax(tmp[len - 2 - j], tmp[len - 3 - j]);
            }

            // cout << "tmp = " << endl;
            // for(auto t: tmp) cout << t << ",";
            // cout << endl;

            // cout << "tmp2 = " << endl;
            // for(auto t: tmp2) cout << t << ",";
            // cout << endl;



        } else {
            vector<ll> tmp2;

            // (
            for(auto t: tmp) {
                tmp2.push_back(t + b);
            }

            // )
            REP(j, SIZE(tmp) - 1) {
                chmax(tmp2[j], tmp[j + 1]);
            }

            // tmp = move(tmp2);

            // offset += b;
            // REP(j, SIZE(tmp) - 1) {
            //     chmax(tmp[j], tmp[j + 1] - b);
            // }

            REP(j, SIZE(tmp) - 1) {
                chmax(tmp[j], tmp[j] + b);
                chmax(tmp[j], tmp[j+1]);
            }
            tmp[SIZE(tmp)-1] += b;



            // cout << "tmp = " << endl;
            // for(auto t: tmp) cout << t << ",";
            // cout << endl;

            // cout << "tmp2 = " << endl;
            // for(auto t: tmp2) cout << t << ",";
            // cout << endl;

        }

        // cout << "len of tmp = " << SIZE(tmp) <<endl;
        // for(auto t: tmp) {
        //     cout << "  " << t << endl;
        // }

    }

    // cout << "offset = " << offset << endl;
    tmp[0] += offset;
    return tmp;
}

vector<ll> do_dp_second_half(vector<ll>& B) {
    int n = SIZE(B);
    
    vector<ll> tmp;
    REP(i, n) {

        auto b = B[i];

        if (i == 0) {
            // )
            tmp.push_back(0);
        }
        else if (i % 2) {
            vector<ll> tmp2;
            
            // (
            for(auto t: tmp) {
                tmp2.push_back(t + b);
            }
            // )
            tmp2.push_back(tmp.back());

            // )
            REP(j, SIZE(tmp) - 1) {
                chmax(tmp2[j + 1], tmp[j]);
            }
            tmp = move(tmp2);

        } else {
            vector<ll> tmp2;
            // )
            for(auto t: tmp) {
                tmp2.push_back(t);
            }

            // (
            REP(j, SIZE(tmp) - 1) {
                chmax(tmp2[j], tmp[j + 1] + b);
            }
            tmp = move(tmp2);
        }
        cout << "len of tmp = " << SIZE(tmp) <<endl;
        for(auto t: tmp) {
            cout << "  " << t << endl;
        }
    }
    return tmp;
}

ll solve(int N, vector<ll>& A) {
    // vector<ll> A1;
    // REP(n, N) A1.push_back(A[n]);
    // auto dp1 = do_dp_first_half(A1);

    // vector<ll> A2;
    // REP(n, N) A2.push_back(A[N * 2 - 1 - n]);
    // auto dp2 = do_dp_second_half(A2);

    // ll ans = 0;
    // REP(i, SIZE(A1)) {
    //     chmax(ans, A1[i] + A2[i]);
    // }

    // cout << "SIZE of A = " << SIZE(A) << endl;
    auto dptmp = do_dp_first_half(A);
    // cout << "SIZE = " << SIZE(dptmp) << endl;
    // for(auto t: dptmp) cout << t << endl;
    // cout << dptmp[

    return dptmp[0];

    // return ans;
    return 777;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    REP(tcase, T) {
        int N; cin >> N;
        vector<ll> A(2 * N);
        REP(n, 2 * N) cin >> A[n];
        cout << solve(N, A) << endl;
    }





    return 0;
}
