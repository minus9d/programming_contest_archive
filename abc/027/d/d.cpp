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

int main(void)
{
    cin.sync_with_stdio(false);
    string s;
    cin >> s;

    vector<int> table;
    int sum = 0;
    for(int i = SIZE(s)-1; i >= 0; --i) {
        if (s[i] == '+') ++sum;
        else if (s[i] == '-') --sum;
        else table.pb(sum);
    }
    
    sort(ALL(table));

    int ans = 0;
    REP(i,SIZE(table)/2) ans -= table[i];
    FOR(i,SIZE(table)/2,SIZE(table)) ans += table[i];

    cout << ans << endl;

    return 0;
}
