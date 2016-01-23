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
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    vector<pair<int,int>> nums(N-1);
    REP(n,N-1) {
        int t;
        cin >> t;
        nums[n] = mp(t,n);
    }
    sort(ALL(nums));
    
    vector<int> ans(N);
    for(auto e: nums) {
        int n = e.first;
        int idx = e.second;
        if (ans[idx] == 0) ans[idx] = n;
        if (ans[idx+1] == 0) ans[idx+1] = n;
    }
    
    REP(i,SIZE(ans)){
        cout << ans[i];
        if (i == SIZE(ans)-1) cout << endl;
        else cout << " ";
    }

    return 0;
}
