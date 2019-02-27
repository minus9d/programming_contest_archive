//  まったく分からないので解説PDFと
//  https://betrue12.hateblo.jp/entry/2018/08/26/122740を見る
//
//  前提知識として中央値の言いかえを使う
//  ある数列が与えられたとき、「X以上の要素数がceil(M/2)個以上ある」
//  最大の整数が、中央値。
//  例えば、上の条件を満たす整数をo, 満たさない整数をxとすると
//  以下のようになったとする。
//           x x  
//     o o o 
//     1 2 3 4 5
//  この場合3が中央値。これは二分探索で求まる。
//
//  本問題にて与えられる数列の長さはN。
//  Nの部分数列の数KはN*(N+1)/2。
//  すなわち新たに作られる数列mの長さはK。
//  数列mの中央値は、さっき述べたように、
//  「X以上の要素数がceil(K/2)個以上ある」最大の整数Xを二分探索で求める
//  ことで得られる。
//
//  この二分探索を実現するためには、N*(N+1)/2個の部分数列すべてのうち
//  「その中央値は整数X以上」であるものが何個かを高速に求める必要がある。
//  ナイーブにやると間に合わないが、
//  もとの数列でX以上の要素を+1, X未満の要素を-1と置き換えると、
//  和がゼロ以上の部分数列の数を求める問題に帰着する。
//  これはBITにより高速に求めることができるようになる
//
//  知識
//    * 中央値が出てきたら「X以上の要素数がceil(M/2)個以上ある」置き換えで
//      二分探索が使えないか考える


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

// 1 originなので注意!!
class Bit
{
private:
    int m_n;
    vector<int> m_bit;
    
public:
    void init(int n) {
        m_n = n;
        m_bit.resize(n + 1);
    }

    int sum(int i) {
        int s = 0;
        while (i > 0) {
            s += m_bit[i];
            i -= i & -i;
        }
        return s;
    }
    
    void add(int i, int x) {
        while (i <= m_n) {
            m_bit[i] += x;
            i += i & -i;
        }
    }
};

template <typename T>
ll getNumberOfSegmentsWhoseSumIsNotNegative(const vector<T>& arr) {
    auto N = SIZE(arr);
    // まず累積和作成  のちの計算を簡単にするため先頭に0を入れる
    vector<T> cum(N+1);
    REP(i, N) cum[i + 1] += cum[i] + arr[i];

    // BITを使うため最小値を1に
    auto mn = *min_element(ALL(cum));
    auto offset = -mn + 1;
    for(auto& e: cum) e += offset;
    auto mx = *max_element(ALL(cum));

    ll ans = 0;
    Bit bit; bit.init(mx);
    bit.add(offset, 1);
    FOR(i, 1, N + 1) {
        auto c = cum[i];
        ans += bit.sum(c);
        bit.add(c, 1);
    }
    return ans;
}

bool judge(ll k, ll N, vector<ll>& As) {
    // k以上なら+1, k未満なら-1な数列を生成
    vector<ll> Bs(N);
    REP(i, N) {
        Bs[i] = (As[i] >= k) ? 1 : -1;
    }
    // 和が0以上の区間の数
    auto n = getNumberOfSegmentsWhoseSumIsNotNegative(Bs);
    ll border = (N * (N + 1) / 2 + 1) / 2;
    return n < border;
}

ll solve(ll N, vector<ll>& As) {
    ll lo = 1;
    ll hi = 1e9 + 1; // 1e9にしたせいで1WA
    
    while(lo < hi) {
        auto k = (lo + hi) / 2;
        if (judge(k, N, As)) {
            hi = k;
        } else {
            lo = k + 1;
        }
    }
    return lo - 1;
}

ll solve_slow(ll N, vector<ll>& As) {
    vector<ll> Bs;
    REP(i, N) {
        FOR(j, i, N) {
            vector<ll> tmp;
            FOR(k, i, j + 1) {
                tmp.pb(As[k]);
            }
            sort(ALL(tmp));
            auto idx = SIZE(tmp) / 2;
            Bs.pb(tmp[idx]);
        }
    }
    sort(ALL(Bs));
    auto idx = SIZE(Bs) / 2;
    return Bs[idx];
}


int main(void)
{
    cin.sync_with_stdio(false);
    ll N;
    cin >> N;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];
    cout << solve(N, As) << endl;

    return 0;

    // // エラーテスト用
    // {
    //     ll N = 1;
    //     while(true) {
    //         REP(rep, 100) {
    //             cout << "N = " << N << endl;
    //             vector<ll> As;
    //             REP(n, N) {
    //                 As.pb((ll)(rand() % 10000) * (rand() % 100000) + 1);
    //             }
    //             auto myans = solve(N, As);
    //             auto gt = solve_slow(N, As);
    //             if (myans != gt) {
    //                 cout << "error!" << endl;
    //                 cout << N;
    //                 for(auto a: As) cout << a << " ";
    //                 cout << endl;
    //                 return 0;
    //             }
    //         }
    //         ++N;
    //     }
    // }
}
