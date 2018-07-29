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

ll bf(vector<ll>& Ss, int N, int O, int D) {
    ll ans = -1e18;
    REP(i, N) {
        ll sum = 0;
        ll sum_odd = 0;
        FOR(j, i, N) {
            sum += Ss[j];
            sum_odd += Ss[j] % 2;
            if (sum > D || sum_odd > O) break;
            ans = max(ans, sum);
        }
    }
    return ans;
}

ll fast(vector<ll>& Ss, ll N, ll O, ll D) {
    vector<ll> sum_Ss(N+1);
    vector<ll> sum_odds(N+1);
    REP(i, N) {
        if(i == 0) {
            sum_Ss[i+1] = Ss[i];
            sum_odds[i+1] = Ss[i] % 2;
        }
        else {
            sum_Ss[i+1] = Ss[i] + sum_Ss[i];
            sum_odds[i+1] = (Ss[i] % 2) + sum_odds[i];
        }
    }
    
    // cout << "sum_Ss: ";
    // REP(i, N+1) cout << sum_Ss[i] << " "; cout << endl;
    // cout << "sum_odds: ";
    // REP(i, N+1) cout << sum_odds[i] << " "; cout << endl;

    ll ans = -1e18;
    REP(s, N) {
        auto it1 = lower_bound(ALL(sum_odds), sum_odds[s] + O + 1);
        auto it2 = lower_bound(ALL(sum_Ss), sum_Ss[s] + D + 1);
        auto idx1 = it1 - sum_odds.begin();
        auto idx2 = it2 - sum_Ss.begin();
        auto idx_end = min(idx1, idx2);
        idx_end--;
        
        if (idx_end > s) {
            auto sum = sum_Ss[idx_end] - sum_Ss[s];
            ans = max(ans, sum);
            // cout << "sum:" << sum << endl;
        }
    }
    return ans;
}

void solve() {
    ll N, O, D;
    cin >> N >> O >> D;
    ll X1, X2, A, B, C, M, L;
    cin >> X1 >> X2 >> A >> B >> C >> M >> L;
    
    vector<ll> Xs(N);
    vector<ll> Ss(N);
    Xs[0] = X1;
    Xs[1] = X2;
    FOR(i, 2, N) {
        Xs[i] = (A * Xs[i-1] + B * Xs[i - 2] + C) % M;
    }
    REP(i, N) {
        Ss[i] = Xs[i] + L;
        // cerr << Ss[i] << " ";
    }
    // cerr << endl;

    auto ans = fast(Ss, N, O, D);
   
    if (ans == -1e18) cout << "IMPOSSIBLE";
    else cout << ans;
}

void test() {
    while(1) {
        int N = rand() % 10 + 2;
        int O = rand() % (N + 1);
        int D = rand() % 1000 - 500;
        vector<ll> Ss(N);
        REP(n, N) {
            Ss[n] = rand() % 6;
        }
        auto ans1 = bf(Ss, N, O, D);
        auto ans2 = fast(Ss, N, O, D);
        if (ans1 != ans2) {
            cout << "error!" << endl;
            cout << "N, O, D = " << N << ", " << O << ", " << D << endl;
            REP(n, N) cout << Ss[n] << " "; cout << endl;
            cout << "gt = " << ans1 << ", fast = " << ans2 << endl;
            exit(0);
        }
    }
}

int main(void)
{
    cin.sync_with_stdio(false);

    // test();

    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
