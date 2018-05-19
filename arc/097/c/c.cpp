// これは本番で書いたコード
// 後から解説を見ると、各位置について5文字分だけ調べれば十分だった

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
    string s;
    cin >> s;
    int len = SIZE(s);
    int K;
    cin >> K;

    vector<string> top5;
    REP(i, len) {
        string t;
        //cerr << "i: " << i << endl;
        FOR(j, i, len) {
            t += s[j];

            auto it = lower_bound(ALL(top5), t);
            if (SIZE(top5) == 5 && it == top5.end()) {
                break;
            }
            else if (SIZE(top5) > 0 && it != top5.end() && t == *it) {
                continue;
            }
            else {
                top5.insert(it, t);
                if (SIZE(top5) > 5) top5.pop_back();
            }
        }
    }
    cout << top5[K-1] << endl;

    return 0;
}
