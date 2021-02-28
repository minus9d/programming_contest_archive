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

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N, X;
    cin >> N >> X;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];
    sort(ALL(As));

    ll ans = 1e18;
    FOR(i, 1, N + 1) {
        if (i == 1) {
            chmin(ans, X - As.back());
        } else {
            vector<int> Bs(N);
            REP(n, N) {
                Bs[n] = As[n] % i;
            }
            vector<vector<vector<ll>>> dp(N + 1);
            REP(j, N + 1) {
                dp[j] = vector<vector<ll>>(i + 1, vector<ll>(i));
            } 

            vector<vector<vector<ll>>> dp2(N + 1);
            REP(j, N + 1) {
                dp2[j] = vector<vector<ll>>(i + 1, vector<ll>(i));
            } 

            dp[0][0][0] = 0;
            dp2[0][0][0] = 1;
            REP(j, N) {
                auto a = As[j];
                auto b = Bs[j];
                REP(k, i + 1) {
                    REP(m, i) {
                        chmax(dp[j+1][k][m], dp[j][k][m]);
                        if (dp2[j][k][m]) {
                            dp2[j+1][k][m] = 1;
                        }

                        // 選ぶ
                        if (k >= 1 && dp2[j][k-1][(m+i-b)%i]) {
                            chmax(dp[j+1][k][m],
                                  dp[j][k-1][(m+i-b)%i] + a);
                            dp2[j+1][k][m] = 1;
                        };
                    }
                }
            }

            // REP(j, N+1) {
            //     REP(k, i + 1) {
            //         REP(m, i) {
            //             cout << "dp[" << j << "][" << k << "][" << m << "] = " << 
            //                 dp[j][k][m] << ", dp2 = " <<
            //                 dp2[j][k][m] << endl;
            //         }
            //     }
            // }

            ll need_mod = X % i;
            if (dp2[N][i][need_mod]) {
                ll sum = dp[N][i][need_mod];
                ll remain = X - sum;
                ll time = remain / i;
                chmin(ans, time);
            }
        }
    }

    cout << ans << endl;

    return 0;
}
