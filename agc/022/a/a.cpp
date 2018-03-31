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

bool isMAX(string S, int MAX) {
    if (SIZE(S) != MAX) return false;
    REP(i, MAX) {
        char ch = 'a' + (MAX - i - 1);
        if (S[i] != ch) return false;
    }
    return true;
}

string solve(string S, int MAX) {
    if (isMAX(S, MAX)) {
        return "-1";
    }
    else if (SIZE(S) != MAX) {
        set<char> seen(ALL(S));
        REP(i, MAX) {
            auto ch = 'a' + i;
            if (!seen.count(ch)) {
                S += ch;
                return S;
            }
        }
    }
    else if (S[MAX-2] < S[MAX-1]) {
        string ans;
        REP(i, MAX-2) ans += S[i];
        ans += S[MAX-1];
        return ans;
    } else {
        char prev = S[MAX-1];
        for(int i = MAX-2; i >= 0; --i) {
            char ch = S[i];
            if (ch > prev) {
                prev = ch;
            }
            else {
                string ans;
                REP(j, i) ans += S[j];

                char add = S[i+1];
                FOR(j, i+2, MAX) {
                    if (S[j] > S[i] && S[j] < add) add = S[j];
                }
                ans += add;
                return ans;
            }
        }
    }
    
}

int main(void)
{
    cin.sync_with_stdio(false);

    // vector<string> check {
    //     "a", "ab", "abc", "ac", "acb",
    //     "b", "ba", "bac", "bc", "bca",
    //     "c", "ca", "cab", "cb", "cba",
    // };
    // REP(i, SIZE(check)-1) {
    //     auto ans = solve(check[i], 3);
    //     auto expected = check[i+1];
    //     if (ans != expected) {
    //         cout << "error! query = " << check[i] << ", ans = " << ans << ", expected = " << expected << endl;
    //     }
    // }

    string S;
    cin >> S;
    cout << solve(S, 26) << endl;


    return 0;
}
