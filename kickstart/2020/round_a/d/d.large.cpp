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

ll dfs(vector<string>& strs, ll K, int s_idx, int e_idx, int ch_idx) {

    ll ans = 0;
    int idx = s_idx;
    REP(ch, 26) {

        int num_start_with_ch = 0;
        bool isFirst = true;
        int next_s_idx = -1;
        int next_e_idx = -1;

        while(1) {
            if (idx == e_idx) break;

            auto& str = strs[idx];
            if (ch_idx >= SIZE(str)) {
                ++idx;
                continue;
            }

            if (str[ch_idx] == 'A' + ch) {
                num_start_with_ch++;
                if (isFirst) {
                    next_s_idx = idx;
                    isFirst = false;
                }
                next_e_idx = idx + 1;
            } else {
                break;
            }
            ++idx;
        }

        ans += num_start_with_ch / K;
        if (next_s_idx != -1) {
            ans += dfs(strs, K, next_s_idx, next_e_idx, ch_idx + 1);
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
    sort(ALL(strs));

    cout << dfs(strs, K, 0, N, 0);
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
