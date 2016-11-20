#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
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

int N, K, S, T;
bool check(int k) {
    
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> K >> S >> T;
    vector<int> Cs(N);
    vector<int> Vs(N);
    REP(n,N) {
        cin >> Cs[n] >> Vs[n];
    }
    vector<int> gas_loc(K);
    REP(k,K) cin >> gas_loc[k];
    gas_loc.pb(0);
    gas_loc.pb(S);
    sort(ALL(gas_loc));
    vector<int> distances;
    FOR(i,1,SIZE(gas_loc)) {
        distances.pb(gas_loc[i] - gas_loc[i-1]);
    }

    // int min_tank = *min_element(ALL(distances));
    // cout << "min_tank = " << min_tank << endl;

    if (T < S) {
        cout << -1 << endl;
        return 0;
    }

    // find min capacity
    int lo = 0;
    int hi = 1000000005;
    while (lo < hi) {
        int k = (lo + hi) / 2;

        bool fail = false;
        int time_sum = 0;
        for(auto di: distances) {
            if (k < di) {
                fail = true;
                break;
            }
            int k2 = min(k, 2*di);
            time_sum += (2*di - (k2 - di));
        }
        if (!fail && time_sum <= T) {
            hi = k;
        }
        else {
            lo = k + 1;
        }
    }
    // cout << "lo:" << lo << endl;
    int lo_cap = lo;
    
    int MAX = 1e9 + 1000;
    int ans = MAX;
    REP(n,N) {
        int c = Cs[n];
        int v = Vs[n];
        if (v >= lo_cap) {
            ans = min(ans, c);
        }
    }
    if (ans == MAX) {
        cout << -1 << endl;
    }
    else {
        cout << ans << endl;
    }
   
    return 0;
}
