#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
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

ll pow2(pair<int,int>& a, pair<int,int>& b) {
    ll d1 = a.first - b.first;
    ll d2 = a.second - b.second;
    
    return (ll)d1 * d1 + d2 * d2;
}

double longest_dist(vector<pair<int,int>>& dots)
{
    auto size = SIZE(dots);
    ll mx = 0LL;
    REP(i, size) {
        REP(j, size) {
            ll tmp = pow2(dots[i], dots[j]);
            mx = max(mx, tmp);
        }
    }
    return sqrt(mx);
}



int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    vector<pair<int,int>> A(N);
    vector<pair<int,int>> B(N);
    REP(n, N) {
        cin >> A[n].first >> A[n].second;
    }
    REP(n, N) {
        cin >> B[n].first >> B[n].second;
    }

    auto l1 = longest_dist(A);
    auto l2 = longest_dist(B);
    auto ratio = l2 / l1;

    printf("%.9lf\n", ratio);

    return 0;
}
