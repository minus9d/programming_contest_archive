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
    int N;
    cin >> N;
    vector<ll> A(N);
    REP(n, N) cin >> A[n];

    ll all = abs(A[0]);
    REP(n, N-1) {
        all += abs(A[n] - A[n+1]);
    }
    all += abs(0 - A[N-1]);

    REP(n, N) {
        ll tmp = all;
        if (n == 0) {
            tmp -= abs(A[0]);
            tmp -= abs(A[0] - A[1]);
            tmp += abs(A[1]);
        }
        else if (n == N-1) {
            tmp -= abs(A[N-1]);
            tmp -= abs(A[N-1] - A[N-2]);
            tmp += abs(A[N-2]);
        }
        else {
            tmp -= abs(A[n] - A[n-1]);
            tmp -= abs(A[n] - A[n+1]);
            tmp += abs(A[n+1] - A[n-1]);
        }
        cout << tmp << endl;
    }

    return 0;
}
