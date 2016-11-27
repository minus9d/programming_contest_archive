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

int get_pair_num(const vector<int>& v) {
    // v is sorted
    int prev = -1;
    int ans = 0;
    for(auto e: v) {
        if (e == prev) {
            ++ans;
            prev = -1;
        }
        else {
            prev = e;
        }
    }
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<int> Xs(N);
    REP(n,N) {
        cin >> Xs[n];
    }
    sort(ALL(Xs));


    vector<vector<int>> nums(M);
    REP(n,N) {
        int x = Xs[n];
        nums[x % M].pb(x);
    }

    ll ans = 0;
    REP(m, M / 2 + 1) {
        if (m == 0 || m * 2 == M) {
            ans += SIZE(nums[m]) / 2;
        }
        else {
            int n = M - m;
            auto size_m = SIZE(nums[m]);
            auto size_n = SIZE(nums[n]);
            ans += min(size_m, size_n);
            int pair_num = (size_m < size_n) ?
                get_pair_num(nums[n]) : 
                get_pair_num(nums[m]);
            ans += min(abs(size_m - size_n) / 2,
                       pair_num);
        }
    }
    cout << ans << endl;

    return 0;
}
