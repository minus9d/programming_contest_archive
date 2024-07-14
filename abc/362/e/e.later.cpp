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
constexpr ll MOD =  998244353;
using mint = Fp<MOD>;

#define pb push_back
#define mp make_pair
#define mt make_tuple

// 本番中に出したコード。WA
// 等差級数の差が０のときの考慮ができていない
vector<ll> solve_mine_wrong(int N, vector<ll> A) {

    vector<mint> ans(N+1);
    ans[1] = N;
    ans[2] = mint(N) * mint(N - 1) / 2;

    REP(i, N-2) {
        FOR(j, i + 1, N-1) {
            ll x = A[i];
            ll y = A[j];
            ll d = y - x;

            // num -> <len, mint>
            map<ll, pair<ll, mint>> cur;
            cur[y] = {2, mint(1)};

            FOR(k, j + 1, N) {
                ll a = A[k];

                if (cur.count(a - d)) {
                    auto tmp = cur[a];
                    tmp.first = cur[a - d].first + 1;
                    tmp.second += cur[a - d].second;
                    cur[a] = tmp;
                }

            }
            for(auto c: cur) {
                auto len = c.second.first;
                auto num = c.second.second;
                if (len > 2) {
                    ans[len] += num ;
                }
            }
        }
    }

    vector<ll> ret;
    for(auto a: ans) ret.push_back(a.val);
    return ret;
}

vector<ll> solve_mine(int N, vector<ll> A) {

    vector<mint> ans(N+1);
    ans[1] = N;
    ans[2] = mint(N) * mint(N - 1) / 2;

    REP(i, N-2) {
        FOR(j, i + 1, N-1) {
            ll x = A[i];
            ll y = A[j];
            ll d = y - x;
            // {num, {len -> mint}}
            map<ll, map<ll, mint>> cur;
            cur[y][2] = mint(1);

            // cout << "for i, j = " << i << "," << j << endl;
            FOR(k, j + 1, N) {
                map<ll, map<ll, mint>> nxt = cur;

                ll a = A[k];

                map<ll, mint> tmp;
                if (cur.count(a - d)) {
                    for(auto [len, comb]: cur[a - d]) {
                        nxt[a][len + 1] += comb;
                    }
                }
                cur = nxt;

                // cout << " at k = " << k << endl;
                // for(auto [c, len_and_comb]: cur) {
                //     for (auto [len, comb]: len_and_comb) {
                //         cout << "  last " << c << ", len = " << len << ", comb = " << comb << endl;
                //     }
                // }
            }

            for(auto [c, len_and_comb]: cur) {
                for (auto [len, comb]: len_and_comb) {
                    if (len > 2) {
                        ans[len] += comb ;
                    }
                }
            }
        }
    }

    vector<ll> ret;
    for(auto a: ans) ret.push_back(a.val);
    return ret;
}

// https://atcoder.jp/contests/abc362/submissions/55519772
vector<ll> solve_gt(int N, vector<ll> v) {

	vector<map<pair<long long, int>, long long>>dp(N + 1);
	for (int i = 0; i < v.size(); i++) {
		for (int j = N - 1; j >= 2; j--) {
			for (const auto& k : dp[j]) {
				if (k.first.first + k.first.second == v[i]) {
					dp[j + 1][{v[i], k.first.second}] += k.second;
					dp[j + 1][{v[i], k.first.second}] %= MOD;
				}
			}
		}
		for (int j = 0; j < i; j++) {
			dp[2][{v[i], v[i] - v[j]}]++;
		}
	}

    vector<ll> ans; ans.pb(0); ans.pb(N);
	for (int i = 2; i <= N; i++) {
		long long sum = 0;
		for (const auto &j : dp[i]) {
			sum += j.second;
			sum %= MOD;
		}
        ans.pb(sum);
	}
    return ans;
}    


int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    vector<ll> A(N);
    REP(n, N) cin >> A[n];

    // // for debug
    // while(1) {
    //     int N = 5;
    //     vector<ll> A;
    //     REP(n, N) A.push_back(rand() % 100);
    //     auto mine = solve_mine(N, A);
    //     auto gt = solve_gt(N, A);

    //     FOR(i, 1, N+1) {
    //         if (mine[i] != gt[i]) {
    //             cout << "error!" << endl;
    //             cout << "A:" << endl;
    //             for(auto a: A) cout <<a << " ";
    //             cout << endl;
    //             cout << "gt:" << endl;
    //             FOR(i, 1, N+1) {
    //                 cout << (i == 1 ? "" : " ") << gt[i];
    //             }
    //             cout << endl;
    //             cout << "mine:" << endl;
    //             FOR(i, 1, N+1) {
    //                 cout << (i == 1 ? "" : " ") << mine[i];
    //             }
    //             cout << endl;
    //             return 0;
    //         }
    //     }
    //     cout << "ok" << endl;
    // }

    auto ans = solve_mine(N, A);
    FOR(i, 1, N+1) {
        cout << (i == 1 ? "" : " ") << ans[i];
    }
    cout << endl;

    return 0;
}
