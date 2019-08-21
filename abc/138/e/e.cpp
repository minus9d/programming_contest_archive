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

ll solve(string s, string t) {
    int s_len = SIZE(s);
    map<char, vector<ll>> ch2loc;
    REP(i, s_len) {
        auto ch = s[i];
        ch2loc[ch].pb(i);
    }

    ll ans = 0;
    ll prev = -1;
    bool ok = true;
    for(auto ch: t) {
        if (SIZE(ch2loc[ch]) == 0) {
            ok = false;
            break;
        } else {
            auto it = lower_bound(ALL(ch2loc[ch]), prev + 1);
            if (it == ch2loc[ch].end()) {
                ans += (s_len - prev) + ch2loc[ch][0];
                prev = ch2loc[ch][0];
            } else {
                ans += *it - prev;
                prev = *it;
            }
        }
        // cout << "prev = " << prev << ", ans = " << ans << endl;
    }
    if (ok) {
        return ans;
    } else {
        return -1;
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    string s;
    cin >> s;
    string t;
    cin >> t;

    cout << solve(s, t) << endl;

    // assert(solve("a", "aaa") == 3);

    return 0;
}
