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
    cin >> N;
    vector<int> Hs(N);
    REP(n, N) cin >> Hs[n];
    
    int ans = 0;
    while(true) {
        int mx = -10;
        int l = -10;
        int r = -10;
        REP(n, N) {
            int h = Hs[n];
            if (h > mx) {
                l = r = n;
                mx = h;
            }
            else if (h == mx) {
                if (r == n - 1) {
                    r = n;
                } else {
                    l = r = n;
                }
            }
        }
        // cout << "mx, l, r = " << mx << "," << l << "," << r << endl;
        if (mx == 0) break;
        ++ans;
        FOR(n, l, r + 1) Hs[n]--;
    }
    cout << ans << endl;
    return 0;
}
