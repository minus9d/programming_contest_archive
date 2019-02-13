// 本番中にAC!
//
// blueを○, redを×で表す。以下の場合を考える。
//
//   ○○××
//   ○×○×
//
// 1回目に高橋君が受け取れるのは、左から1番目の列にあるボール、すなわち○○のいずれか
// 2回目に高橋君が受け取れるのは、左から1, 2番目の列にあるボール、すなわち○○○×のいずれか
// である。
// DPにより、最初のN個のボールを取り出す場合の数を求められる。
//
// N個のボールを取り出した後は、残りのボールを、任意の順番で取り出せる。
// (証明できてないが、そう信じて実装したら通った)


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

const ll MOD = 998244353;

// [i番目の取り出し][赤を取り出した回数]
ll dp[2001][2001];

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
            if ((y & 1) == 1) {
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
        return modPow(x, m_mod - 2);
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
        for (int i = 1; i <= k; i++) {
            q = (q * i) % m_mod;
            p = (p * (n - i + 1)) % m_mod;
        }
        return modDivision(p, q);
    }

    // make nCk table from 0C0 to nCn
    vector<vector<ll>> makeNckTableFrom00ToNN(ll n_max) {
        assert(n_max > 0);
        vector<vector<ll>> table(n_max + 1, vector<ll>(n_max + 1));
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
        vector<ll> table(n + 1);
        table[0] = 1;
        ll p = 1, q = 1;
        table[0] = 1;
        FOR(i, 1, k_max + 1) {
            q = (q * i) % m_mod;
            p = (p * (n - i + 1)) % m_mod;
            table[i] = modDivision(p, q);
        }
        return table;
    }

    // make nCk table from n1Ck to n2Ck
    vector<ll> makeTableFromN1CkToN2Ck(ll n1, ll n2, ll k) {
        vector<ll> table;
        ll tmp = -1;
        FOR(n, n1, n2 + 1) {
            if (n == n1) {
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

int main(void)
{
    cin.sync_with_stdio(false);
    string S;
    cin >> S;
    int N = SIZE(S);
    vector<int> red(N);
    vector<int> blue(N);
    vector<int> red_sum(N);
    vector<int> blue_sum(N);
    REP(n, N) {
        auto ch = S[n];
        if (ch == '0') {
            red[n] = 2;
        }
        else if (ch == '1') {
            red[n] = 1;
            blue[n] = 1;
        }
        else {
            blue[n] = 2;
        }
        if (n == 0) {
            red_sum[n] = red[n];
            blue_sum[n] = blue[n];
        }
        else {
            red_sum[n] = red_sum[n-1] + red[n];
            blue_sum[n] += blue_sum[n-1] + blue[n];
        }
    }



    REP(n, N) {
        auto r = red[n];
        auto b = blue[n];
        if (n == 0) {
            if (r > 0) {
                dp[n][1] = 1;
            }
            if (b > 0) {
                dp[n][0] = 1;
            }
        }
        else {
            REP(used_red, n + 1) {
                if (dp[n - 1][used_red] == 0) continue;
                auto red_prev = red_sum[n - 1];
                auto blue_prev = blue_sum[n - 1];

                auto used_blue = n - used_red;

                auto red_avail = (red_prev - used_red) + red[n];
                auto blue_avail = (blue_prev - used_blue) + blue[n];

                if (red_avail > 0) {
                    dp[n][used_red + 1] += dp[n - 1][used_red];
                    dp[n][used_red + 1] %= MOD;
                }
                if (blue_avail > 0) {
                    dp[n][used_red] += dp[n - 1][used_red];
                    dp[n][used_red] %= MOD;
                }
                //cout << "dp[" << n << "][" << used_red << "] = " <<
                //    dp[n][used_red] << endl;
            }
        }
    }

    ll ans = 0;
    NCK nck(MOD);
    REP(used_red, N + 1) {
        auto used_blue = N - used_red;
        auto red_avail = red_sum[N - 1] - used_red;
        auto blue_avail = blue_sum[N - 1] - used_blue;

        ans += dp[N - 1][used_red] * nck.choose(red_avail + blue_avail, red_avail);
        ans %= MOD;
    }
    cout << ans << endl;

    return 0;
}
