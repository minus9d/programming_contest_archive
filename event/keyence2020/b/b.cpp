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
    ll N;
    cin >> N;

    // right, left, center
    vector<tuple<ll, ll, ll>> arms;
    REP(n, N) {
        ll x, l;
        cin >> x >> l;
        ll left = x - l;
        ll right = x + l;
        arms.pb(mt(right, left, x));
    }
    sort(ALL(arms));

    ll prev = -1e9;
    ll ans = 0;
    for(auto arm: arms) {
        auto right = get<0>(arm);
        auto left = get<1>(arm);
        if (left >= prev) {
            prev = right;
            ++ans;
        }
    }
    cout << ans << endl;

    return 0;
}
