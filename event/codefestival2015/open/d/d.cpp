#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <numeric>
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
#define mt make_tuple

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> points(N);
    REP(n,N) cin >> points[n];

    int sum = accumulate(ALL(points), 0);

    vector<set<int>> info(N);

    int Q;
    cin >> Q;
    REP(q,Q) {
        int a,b,c;
        cin >> a >> b >> c;
        --b;
        --c;
        if (a == 0) {
            info[b].insert(c);
        }
        else {
            if (info[b].count(c)) {
                printf("%d %d\n", points[c], points[c]);
            }
            else {
                int known = points[b];
                for(auto e: info[b]) {
                    known += points[e];
                }
                int unknown_points = sum - known;
                int unknown_person_num = N - 1 - info[b].size();
                // printf("p, n = %d, %d\n", unknown_points, unknown_person_num);

                int mx = min(100, unknown_points);
                int mn = max(0, unknown_points - (unknown_person_num - 1) * 100);
                printf("%d %d\n", mn, mx);
            }
        }
    }

    return 0;
}
