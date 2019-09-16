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

ll solve(int N, vector<int>& S) {
    sort(ALL(S));
    auto used = vector<int>{S.back()};
    auto unused = S;
    S.pop_back();

    int num_of_gen = 1;

    while (SIZE(used) < (1<<N)) {
        vector<int> next_used;
        REP(i, num_of_gen) {
            auto loc = lower_bound(ALL(unused), used[i]);
            if (loc == unused.begin()) return false;
            next_used.pb(used[i]);
            next_used.pb(*(loc - 1));
            unused.erase((loc - 1));
        }
        used = next_used;
        num_of_gen *= 2;
    }
    return true;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> S((1<<N));
    REP(n, (1<<N)) cin >> S[n];

    if (solve(N, S)) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}

