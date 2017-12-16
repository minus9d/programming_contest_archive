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


void solve(vector<pair<int,int>>& ans, vector<ll>& A, int N) {
    // 全部に最大値を足して、全部+にする
    auto mxItr = max_element(ALL(A));
    auto mxIdx = mxItr - A.begin();
    REP(i, N) {
        if (i != mxIdx) {
            ans.pb(mp(mxIdx, i));
        }
    }
    FOR(i, 1, N) {
        ans.pb(mp(i-1, i));
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<ll> A(N);
    ll mn = 1e9;
    ll mx = -1e9;
    REP(n,N) {
        cin >> A[n];
        mn = min(mn, A[n]);
        mx = max(mx, A[n]);
    }

    vector<pair<int,int>> ans;
    if (abs(mx) > abs(mn)) {
        solve(ans, A, N);

        cout << SIZE(ans) << endl;
        for(auto a: ans) {
            cout << (a.first + 1) << " " << (a.second + 1) << endl;
        }
    }
    else {
        vector<ll> B(N);
        REP(n,N) {
            B[n] = -A[N-n-1];
        }
        solve(ans, B, N);

        cout << SIZE(ans) << endl;
        for(auto a: ans) {
            auto f = a.first;
            auto s = a.second;
            f = N - f - 1;
            s = N - s - 1;
            cout << (f + 1) << " " << (s + 1) << endl;
        }
    }

    return 0;
}
