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
    map<string, int> m;
    REP(n, N) {
        string s;
        cin >> s;
        m[s]++;
    }

    int mx = 0;
    for(auto kv: m) {
        mx = max(kv.second, mx);
    }

    set<string> words;
    for(auto kv: m) {
        if (kv.second == mx) words.insert(kv.first);
    }
    for(auto w: words) cout << w << endl;

    return 0;
}

