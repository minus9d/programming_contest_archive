#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, A, B;
    cin >> N >> A >> B;
    vector<ll> Ss(N);
    REP(n, N) cin >> Ss[n];

    ll sum = accumulate(ALL(Ss), 0LL);
    
    vector<ll> larges(N-1);
    FOR(i, 1, N) larges[i-1] = Ss[i];
    sort(ALL(larges), greater<ll>());

    int ans = 0;
    int idx = 0;
    while ( Ss[0] * A < B * sum ) {
        sum -= larges[idx];
        ++idx;
        ++ans;
    }
    cout << ans << endl;
    return 0;
}


