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
    vector<pair<int, int>> xys(N);
    REP(n, N) cin >> xys[n].first >> xys[n].second;

    int cnt = 0;
    double dist_sum = 0.0;
    vector<int> shff(N);
    REP(n, N) shff[n] = n;
    do {
        double dist = 0.0;
        FOR(i, 1, N) {
            auto prev = shff[i - 1];
            auto curr = shff[i];
            auto xy1 = xys[prev];
            auto xy2 = xys[curr];
            dist += hypot(xy1.first - xy2.first,
                          xy1.second - xy2.second);
        }
        dist_sum += dist;
        ++cnt;
    }while(next_permutation(ALL(shff)));
    
    printf("%.12f\n", dist_sum / cnt);
    return 0;
}
