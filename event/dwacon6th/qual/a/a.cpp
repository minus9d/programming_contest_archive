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
    int N;
    cin >> N;
    vector<pair<string, int>> vec;
    REP(n, N) {
        string name;
        int time;
        cin >> name >> time;
        vec.pb({name, time});
    }
    string key;
    cin >> key;

    bool flag = false;
    ll ans = 0;
    for (auto e: vec) {
        if (flag) ans += e.second;
        if (e.first == key) flag = true;
    }
    cout << ans << endl;

    return 0;
}
