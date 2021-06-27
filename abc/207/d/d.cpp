#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <complex>
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


using P = pair<double, double>;

// https://stackoverflow.com/questions/28182887/sorting-complex-numbers-in-a-vector-c/28183074
bool myWay(const complex<double> a, const complex<double> b)
{
    if (real(a) == real(b))
        return imag(a) < imag(b);
    return real(a) < real(b);
}

double epsilon = 1e-7; // 1e-7: WA  1e-8: WA

bool are_signature_same(vector<complex<double>> sig,
                        vector<complex<double>> sig_cd) {
    // WAの方法
    // ソートで微妙に順番入れ替わる？
    // bool ok = true;
    // REP(ii, SIZE(sig)) {
    //     auto& s1 = sig[ii];
    //     auto& s2 = sig_cd[ii];
    //     if (abs(real(s1) - real(s2)) > epsilon
    //         || abs(imag(s1) - imag(s2)) > epsilon) {
    //         ok = false;
    //         break;
    //     }
    // }
    // return ok;

    // 対応する要素を順に見つけていく
    auto size = SIZE(sig_cd);
    for(auto& s1: sig) {
        bool found = false;
        REP(i, size) {
            auto& s2 = sig_cd[i];

            // 十分近い候補を見つける
            if (abs(real(s1) - real(s2)) < epsilon
                && abs(imag(s1) - imag(s2)) < epsilon) {
                found = true;
                sig_cd[i] = 1e9 + 1i * 1e9;
                break;
            }
        }
        if (!found) return false;
    }

    // 


    return true;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    vector<P> ABs(N);
    REP(n, N) {
        double a, b; cin >> a >> b;
        ABs[n] = mp(a, b);
    }
    vector<P> CDs(N);
    REP(n, N) {
        double c, d; cin >> c >> d;
        CDs[n] = mp(c, d);
    }

    // corner (5/64 cases!)
    if (N == 1) {
        cout << "Yes" << endl;
        return 0;
    }

    vector<complex<double>> sig;
    complex<double> vec;
    {
        auto pt0 = ABs[0];
        auto pt1 = ABs[1];
        vec = (pt1.first - pt0.first) + 1i * (pt1.second - pt0.second);

        FOR(i, 2, N) {
            auto ptX = ABs[i];
            complex<double> vec2 = (ptX.first - pt0.first) + 1i * (ptX.second - pt0.second);
        
            auto vec3 = vec2 / vec;
            sig.pb(vec3);
        }
    }
    sort(ALL(sig), myWay);

    // cout << endl;
    // cout << "signature:" << endl;
    // for(auto s: sig) {
    //     cout << "  " << s << endl;
    // }
    // cout << endl;

    bool found = false;
    REP(i, N) {
        if (found) break;
        REP(j, N) {
            if (i == j) continue;

            auto pt0 = CDs[i];
            auto pt1 = CDs[j];
            complex<double> vec_cd = (pt1.first - pt0.first) + 1i * (pt1.second - pt0.second);

            // 長さ同じ?
            if (abs(norm(vec) - norm(vec_cd)) < epsilon) {
                vector<complex<double>> sig_cd;
                REP(k, N) {
                    if (k == i || k == j) continue;
                    
                    auto ptX = CDs[k];
                    complex<double> vec2 = (ptX.first - pt0.first) + 1i * (ptX.second - pt0.second);
        
                    auto vec3 = vec2 / vec_cd;
                    sig_cd.pb(vec3);
                }
                sort(ALL(sig_cd), myWay);

                // cout << endl;
                // cout << "signature CD:" << endl;
                // for(auto s: sig_cd) {
                //     cout << "  " << s << endl;
                // }
                // cout << endl;
                
                // signatureが一致？
                if (are_signature_same(sig, sig_cd)) {

                    // cout << endl;
                    // cout << "signature:" << endl;
                    // for(auto s: sig) {
                    //     cout << "  " << s << endl;
                    // }
                    // cout << endl;

                    // cout << endl;
                    // cout << "signature CD:" << endl;
                    // for(auto s: sig_cd) {
                    //     cout << "  " << s << endl;
                    // }
                    // cout << endl;


                    found = true;
                    break;
                }

            }
        }
    }

    cout << (found ? "Yes" : "No") << endl;
    // // for debug!
    // if (found) {
    //     cout << "Yes" << endl;
    // } else {
    //     return 1;
    // }


    return 0;
}
