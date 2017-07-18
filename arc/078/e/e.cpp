// N = 123 のとき
//   YESとなるのは 1, [10, 12], [100, 999], [1230, 9999], ...
//   よって、1, 10, 100, .. と順に調べていき、初めてNOになる場所を探す。
//   上記の場合は1000で初めてNOになる。
//   次に1000から値を増やしていき、初めてYESになる場所を二分探索で調べる。
//   上記の場合は1230で始めてYESになる。
//   1230を10で割ったものが求める答。
// N = 100のとき
//   N = 1, 10, 100, ...のときはコーナーケースとして別途処理する必要がある。
//   N = 100のとき、YESとなるのは1, 10, [100, ∞]。
//   N = 1e10を試してYESであれば、この場合であることが分かる。
//   あとは、1e10 + 1, 1e9 + 1と順にためしていき、初めてNOとなる場所を見つける


#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
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

bool check(ll n) {
    cout << "? " << n << endl << flush;
    string ans;
    cin >> ans;
    return (ans == "Y");
}

int main(void)
{
    // cin.sync_with_stdio(false);
    ll MAX = 1000000000;
    if (check(MAX * 10)) {
        ll query = MAX / 10;
        bool found = false;
        while(query >= 1) {
            if (check(query + 1)) {
                query /= 10;
            }
            else {
                found = true;
                break;
            }
        }
        ll ans = 1;
        if (found) ans = query * 10;
        cout << "! " << ans << endl << flush;
        return 0;
    }


    ll query = 1;
    while(1) {
        if (check(query)) {
            query *= 10;
        }
        else break;
    }

    ll lo = query;
    ll hi = query * 10 - 1;
    while(lo < hi) {
        ll k = (lo + hi) / 2;
        if (check(k)) {
            hi = k;
        }
        else {
            lo = k + 1;
        }
    }
    cout << "! " << lo / 10 << endl << flush;

    return 0;
}
