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
    vector<pair<int, int>> BAs(M);
    REP(m, M) {
        cin >> BAs[m].second >> BAs[m].first;
    }
    sort(ALL(BAs));

    int prev = -1;
    int ans = 0;
    for(auto ba: BAs) {
        auto b = ba.first;
        auto a = ba.second;
        if (prev == -1) {
            prev = b - 1;
            ++ans;
        }
        else {
            if (prev < a) {
                prev = b - 1;
                ++ans;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
