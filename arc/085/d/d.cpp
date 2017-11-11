#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
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
    ll N, X, Y;
    cin >> N >> X >> Y;
    vector<ll> A(N);
    REP(n, N) cin >> A[n];
    reverse(ALL(A));

    vector<ll> mins(N);
    vector<ll> maxs(N);

    FOR(i, 2, N) {
        if (i == 2) {
            mins[i] = min(abs(A[0] - A[1]), abs(A[0] - A[2]));
            maxs[i] = max(abs(A[0] - A[1]), abs(A[0] - A[2]));
        }
        else {
            mins[i] = min(min(abs(A[0] - A[1]), abs(A[0] - A[i])), maxs[i - 1]);
            maxs[i] = max(max(abs(A[0] - A[1]), abs(A[0] - A[i])), mins[i - 1]);
        }
    }

    ll ans = -1e9;
    REP(i, N) {
        if (i == 0) {
            ans = abs(A[0] - Y);
        }
        else if (i == 1) {
            ans = max(ans, abs(A[0] - A[1]));
        }
        else {
            ans = max(ans, mins[i]);
        }
    }
    cout << ans << endl;

    return 0;
}
