// 本番後にAC
// 本番中と同じ方針のままバグを修正したら通った。
// 3x3の盤面を用いて愚直解と比較してバグ出しした。
// 解説PDFは大きな数字から割り当てることになっていたが、この方針でもいけた
//
// 方針
// A, Bのうちもっとも数値の小さいものから順に考える。
// 例
//    アイウ 9
//    エオカ 6
//    キクケ 8
//    9 4 7
// 上記の場合、2列目の4がもっとも小さい。
// これから、「1,2,3のうちの2つと、4が、イオクに入る」ことがわかる。
// つまり3C2 * 3!の並びがありえる。
//
// これにより盤面が以下のように更新された。使用済みのセルを■で表す。
//    ア■ウ 9
//    エ■カ 6
//    キ■ケ 8
//    9 4 7

// 次に小さい番号は2行目の6。
// 「1,2,3,4,5のうち未使用である2つの数字のうちの1つと、6とが、エカに入る」ことがわかる。
// ありえる並びは2C1 * 2!。
// 
// 以下同様。
// 
// AとBに同じ数値が同時にでてくるときは、その数字の場所が確定することに
// 気をつける必要がある。
//

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


ll solve_slow(ll H, ll W, vector<int>& As, vector<int>& Bs) {
    vector<int> shff;
    REP(n, H * W) shff.push_back(n + 1);
    ll ans = 0;
    do {
        vector<vector<int>> cells(H, vector<int>(W));
        REP(h, H) REP(w, W) {
            int idx = h * W + w;
            cells[h][w] = shff[idx];
        }

        bool ok = true;
        REP(h, H) {
            int sum = 0;
            int mx = 0;
            REP(w, W) mx = max(mx, cells[h][w]);
            if (mx != As[h]) ok = false;
        }
        REP(w, W) {
            int sum = 0;
            int mx = 0;
            REP(h, H) mx = max(mx, cells[h][w]);
            if (mx != Bs[w]) ok = false;
        }
        ans += ok;
    } while (next_permutation(ALL(shff)));
    return ans;
}


ll solve(ll H, ll W, vector<int>& As, vector<int>& Bs) {
    NCK nck(MOD);

    set<int> As_set(ALL(As));
    set<int> Bs_set(ALL(Bs));

    vector<ll> fact(H * W + 1);
    ll t = 1;
    REP(i, H * W) {
        t *= (i + 1);
        t %= MOD;
        fact[i + 1] = t;
    }

    // 同じ数字が2回出るのは許されない
    if (SIZE(As_set) != SIZE(As)) return 0;
    if (SIZE(Bs_set) != SIZE(Bs)) return 0;

    vector<pair<int, int>> A_vi;
    vector<pair<int, int>> B_vi;
    REP(h, H) {
        A_vi.pb({ As[h], h });
    }
    REP(w, W) {
        B_vi.pb({ Bs[w], w });
    }
    sort(ALL(A_vi));
    sort(ALL(B_vi));

    vector<vector<char>> used(H, vector<char>(W));

    int a_loc = 0;
    int b_loc = 0;
    int prev_num = 0;
    int free_num = 0; // 未確定のセルに自由に配置できる数値の数
    ll ans = 1;

    // As, Bsの中から、もっとも数値の小さいものを選んでいく
    while (true) {
        if (a_loc == H && b_loc == W) break;
        int a_min = (a_loc != H) ? A_vi[a_loc].first : 1e9;
        int b_min = (b_loc != W) ? B_vi[b_loc].first : 1e9;

        int a_min_idx = (a_loc != H) ? A_vi[a_loc].second : 1e9;
        int b_min_idx = (b_loc != W) ? B_vi[b_loc].second : 1e9;

        //cout << "a_loc, b_loc = " << a_loc << "," << b_loc << endl;

        int empty_num = 0;  // 盤面のうちまだ数字が確定していないセルの数
        if (a_min == b_min) {

            //// 最後だけは例外, a_min == b_min == H * Wになるはず
            //if (a_min == H * W) {
            //    break;
            //}

            used[a_min_idx][b_min_idx] = 1;
            REP(w, W) empty_num += (used[a_min_idx][w] == 0);
            REP(h, H) empty_num += (used[h][b_min_idx] == 0);
            REP(w, W) used[a_min_idx][w] = 1;
            REP(h, H) used[h][b_min_idx] = 1;

            free_num += (a_min - prev_num - 1);  // a_minを割り当てる場所は固定
            prev_num = a_min;
            ++a_loc;
            ++b_loc;

        }
        else if (a_min < b_min) {
            REP(w, W) empty_num += (used[a_min_idx][w] == 0);
            REP(w, W) used[a_min_idx][w] = 1;

            free_num += (a_min - prev_num);
            prev_num = a_min;
            ++a_loc;
        }
        else if (b_min < a_min) {
            REP(h, H) empty_num += (used[h][b_min_idx] == 0);
            REP(h, H) used[h][b_min_idx] = 1;

            free_num += (b_min - prev_num);
            prev_num = b_min;
            ++b_loc;
        }

        //cout << "free_num, empty_num = " << free_num << "," << empty_num << endl;

        if (free_num < empty_num) {
            return 0;
        }

        // free_numの中からempty_num個を自由に割り当てる
        if (a_min == b_min) {
            // この場合 a_min を割り当てる場所は確定している。
            // まだ未確定のセルがempty_num個残っている場合は、free_numの中からempty_num個選んで割り当てる
            if (empty_num > 0) {
                ans *= nck.choose(free_num, empty_num);
                ans %= MOD;
                ans *= fact[empty_num];
                ans %= MOD;
            }
        }
        else {
            // a_minまたはb_minはかならずどこかで使う。
            // 割り当てる場所はempty_num個通り。
            ans *= empty_num;
            ans %= MOD;

            --empty_num;
            --free_num;

            // 未確定のセルに割り当て
            if (empty_num > 0) {
                ans *= nck.choose(free_num, empty_num);
                ans %= MOD;
                ans *= fact[empty_num];
                ans %= MOD;
            }
        }

        free_num -= empty_num;
    }
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, M;
    cin >> N >> M;
    vector<int> As(N);
    vector<int> Bs(M);
    REP(n, N) cin >> As[n];
    REP(m, M) cin >> Bs[m];


    //// for debug
    //while (true) {
    //    int H = 3;
    //    int W = 3;
    //    vector<int> shff;
    //    REP(n, H * W) shff.push_back(n + 1);
    //    random_shuffle(ALL(shff));

    //    vector<vector<int>> cells(H, vector<int>(W));
    //    REP(h, H) REP(w, W) {
    //        int idx = h * W + w;
    //        cells[h][w] = shff[idx];
    //    }

    //    vector<int> As2(H);
    //    vector<int> Bs2(W);
    //    REP(h, H) {
    //        int mx = 0;
    //        REP(w, W) mx = max(mx, cells[h][w]);
    //        As2[h] = mx;
    //    }
    //    REP(w, W) {
    //        int mx = 0;
    //        REP(h, H) mx = max(mx, cells[h][w]);
    //        Bs2[w] = mx;
    //    }

    //    auto mine = solve(H, W, As2, Bs2);
    //    auto gt = solve_slow(H, W, As2, Bs2);
    //    if (gt != mine) {
    //        cout << "error! gt = " << gt << ", mine = " << mine << endl;
    //        REP(h, H) {
    //            REP(w, W) cout << cells[h][w] << " ";
    //            cout << endl;
    //        }
    //    }
    //    else {
    //        cout << "ok" << endl;
    //    }
    //}

    cout << solve(N, M, As, Bs) << endl;

    return 0;
}
