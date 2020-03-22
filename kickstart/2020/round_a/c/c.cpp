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

bool check(ll diff, ll N, ll K, vector<ll>& Ms) {
    ll need = 0;
    REP(n, N - 1) {
        ll gap = Ms[n + 1] - Ms[n];
        need += (gap - 1) / diff;
    }
    // cout << "diff, need = " << diff << ", " << need << endl;
    return need <= K;
}

void solve() {
    ll N, K;
    cin >> N >> K; 
    vector<ll> Ms(N);
    REP(n, N) {
        cin >> Ms[n];
    }

    // difficulty 1?
    ll tmp = 0;
    REP(n, N - 1) {
        ll gap = Ms[n + 1] - Ms[n];
        tmp += gap - 1;
    }
    if (tmp <= K) {
        cout << 1;
        return;
    }

    ll ng = 1;
    ll ok = 1e9 + 10;
    while (ok - ng > 1) {
        ll mid = (ok + ng) / 2;
        if (check(mid, N, K, Ms)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    cout << ok;
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
