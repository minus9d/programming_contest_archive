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
    ll N, K;
    cin >> N >> K;
    vector<ll> Ps(N);
    vector<ll> Hs(N);
    vector<ll> Xs(K);
    vector<ll> Ys(K);
    vector<ll> As(4);
    vector<ll> Bs(4);
    vector<ll> Cs(4);
    vector<ll> Ms(4);
    cin >> Ps[0] >> Ps[1] >> As[0] >> Bs[0] >> Cs[0] >> Ms[0];
    cin >> Hs[0] >> Hs[1] >> As[1] >> Bs[1] >> Cs[1] >> Ms[1];
    cin >> Xs[0] >> Xs[1] >> As[2] >> Bs[2] >> Cs[2] >> Ms[2];
    cin >> Ys[0] >> Ys[1] >> As[3] >> Bs[3] >> Cs[3] >> Ms[3];
    FOR(i, 2, N) {
        Ps[i] = (As[0] * Ps[i-1] + Bs[0] * Ps[i-2] + Cs[0]) % Ms[0] + 1;
        Hs[i] = (As[1] * Hs[i-1] + Bs[1] * Hs[i-2] + Cs[1]) % Ms[1] + 1;
    }
    FOR(i, 2, K) {
        Xs[i] = (As[2] * Xs[i-1] + Bs[2] * Xs[i-2] + Cs[2]) % Ms[2] + 1;
        Ys[i] = (As[3] * Ys[i-1] + Bs[3] * Ys[i-2] + Cs[3]) % Ms[3] + 1;
    }

    // cout << endl;
    // REP(n, N) cout << Ps[n] << " "; cout << endl;
    // REP(n, N) cout << Hs[n] << " "; cout << endl;
    // REP(k, K) cout << Xs[k] << " "; cout << endl;
    // REP(k, K) cout << Ys[k] << " "; cout << endl;

    // small
    int ans = 0;
    REP(k, K) {
        auto x = Xs[k];
        auto y = Ys[k];
        bool ok = false;
        REP(n, N) {
            auto p = Ps[n];
            auto h = Hs[n];
            if ( (h - y) >= abs(p - x) ) ok = true;
        }
        ans += ok;
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
