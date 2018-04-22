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

ll N, C;
vector<ll> Xs;
vector<ll> Vs;

vector<ll> clock_gains;
vector<ll> clock_max_gains;
vector<ll> anticlock_gains;
vector<ll> anticlock_max_gains;

ll clockwise() {
    ll gain = 0;
    ll max_gain = 0;
    clock_gains.resize(N);
    clock_max_gains.resize(N);
    REP(n, N) {
        if (n == 0) {
            gain += Vs[n] - Xs[n];
        }
        else {
            gain += Vs[n] - (Xs[n] - Xs[n-1]);
        }
        max_gain = max(max_gain, gain);
        clock_gains[n] = gain;
        clock_max_gains[n] = max_gain;
    }
    return max_gain;
}

ll anticlockwise() {
    ll gain = 0;
    ll max_gain = 0;
    anticlock_gains.resize(N);
    anticlock_max_gains.resize(N);
    for(int n = N-1; n >= 0; --n) {
        if(n == N-1) {
            gain += Vs[n] - (C - Xs[n]);
        }        
        else {
            gain += Vs[n] - abs(Xs[n] - Xs[n+1]);
        }
        max_gain = max(max_gain, gain);
        anticlock_gains[n] = gain;
        anticlock_max_gains[n] = max_gain;
    }
    return max_gain;
}

ll clockwise_and_anticlockwise() {
    // i番目まで時計方向
    ll ans = 0;
    REP(i, N-1) {
        ll gain = clock_gains[i];
        gain -= Xs[i];
        gain += anticlock_max_gains[i+1];
        ans = max(ans, gain);
    }
    return ans;
}
ll anticlockwise_and_clockwise() {
    // i番目まで逆時計方向
    ll ans = 0;
    FOR(i, 1, N) {
        ll gain = anticlock_gains[i];
        gain -= (C - Xs[i]);
        gain += clock_max_gains[i-1];
        ans = max(ans, gain);
    }
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> C;
    Xs.resize(N);
    Vs.resize(N);
    REP(n, N) cin >> Xs[n] >> Vs[n];

    ll ans1 = clockwise();
    ll ans2 = anticlockwise();
    ll ans3 = clockwise_and_anticlockwise();
    ll ans4 = anticlockwise_and_clockwise();

    
    cout << max(max(max(ans1,ans2),ans3),ans4) << endl;

    return 0;
}
