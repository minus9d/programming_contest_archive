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

int main(void)
{
    cin.sync_with_stdio(false);
    int N,A;
    cin >> N >> A;
    vector<int> Xs(N);
    REP(n,N) cin >> Xs[n];

    ll ans = 0;
    REP(i, 1 << N) {
        if (i == 0) continue;
        ll sum = 0;
        ll n = 0;
        REP(j, N) {
            if (i & (1 << j)) {
                sum += Xs[j];
                ++n;
            }
        }
        if (n * A == sum) {
            ++ans;
        }
    }
    cout << ans << endl;

    return 0;
}
