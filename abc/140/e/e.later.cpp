// 解説記事を読んでAC
//
// 「2番めに大きい値がXになる区間の数」を求める言い換えに気づくことが重要

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

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    vector<int> locs(N + 1);
    REP(n, N) {
        int p;
        cin >> p;
        locs[p] = n + 1;
    }

    // 番兵を入れる
    multiset<int> seen;
    seen.insert(0);
    seen.insert(0);
    seen.insert(N + 1);
    seen.insert(N + 1);

    // 2番めに大きい値が4となる範囲を考える
    // 4より大きい要素のうち、4のすぐ左側にある2つの要素にw, xと名前をつける
    // 4より大きい要素のうち、4のすぐ右側にある2つの要素にy, zと名前をつける
    // 4が2番目となる区間は、xまたはyのどちらかのみが含まれる区間

    // inf               inf
    // inf 1 5 2 4 3 7 6 inf
    //  w    x       y z
    //

    ll ans = 0;
    for(int n = N; n >= 1; --n) {
        auto loc = locs[n];
        auto it = seen.lower_bound(loc);
        auto y = *it;
        ++it;
        auto z = *it;
        --it;
        --it;
        auto x = *it;
        --it;
        auto w = *it;
        // cout << "loc of " << n << ": " << loc << endl;
        // cout << "y = " << y << endl;
        // cout << "z = " << z << endl;
        // cout << "x = " << x << endl;
        // cout << "w = " << w << endl;

        ll combination = (x - w) * (y - loc);
        combination += (z - y) * (loc - x);
        ans += combination * n;

        // cout << "added: " << (x - w) * (y - loc) << endl;
        // cout << "added: " << (z - y) * (loc - x) << endl;

        seen.insert(loc);
    }

    cout << ans << endl;

    return 0;
}
