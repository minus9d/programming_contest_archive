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

int main(void)
{
    int N, M, K;
    cin >> N >> M >> K;

    if (K != 1) return 0;
    
    vector<ll> As(N);
    vector<ll> Bs(M);
    REP(n,N) cin >> As[n];
    REP(m,M) cin >> Bs[m];

    ll sum_a = accumulate(ALL(As), 0LL);
    ll sum_b = accumulate(ALL(Bs), 0LL);

    ll ans = 0;
    REP(n,N) {
        REP(m,M) {
            ll a = sum_a - As[n] + Bs[m];
            ll b = sum_b - Bs[m] + As[n];
            ans = max(ans, a * b);
        }
    }

	cout << ans << endl;

    return 0;
}
