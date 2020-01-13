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
    int N, M;
    cin >> N >> M;



    vector<int> ac_flags(N);
    vector<int> wa_count(N);

    int ac = 0;
    REP(m, M) {
        int p; string s;
        cin >> p >> s;
        --p;
        if (ac_flags[p]) continue;

        if (s == "WA") {
            ++wa_count[p];
        }
        else {
            ac_flags[p] = 1;
            ++ac;
        }
    }

    int wa = 0;
    REP(n, N) {
        if (ac_flags[n]) wa += wa_count[n];
    }
    cout << ac << " " << wa << endl;

    return 0;
}
