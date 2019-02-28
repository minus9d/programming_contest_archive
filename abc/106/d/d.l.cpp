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
    int N, M, Q;
    cin >> N >> M >> Q;

    vector<vector<int>> Ls(N + 1);
    REP(m, M) {
        int l, r;
        cin >> l >> r;
        Ls[l].pb(r);
    }
    FOR(n, 1, N + 1) sort(ALL(Ls[n]));
    
    REP(dummy, Q) {
        int p, q;
        cin >> p >> q;
        int ans = 0;
        FOR(l, p, q + 1) {
            auto it = lower_bound(ALL(Ls[l]), q + 1);
            ans += it - Ls[l].begin();
        }
        cout << ans << endl;
    }

    return 0;
}
