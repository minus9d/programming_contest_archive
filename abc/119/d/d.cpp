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
    ll A, B, Q;
    cin >> A >> B >> Q;
    vector<ll> Ss(A);
    REP(a, A) cin >> Ss[a];
    vector<ll> Ts(B);
    REP(b, B) cin >> Ts[b];
    REP(q, Q) {
        ll x;
        cin >> x;
        vector<ll> S_cand;
        auto s1 = lower_bound(ALL(Ss), x);
        if (s1 != Ss.begin()) S_cand.push_back(*(s1--));
        if (s1 != Ss.end()) S_cand.push_back(*s1);
        vector<ll> T_cand;
        auto t1 = lower_bound(ALL(Ts), x);
        if (t1 != Ts.begin()) T_cand.push_back(*(t1--));
        if (t1 != Ts.end()) T_cand.push_back(*t1);
        
        ll ans = 1e18;
        for(auto s: S_cand) {
            for(auto t: T_cand) {
                ll tmp1 = abs(s - x) + abs(t - s);
                ll tmp2 = abs(t - x) + abs(t - s);
                ans = min(ans, min(tmp1, tmp2));
            }
        }
        cout << ans << endl;
    }

    return 0;
}
