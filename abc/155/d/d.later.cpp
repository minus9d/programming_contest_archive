// 本番中に実装しきれなかったものを後でAC
// 考え方は合っていた
//
// 実装をシンプルにするために、Aの要素を -, 0, +に分けて考える

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

ll N, K;
vector<ll> As;
vector<ll> neg;
vector<ll> pos;
vector<ll> zero;

//bool check(ll mid) {
//    ll s = 0;  // mid以下の数
//    REP(i, SIZE(As)) {
//        auto a = As[i];
//        auto it = upper_bound(As.begin(), As.end(), mid / a);
//        auto tmp = it - As.begin() - 1;
//        s += tmp;
//    }
//    return s >= K;
//}

ll check_neg(ll mid) {

    ll s = 0;
    REP(i, SIZE(neg)) {
        auto n = abs(neg[i]);
        auto it = lower_bound(pos.begin(), pos.end(), (abs(mid) + (n - 1)) / n);
        auto tmp = pos.end() - it;
        s += tmp;
    }

    return s;
}

ll solve_neg(ll k) {
    ll ng = -2e18;
    ll ok = 0;

    while (ok - ng > 1) {
        ll mid = (ng + ok) / 2;
        if (check_neg(mid) >= k) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

ll check_pos_sub(vector<ll>& arr, ll mid) {
    ll s = 0;
    REP(i, SIZE(arr)) {
        auto n = arr[i];
        auto it = upper_bound(arr.begin(), arr.end(), mid / n);
        ll tmp = (it - arr.begin());
        tmp -= (i + 1);
        s += max(0LL, tmp);
    }
    return s;
}

ll check_pos(ll mid) {

    ll s = 0;

    // neg同士
    s += check_pos_sub(neg, mid);
    // pos同士
    s += check_pos_sub(pos, mid);

    return s;
}

ll solve_pos(ll k) {
    ll ng = 0;
    ll ok = 2e18;

    while (ok - ng > 1) {
        ll mid = (ng + ok) / 2;
        if (check_pos(mid) >= k) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> K;
    As.resize(N);
    REP(n, N) {
        cin >> As[n];
        if (As[n] < 0) {
            neg.pb(abs(As[n]));
        }
        else if (As[n] > 0) {
            pos.pb(As[n]);
        }
        else {
            zero.pb(0);
        }
    }
    sort(ALL(As));
    sort(ALL(neg));
    sort(ALL(pos));

    ll pos_size = SIZE(pos);
    ll neg_size = SIZE(neg);
    ll zero_size = SIZE(zero);

    //ll pos_num =
    //    pos_size * (pos_size - 1) / 2
    //    + neg_size * (neg_size - 1) / 2;
    ll neg_num =
        pos_size * neg_size;
    ll zero_num = zero_size * (pos_size + neg_size)
        + zero_size * (zero_size - 1) / 2;

    if (K <= neg_num) {
        cout << solve_neg(K) << endl;
    }
    else if (K <= neg_num + zero_num) {
        cout << 0 << endl;
    }
    else {
         cout << solve_pos(K - neg_num - zero_num) << endl;
    }
    return 0;

}
