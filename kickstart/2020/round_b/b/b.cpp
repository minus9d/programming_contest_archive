#include <algorithm>
#include <array>
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
typedef long long ll;
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())
template<class T> inline bool chmin(T& a, T b) {
    if (a > b) {
        a = b; return true;
    }
    return false;
}
template<class T> inline bool chmax(T& a, T b) {
    if (a < b) {
        a = b; return true;
    }
    return false;
}
#define pb push_back
#define mp make_pair
#define mt make_tuple

bool check(ll day, vector<ll> Xs, ll D) {
    for (auto x: Xs) {
        day = (day + x - 1) / x * x;
    }
    return day <= D;
}

void solve() {
    ll N, D;
    cin >> N >> D;
    vector<ll> Xs(N);
    REP(n, N) cin >> Xs[n];

    ll lo = 1;
    ll hi = 1e12 + 1;

    while (hi - lo > 1) {
        ll mid = (lo + hi) / 2;
        (check(mid, Xs, D) ? lo : hi) = mid;
    }
    cout << lo;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
