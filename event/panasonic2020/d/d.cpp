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

vector<char> str;

void dfs(int idx, int used, int N) {
    if (idx == N) {
        for(auto ch: str) cout << ch;
        cout << endl;
        return;
    }
    REP(i, used + 1) {
        str[idx] = 'a' + i;
        dfs(idx + 1, max(used, i + 1), N);
    }
}


int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    str.resize(N);

    dfs(0, 0, N);

    return 0;
}
