// 本番中に思いついたが実装しきれなかった方法でとき直したもの
// (n, r) = (n - 1, r - 1) + (n - 1, r) という公式を使って力技で解く
//
// https://twitter.com/nico_shindannin/status/1226502779289489408
// のように解けばもっと簡単だった

#include <algorithm>
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
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

class NCK {
private:
    ll m_mod;

public:
    // mod must be a prime number
    NCK(ll mod) : m_mod(mod) {}

    // x^y % m_mod
    ll modPow(ll x, ll y)
    {
        ll r = 1, a = x;
        while (y > 0) {
            if ((y&1) == 1) {
                r = (r * a) % m_mod;
            }
            a = (a * a) % m_mod;
            y /= 2;
        }
        return r;
    }

    // a^-1 ≡ a^(p-2) (mod p)   (p is prime)
    ll modInverse(ll x)
    {
        return modPow(x, m_mod-2);
    }

    // Modular division x / y, find modular multiplicative inverse of y
    // and multiply by x.
    ll modDivision(ll p, ll q)
    {
        return (p * modInverse(q)) % m_mod;
    }

    // Binomial coifficient C(n,k) in O(k) time.
    ll choose(ll n, ll k)
    {
        if (k > n) {
            return 0;
        }
        ll p = 1, q = 1;
        for (int i=1; i<=k; i++) {
            q = (q * i) % m_mod;
            p = (p * (n - i + 1)) % m_mod;
        }
        return modDivision(p, q);
    }

    // make nCk table from 0C0 to nCn
    vector<vector<ll>> makeNckTableFrom00ToNN(ll n_max) {
        assert(n_max > 0);
        vector<vector<ll>> table(n_max+1, vector<ll>(n_max+1));
        table[0][0] = 1;
        FOR(i, 1, n_max + 1) {
            table[i][0] = 1;
            FOR(j, 1, n_max + 1) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % m_mod;
            }
        }
        return table;
    }

    // make nCk table from nC0 to nCn
    vector<ll> makeNckTableFromN0ToNN(ll n, ll k_max) {
        assert(n > 0);
        assert(n >= k_max);
        vector<ll> table(n+1);
        table[0] = 1;
        ll p = 1, q = 1;
        table[0] = 1;
        FOR(i, 1, k_max+1) {
            q = (q * i) % m_mod;
            p = (p * (n - i + 1)) % m_mod;
            table[i] = modDivision(p, q);
        }
        return table;
    }

    // make nCk table from n1Ck to n2Ck
    vector<ll> makeTableFromN1CkToN2Ck(ll n1, ll n2, ll k) {
        vector<ll> table;

        // n < kのときは nCk = 0
        FOR(n, n1, k) {
            table.pb(0);
        }

        ll tmp = -1;
        FOR(n, k, n2 + 1) {
            if (n == k) {
                tmp = this->choose(n, k);
            }
            else {
                tmp *= n;
                tmp %= this->m_mod;
                tmp = this->modDivision(tmp, n - k);
            }
            table.pb(tmp);
        }
        return table;
    }

    // make modInverse table from 0 to n_max
    vector<ll> makeModInverseTable(ll n_max) {
        assert(n_max > 0);
        vector<ll> table(n_max + 1);
        FOR(i, 1, n_max + 1) {
            table[i] = modInverse(i);
        }
        return table;
    }
};

const ll MOD = 1e9 + 7;

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

using mint = Fp<MOD>;

ll solve_slow(ll r1, ll c1, ll r2, ll c2) {
    NCK nck(MOD);
    mint ans = 0;
    FOR(r, r1, r2 + 1) {
        FOR(c, c1, c2 + 1) {
            ans += nck.choose(r + c, r);
        }
    }
    return ans.val;
}

ll solve_fast(ll r1, ll c1, ll r2, ll c2) {

    // 盤面が横6, 縦4だとする。
    // abcdez
    // abcdez
    // abcdez
    // xabcde

    // n choose k のことを (n, k)と表す。
    // xはすぐ計算できる。

    // a, b, c, d, eの部分は、
    // (n, r) = (n - 1, r - 1) + (n - 1, r) という公式に着目するとすぐ計算できる。
    //
    // 例えば、"a"で表した部分は、
    // 下から順に (s, t), (s, t - 1), (s + 1, t - 1), (s + 2, t - 1) だとする。
    //
    // 最初の2個(s, t), (s, t - 1)に公式を適用し (s + 1, t)
    // (s + 1, t) と (s + 1, t - 1) に公式を適用し (s + 2, t)
    // (s + 2, t) と (s + 2, t - 1) に公式を適用し (s + 3, t)
    // つまりaの和は(s + 3, t)で計算できることがわかる

    // zの部分は、上から順に(s, t), (s - 1, t), (s - 2, t), と並んでいるので
    // 順番に計算できる


    NCK nck(MOD);

    // xの部分を計算
    mint ans1 = nck.choose(r1 + c1, r1);

    if (c2 - c1 >= 1) {

        // aの和を計算
        mint c = c1 + 1;
        mint r = r1;
        r += r2 - r1;
        mint n = r + c;
        mint k = c;
        mint tmp = nck.choose(n.val, k.val);
        ans1 += tmp;

        // bの和, cの和, ..., eの和を順に計算
        int offset = 1;
        FOR(i, c1 + 2, c2 + 1) {
            tmp *= (n + offset);
            tmp /= (k + offset);
            ans1 += tmp;
            offset++;
        }
    }

    // zの部分を上から順に計算
    if (r2 - r1 >= 1) {
        mint n = r2 + c2;
        mint k = c2;
        mint tmp = nck.choose(n.val, k.val);
        ans1 += tmp;
        mint offset = 0;
        for(int r = r2 - 1; r >= r1 + 1; --r) {
            tmp /= (n - offset);
            tmp *= (n - offset - k);
            ans1 += tmp;
            offset += 1;
        }
    }

    return ans1.val;
}

int main(void)
{
    cin.sync_with_stdio(false);

    // // verify
    // FOR(r1, 1, 10) {
    //     FOR(c1, 1, 10) {
    //         FOR(r2, r1, 10) {
    //             FOR(c2, c1, 10) {
    //                 cout << endl;
    //                 ll mine = solve_fast(r1, c1, r2, c2);
    //                 ll gt = solve_slow(r1, c1, r2, c2);
    //                 if (mine != gt) {
    //                     cout << "error!" << endl;
    //                     cout << r1 << " " << c1 << " "
    //                          << r2 << " " << c2 << endl;
    //                     cout << "mine, gt = " << mine << " " << gt << endl;
    //                 }
    //             }
    //         }
    //     }
    // }
    
    ll r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    cout << solve_fast(r1, c1, r2, c2) << endl;

    return 0;
}
