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


// 1: loop  -1: not loop  0: unknown
char cache[1010][1010];

int rev(int x) {
    auto s = to_string(x);
    reverse(ALL(s));
    return stoi(s);
}

int check(int n, int m) {
    if (m < n) swap(n, m);
    if (cache[n][m] != 0) return cache[n][m] == 1;
    set<pair<int, int>> history;
    int res = 0;
    while(true) {
        if (history.count({n,m})) {
            res = 1;
            break;
        }
        history.insert({n,m});
        if (n * m == 0) {
            res = -1;
            break;
        }
        n = rev(n);
        if (m < n) swap(n, m);
        m -= n;
        if (m < n) swap(n, m);
        if (cache[n][m] != 0) {
            res = cache[n][m];
            break;
        }
    }
    for (auto h: history) {
        cache[h.first][h.second] = res;
    }
    return res == 1;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    int ans = 0;
    FOR(n, 1, N+1) {
        FOR(m, 1, M+1) {
            ans += check(n, m);
        }
    }
    cout << ans << endl;
    return 0;
}
