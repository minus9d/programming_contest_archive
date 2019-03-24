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

void solve() {
    ll N, P;
    cin >> N >> P;
    vector<ll> Ss(N);
    REP(n, N) cin >> Ss[n];
    sort(ALL(Ss));

    ll left = 0;
    ll right = left + P - 1;
    ll ans = 1e18;

    ll prev = 0;
    while(right < N) {
        ll need = 0;
        if (left == 0) {
            REP(i, right) {
                need += Ss[right] - Ss[i];
            }
        } else {
            need = prev - (Ss[right - 1] - Ss[left - 1]);
            need += (Ss[right] - Ss[right - 1]) * (P - 1);
        }
        ans = min(ans, need);
        prev = need;
        ++left;
        ++right;
        // cout << "left, need = " << left << "," << need << endl;
    }
    cout << ans;
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
