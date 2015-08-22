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
#include <complex>
#include <cstdlib>
#include <cstring>

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

ll MOD = 1000000007;
int N;
vector<int> vals;
int seen[3001][4][3001];

ll dp(int idx, int remain, int prev_idx) {
    if (seen[idx][remain][prev_idx] != -1) return seen[idx][remain][prev_idx];
    ll ans = 0;
    
    // printf("dp(%d,%d,%d)\n", idx,remain,prev_idx);
    if (idx == N) {
        ans = remain == 0;
    }
    else {
        if (remain == 0) ans = 1;
        else {
            // auto choose = lower_bound(ALL(vals), prev * 2);
            // if (choose == vals.end()) return 0;

            auto t = dp(idx+1, remain, prev_idx);
            if (prev_idx == -1 || vals[idx] >= vals[prev_idx] * 2) {
                t += dp(idx+1, remain-1, idx);
            }
            ans = t % MOD;
        }
    }
    return seen[idx][remain][prev_idx] = ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N;
    vals.resize(N);

    memset(seen, 0xff, sizeof(seen));

    REP(n,N) cin >> vals[n];
    sort(ALL(vals));

    cout << dp(0, 4, -1) << endl;
    
    return 0;
}
