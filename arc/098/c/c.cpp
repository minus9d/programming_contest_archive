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
    int N;
    string S;
    cin >> N >> S;

    vector<int> west(N);
    int i = 0;
    REP(n, N){
        if (S[n] == 'W') ++i;
        west[n] = i;
    }

    vector<int> east(N);
    int j = 0;
    for(int n = N-1; n >= 0; --n) {
        if (S[n] == 'E') ++j;
        east[n] = j;
    }

    // REP(n,N) cout << west[n] << " ";
    // cout << endl;
    // REP(n,N) cout << east[n] << " ";
    // cout << endl;

    int ans = 1e9;
    REP(n, N) {
        int t = 0;
        if (n != 0) t += west[n-1];
        if (n != N-1) t += east[n+1];
        ans = min(ans, t);
    }
    cout << ans << endl;

    return 0;
}
