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

vector<ll> getPrimesFast(const ll n){
    vector<ll> primes;
    if (n < 10000){
        primes.clear();
        if (n < 2){
            return primes;
        }
        primes.push_back(2);
        if (n == 2){
            return primes;
        }
        primes.push_back(3);
        if (n == 3){
            return primes;
        }
        for(ll i = 5; i <= n; i += 2){
            bool isPrime = true;
            for(size_t p = 0; p < primes.size(); ++p){
                if (i % primes[p] == 0){
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                primes.push_back(i);
            }
        }
        return primes;
    }
    else{
        vector<ll> sieve = getPrimesFast(sqrt(n));

        vector<short> isPrime(n+1, 1);
        for(size_t i = 0; i < sieve.size(); ++i){
            for(ll j = sieve[i] * 2; j <= n; j += sieve[i]){
                isPrime[j] = 0;
            }
        }

        for(ll i = 2; i <= n; ++i){
            if (isPrime[i]){
                primes.push_back(i);
            }
        }
        return primes;
    }
}

bool is_validate(int N, vector<vector<int>> cells) {
    set<int> should;
    REP(i, N * N) should.insert(i + 1);

    set<int> seen;
    REP(j, N) {
        REP(i, N) {
            seen.insert(cells[j][i]);
        }
    }

    if (seen != should) return false;

    auto primes = getPrimesFast(N * N * 2);
    set<ll> prime_set(ALL(primes));

    bool ok = true;
    REP(j, N) {
        REP(i, N) {
            if (j != 0 && prime_set.count(cells[j][i] + cells[j-1][i])) {
                ok = false;
                break;
            }
            if (i != 0 && prime_set.count(cells[j][i] + cells[j][i-1])) {
                ok = false;
                break;
            }
        }
        if (!ok) break;
    }
    return ok;
}

void solve_slow(int N) {
    vector<int> shff;
    REP(i, N * N) shff.pb(i + 1);

    auto primes = getPrimesFast(N * N * 2);
    set<ll> prime_set(ALL(primes));

    // for(auto p: prime_set) cout << p << ",";
    // cout << endl;

    do {
        vector<vector<int>> cells(N, vector<int>(N));
        int idx = 0;
        REP(j, N) {
            REP(i, N) {
                cells[j][i] = shff[idx++];
            }
        }
        bool ok = true;
        REP(j, N) {
            REP(i, N) {
                if (j != 0 && prime_set.count(cells[j][i] + cells[j-1][i])) {
                    ok = false;
                    break;
                }
                if (i != 0 && prime_set.count(cells[j][i] + cells[j][i-1])) {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
        }
        if (ok) {
            REP(j, N) {
                REP(i, N) {
                    cout << (i == 0 ? "" : " ") << cells[j][i];
                }
                cout << endl;
            }
            return;
        }
    } while(next_permutation(ALL(shff)));
}

void solve_fast(ll N) {
    auto primes = getPrimesFast(N * N * 2);
    set<ll> prime_set(ALL(primes));

    if (N == 3) {
        solve_slow(N);
        return;
    }

    if (N % 2 == 0) {
        vector<ll> cells;
        auto cells2 = make_v<int>(N, N);

        set<ll> used_i;
        set<ll> used_j;
        vector<pair<ll, ll>> pairs;
        for(ll i = 1; i <= N * N; i += 2) {
            for(ll j = 2; j <= N * N; j += 2) {
                if (used_j.count(j)) continue;
                ll sum = i + j;
                if (!prime_set.count(sum)) {
                    pairs.pb({i, j});
                    used_i.insert(i);
                    used_j.insert(j);
                    break;
                }
            }
            if (SIZE(pairs) == N) break;
        }
    
        // cout << N << " ";
        // if (SIZE(pairs) == N) {
        //     cout << "ok!" << endl;
        // } else {
        //     cout << "error!" << endl;
        //     exit(-1);
        // }
    
        for(ll i = 1; i <= N * N; i += 2) {
            if (!used_i.count(i)) cells.pb(i);
        }
        for(auto [i, j]: pairs) cells.pb(i);
        for(auto [i, j]: pairs) cells.pb(j);
        for(ll j = 2; j <= N * N; j += 2) {
            if (!used_j.count(j)) cells.pb(j);
        }
    
        int cnt = 0;
        REP(j, N) {
            REP(i, N) {
                auto tmp = cells[cnt++];
                cout << (i == 0 ? "" : " ") << tmp;
                cells2[j][i] = tmp;
            }
            cout << endl;
        }

        // // for debug
        // if (!is_validate(N, cells2)) {
        //     cout << "error!!" << endl;
        //     cout << "N = " << N << endl;
        //     exit(-1);
        // }

    } else {

        // x x x  x x 
        // x x x  7 x 
        // x x 1  8 o
        // o o 14 o o
        // o o o  o o

        set<ll> used_i{1, 7};
        set<ll> used_j{8, 14};

        vector<pair<ll, ll>> pairs;
        for(ll i = 1; i <= N * N; i += 2) {
            if (used_i.count(i)) continue;
            for(ll j = 2; j <= N * N; j += 2) {
                if (used_j.count(j)) continue;
                ll sum = i + j;
                if (!prime_set.count(sum)) {
                    pairs.pb({i, j});
                    used_i.insert(i);
                    used_j.insert(j);
                    break;
                }
            }
            if (SIZE(pairs) == N - 2) break;
        }

        // cout << N << " ";
        // if (SIZE(pairs) == N - 2) {
        //     cout << "ok!" << endl;
        // } else {
        //     cout << "error!" << endl;
        //     exit(-1);
        // }

        auto cells = make_v<int>(N, N);
        cells[N / 2][N / 2] = 1;
        cells[N / 2][N / 2 + 1] = 8;
        cells[N / 2 - 1][N / 2 + 1] = 7;
        cells[N / 2 + 1][N / 2] = 14;

        int num1 = (N / 2) - 1;
        int num2 = (N / 2);
        
        int idx = 0;
        REP(i, num1) {
            cells[N / 2 - 1][N - 1 - i] = pairs[idx].first;
            cells[N / 2][N - 1 - i] = pairs[idx].second;
            idx++;
        }
        REP(i, num2) {
            cells[N / 2][i] = pairs[idx].first;
            cells[N / 2 + 1][i] = pairs[idx].second;
            idx++;
        }

        vector<int> odd;
        for(ll i = 1; i <= N * N; i += 2) {
            if (!used_i.count(i)) odd.pb(i);
        }

        idx = 0;
        for(auto o: odd) {
            int y = idx / N;
            int x = idx % N;
            cells[y][x] = o;
            ++idx;
        }

        vector<int> even;
        for(ll j = 2; j <= N * N; j += 2) {
            if (!used_j.count(j)) even.pb(j);
        }

        idx = N * N / 2 + N + 1;
        for(auto e: even) {
            int y = idx / N;
            int x = idx % N;
            cells[y][x] = e;
            ++idx;
        }

        REP(y, N) {
            REP(x, N) {
                cout << (x == 0 ? "" : " ") << cells[y][x];
            }
            cout << endl;
        }

        // for debug
        // if (!is_validate(N, cells)) {
        //     cout << "error!!" << endl;
        //     cout << "N = " << N << endl;    
        //     exit(0);
        // }
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    solve_fast(N);

    // FOR(n, 3, 1001) {
    //     cout << endl;
    //     cout << "n = " << n << endl;
    //     solve_fast(n);
    // }

    return 0;
}
