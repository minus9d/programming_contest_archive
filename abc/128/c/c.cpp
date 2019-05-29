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
    int N, M;
    cin >> N >> M;

    vector<vector<int>> Ss(M, vector<int>());
    vector<int> Ps(M);
    REP(m, M) {
        int K;
        cin >> K;
        REP(k, K) {
            int s;
            cin >> s;
            --s;
            Ss[m].pb(s);
        }
    }
    REP(m, M) cin >> Ps[m];

    int ans = 0;
    REP(i, 1 << N) {
        bool ok = true;
        REP(m, M) {
            int sum = 0;
            for(auto s: Ss[m]) {
                if (i & (1 << s)) sum++;
            }
            if ((sum % 2) != Ps[m]) {
                ok = false;
            }
        }
 
        ans += ok;
    }
    cout << ans << endl;

    return 0;
}
