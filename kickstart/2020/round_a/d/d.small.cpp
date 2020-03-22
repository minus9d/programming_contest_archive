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

ll dfs(vector<string>& strs, ll K) {
    vector<vector<string>> strsList(27, vector<string>());
    for(auto& s: strs) {
        strsList[s[0] - 'A'].pb(s);
    }

    ll ans = 0;
    REP(ch, 27) {
        auto& starts_with_ch = strsList[ch];
        ans += SIZE(starts_with_ch) / K;
        vector<string> next;
        for(auto s: starts_with_ch) {
            if (SIZE(s) > 1) {
                next.pb(s.substr(1));
            }
        }
        if (SIZE(next) > 0) {
            ans += dfs(next, K);
        }
    }

    //cout << "strs ";
    //for(auto s: strs) cout << s << ",";
    //cout << " ans = " << ans << endl;

    return ans;
}


void solve() {
    ll N, K;
    cin >> N >> K; 
    vector<string> strs(N);
    REP(n, N) {
        cin >> strs[n];
    }

    cout << dfs(strs, K);
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
