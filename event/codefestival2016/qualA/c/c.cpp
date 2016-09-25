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

int main(void)
{
    cin.sync_with_stdio(false);
    string s;
    cin >> s;
    int K;
    cin >> K;

    string ans = "";
    for (auto ch : s) {
        if (ch == 'a') {
            ans += 'a';
            continue;
        }
        int need = 26 - (ch - 'a');
        if (need <= K) {
            ans += 'a';
            K -= need;
        }
        else {
            ans += ch;
        }
    }

    int num = ans.back() - 'a';
    num = (num + K) % 26;
    ans.back() = ('a' + num);

    cout << ans << endl;

    return 0;
}
