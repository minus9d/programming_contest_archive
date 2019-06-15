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
    vector<pair<ll, ll>> XYs(N);
    REP(n, N) cin >> XYs[n].first >> XYs[n].second;

    set<pair<ll, ll>> PQs;
    
    REP(i, N-1) {
        auto xy1 = XYs[i];
        FOR(j, i + 1, N) {
            auto xy2 = XYs[j];
            PQs.insert(mp(xy2.first - xy1.first,
                          xy2.second - xy1.second));
        }
    }

    set<pair<ll, ll>> exist;
    for(auto xy: XYs) {
        exist.insert(xy);
    }

    int max_cnt = 0;
    for(auto pq: PQs) {
        auto p = pq.first;
        auto q = pq.second;

        int cnt = 0;
        for(auto xy: XYs) {
            auto x = xy.first;
            auto y = xy.second;
            
            auto x2 = x + p;
            auto y2 = y + q;
            cnt += (exist.count(mp(x2, y2)));
        }
        max_cnt = max(max_cnt, cnt);
    }

    cout << (N - max_cnt) << endl;

    return 0;
}
