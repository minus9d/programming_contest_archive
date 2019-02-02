// 自力AC 
//
// 解説PDFとは違う方針で解けたが2時間ほど苦戦した
//
// 6x7盤面で、もし壁がなかった場合の数は以下のようになる
// (コード中のans1)
//    1   1   1   1   1   1   1
//    1   2   3   4   5   6   7
//    1   3   6  10  15  21  28
//    1   4  10  20  35  56  84
//    1   5  15  35  70 126 210
//    1   6  21  56 126 210 420
//
// 壁がA = 2, B = 3のときは以下のようになる
//    1   1   1   1   1   1   1
//    1   2   3   4   5   6   7
//    1   3   6  10  15  21  28
//    x   x   x  10  25  46  74
//    x   x   x  10  35  81 155
//    x   x   x  10  45 126 281
//
// ここで右下部分の差分は以下のようになっている
//    x   x   x   x   x   x   x
//    x   x   x   x   x   x   x
//    x   x   x   x   x   x   x    
//    x   x   x  10  10  10  10
//    x   x   x  25  35  45  55
//    x   x   x  46  81  84 139
// 
// 壁の最右端をa, b, cと置くと、差分は以下のように表せる
//    x   x   x     x       x       x        x
//    x   x   x     x       x       x        x
//    x   x   x     x       x       x        x    
//    x   x   a     a       a       a        a
//    x   x   b   a+b    2a+b    3a+b     4a+b
//    x   x   c a+b+c 3a+2b+c 6a+3b+c 10a+4b+c
// 
// あとは右下の10a+4b+c(=ans2)の規則性を探して計算
// コード中のvがa, b, c, wが10, 4, 1に相当

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

const ll MOD = 1000000007;

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

// 壁がないとき、上からh番目、左からw番目のマスに移動する数を計算
ll way_to_go(ll h, ll w, NCK& nck) {
    return nck.choose(h + w - 2, min(h - 1, w - 1));
}
ll way_to_go2(ll h, ll w, NCK& nck) {
    return nck.choose(h + w - 2, w - 1);
}

ll solve_slow(ll H, ll W, ll A, ll B) {
    NCK nck(MOD);
    
    // 壁を考えないとき、右下に行く場合の数
    ll ans1 = way_to_go(H, W, nck);

    // 壁があることによって減じる量を計算
    ll ans2 = 0;
    FOR(h, H - A + 1, H + 1) {
        auto v = way_to_go(h, B, nck);
        auto w = way_to_go(H - h + 1, W - B, nck);
        // cout << "v * w = " << v << " * " << w << " = " << v * w << endl;
        ans2 += v * w;
        ans2 %= MOD;
    }
    auto ans = (ans1 - ans2 + MOD) % MOD;
    return ans;
}

ll solve_fast(ll H, ll W, ll A, ll B) {
    NCK nck(MOD);

    // 壁を考えないとき、右下に行く場合の数
    ll ans1 = way_to_go(H, W, nck);

    // 壁があることによって減じる量を計算
    ll ans2 = 0;
    auto v_table = nck.makeTableFromN1CkToN2Ck(
        H + B - A - 1,
        H + B - 2,
        B - 1);
    auto w_table = nck.makeTableFromN1CkToN2Ck(
        W - B - 1,
        W - B + A - 2,
        W - B - 1);
    reverse(ALL(w_table));

    int i = 0;
    FOR(h, H - A + 1, H + 1) {
        auto v = v_table[i];
        auto w = w_table[i];
        ans2 += v * w;
        ans2 %= MOD;
        ++i;
    }
    auto ans = (ans1 - ans2 + MOD) % MOD;
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll H, W, A, B;
    cin >> H >> W >> A >> B;
    cout << solve_fast(H, W, A, B);
    return 0;

    // 以下、デバッグ用
    FOR(h, 1, 6) {
        FOR(w, 1, 6) {
            FOR(a, 1, h) {
                FOR(b, 1, w) {
                    auto mine = solve_fast(h, w, a, b);
                    auto slow = solve_slow(h, w, a, b);
                    if (mine != slow) {
                        cout << "========" << endl;
                        cout << "error! " << endl;
                        cout << h << " " << w << " " << a << " " << b << endl;
                        cout << "mine:" << mine << endl;
                        cout << "slow:" << slow << endl;
                        cout << "========" << endl;
                        return 0;
                    } else {
                        // ok
                    }
                }
            }
        }
    } 
}
