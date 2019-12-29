// コンテスト後に自力AC
// コンテスト中に考えていた方針は正しかったが実装が間に合わず
//
// N人のゲストの組合せはN * N通り。

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

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

ll N, M;
vector<ll> As;
vector<ll> sumA;

// 値がsum以上の組合せは何個あるか？
ll count_pair_num(ll sum) {
    ll ret = 0;
    for(auto a: As) {
        auto it = lower_bound(ALL(As), sum - a);
        ret += N - (it - As.begin());
    }
    return ret;
}

// 値がsum以上の組合せはpair_num個以上あるか？
bool check(ll sum, ll pair_num) {
    return count_pair_num(sum) >= pair_num;
}

// 値がsum以下の組合せの値の合計を求める
// 事前に累積和の計算が必要
ll count_sum(ll num) {
    ll ret = 0;
    // e.g.  a = 5
    // 例えばAs = [1 3 3 5 5 21 24 34 110], num = 26のとき
    // 26以上になる組合せは(5, 21), (5, 24), (5, 34), (5, 110)
    // 値の合計は、(5 * 4) + (21 + 24 + 34 + 110)
    // この第二項の計算には累積和を使う
    for(auto a: As) {
        auto it = lower_bound(ALL(As), num - a);
        if (it != As.end()) {
            auto tmp1 = sumA[it - As.begin()];
            auto tmp2 = (As.end() - it);
            ret += tmp1 + a * tmp2;
        }
    }
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);

    cin >> N >> M;
    As.resize(N);
    REP(n, N) cin >> As[n];
    sort(ALL(As));

    // 累積和
    sumA.resize(N);
    REP(n, N) {
        if (n == 0) sumA[N - n - 1] = As[N - n - 1];
        else sumA[N - n - 1] = sumA[N - n] + As[N - n - 1];
    }

    // 「X以上の組合せの数」がM以上となる最大のXを二分探索で求める
    ll ok = 0;
    ll ng = As[N-1] * 2 + 1; // 最初 As[N-1] * 2 にしててエラー; 確実に境界をみつけるためには+1が必要
    while (ng - ok > 1) {
        auto mid = (ok + ng) / 2;
        if (check(mid, M)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }

    // 値がok以上の組合せの数を求める
    // この組合せの数はM以上である
    auto pair_num = count_pair_num(ok);

    // 値がok + 1以上の組合せの数を求める
    // この組合せの数は必ずMより小さいことが保証される
    auto pair_num2 = count_pair_num(ok + 1);

    // 値がok + 1以上の組合せの数の和を求める
    ll ans = count_sum(ok + 1);

    // この時点で、(M - pair_num2)個の組合せの分がまだansに反映されていない
    // この組合せは、すべて値がokであることが保証される
    ans += (M - pair_num2) * ok;

    cout << ans << endl;

    return 0;
}

