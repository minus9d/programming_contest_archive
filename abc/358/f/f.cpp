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

void visualize(int N, int M, vector<char> act) {
    cout << "Yes" << endl;
    
    int H = 2 * N + 1;
    int W = 2 * M + 1;

    auto res = vector<vector<char>>(H, vector<char>(W, '+'));
    REP(y, N) {
        REP(x, M) {
            res[2 * y + 1][2 * x + 1] = 'o';
            if (x != M - 1) {
                res[2 * y + 1][2 * x + 2] = '|';
            }
            if (y != N - 1) {
                res[2 * y + 2][2 * x + 1] = '-';
            }
        }
    }

    int y = 1;
    int x = W - 2;
    for(auto a: act) {
        if (a == 'D') {
            res[y + 1][x] = '.';
            y += 2;
        }
        if (a == 'U') {
            res[y - 1][x] = '.';
            y -= 2;
        }
        if (a == 'R') {
            res[y][x + 1] = '.';
            x += 2;
        }
        if (a == 'L') {
            res[y][x - 1] = '.';
            x -= 2;
        }
    }


    // ?
    REP(y, H) {
        res[y][0] = '+';
        res[y][W-1] = '+';
    }
    REP(x, W) {
        res[0][x] = '+';
        res[H-1][x] = '+';
    }

    res[0][W - 2] = 'S';
    res[H - 1][W - 2] = 'G';


    // print
    REP(h, H) {
        REP(w, W) {
            cout << res[h][w];
        }
        cout << endl;
    }
    
}

void solve(int N, int M, int K){
    vector<char> act;
    if (M == 1) {
        if (N == K) {
            REP(i, N - 1) {
                act.push_back('D');
            }
            visualize(N, M, act);
        } else {
            cout << "No" << endl;
        }
    } else {
        // M >= 2

        if (N % 2 == 0) {
            int mn = N;
            int mx = N * M;
            if ((K < mn) or (K > mx) or ((K - mn) % 2 == 1)) {
                cout << "No" << endl;
            } else {
                int remain_pair = (K - mn) / 2;
                REP(i, N / 2) {
                    int left_num = min(M - 1, remain_pair);
                    remain_pair -= left_num;
                    REP(j, left_num) act.push_back('L');
                    act.push_back('D');
                    REP(j, left_num) act.push_back('R');
                    act.push_back('D');
                }
                // for(auto ch: act) cout << ch << ",";
                // cout << endl;

                visualize(N, M, act);
            }
        } else {
            // N % 2 == 1
            int mn = N;
            int mx = N * M;
            if (M % 2 == 0) mx--;

            if ((K < mn) or (K > mx) or ((K - mn) % 2 == 1)) {
                cout << "No" << endl;
            } else {
                if (K <= N * M - (M - 1)) {
                    int remain_pair = (K - mn) / 2;
                    REP(i, N / 2) {
                        int left_num = min(M - 1, remain_pair);
                        remain_pair -= left_num;
                        REP(j, left_num) act.push_back('L');
                        act.push_back('D');
                        REP(j, left_num) act.push_back('R');
                        act.push_back('D');
                    }
                    visualize(N, M, act);
                } else {
                    int remain_pair = (K - mn) / 2;
                    REP(i, N / 2 - 1) {
                        int left_num = min(M - 1, remain_pair);
                        remain_pair -= left_num;
                        REP(j, left_num) act.push_back('L');
                        act.push_back('D');
                        REP(j, left_num) act.push_back('R');
                        act.push_back('D');
                    }

                    REP(i, M - 1) {
                        act.push_back('L');
                    }
                    act.push_back('D');

                    remain_pair = (K - ((N - 1) * M + 1)) / 2;
                    REP(i, (M - 1) / 2) {
                        if (remain_pair > 0) {
                            act.push_back('D');
                            act.push_back('R');
                            act.push_back('U');
                            act.push_back('R');
                            --remain_pair;
                        } else {
                            act.push_back('R');
                            act.push_back('R');
                        }
                    }

                    if (M % 2) {
                        act.push_back('D');
                    } else {
                        act.push_back('R');
                        act.push_back('D');
                    }
                    visualize(N, M, act);
                }
            }
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K;
    cin >> N >> M >> K;

    solve(N, M, K);

    return 0;
}
