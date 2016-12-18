#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <climits>
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

int solve(string T, int offset) {
    auto len = SIZE(T);
    auto ans = 0;
    auto local_ans = 0;
    REP(i, len) {
        auto& ch = T[i];
        char prev_ch = 'z';
        if (i != 0) {
            prev_ch = T[i - 1];
        }
        if (ch == '?') {
            if ((offset + i) % 2) {
                ch = '2';
            }
            else {
                ch = '5';
            }
        }
        if (ch == '5' && prev_ch == '2') {
            local_ans += 2;
            ans = max(ans, local_ans);
        }
        else if (ch == '2' && prev_ch == '5') {
            // do nothing
        }
        else {
            local_ans = 0;
        }
    }
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    string T;
    cin >> T;
    cout << max(solve(T,0),solve(T,1)) << endl;
    return 0;
}
