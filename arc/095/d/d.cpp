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
    vector<ll> As(N);
    REP(n, N) cin >> As[n];
    sort(ALL(As));

    if (N == 2) {
        cout << As[1] << " " << As[0] << endl;
    }
    else {
        auto n = As[N-1];
        int k = 0;
        auto min_diff = 1e9 + 100;
        for(auto a: As) {
            int diff = 0;
            if (n % 2) {
                auto diff1 = abs(n / 2 - a);
                auto diff2 = abs(n / 2 + 1 - a);
                diff = min(diff1, diff2);
            }
            else {
                diff = abs(n / 2 - a);
            }
            if (diff < min_diff) {
                min_diff = diff;
                k = a;
            }
        }
        cout << n << " " << k << endl;
    }

    

    return 0;
}
