#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

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

ll MOD = 1000000007;

ll solve(vector<ll>& kill, ll deathSum) {
    map<int, int> count;
    for(auto e: kill) ++count[e];
    
    return 0;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, M;
    cin >> N >> M;
    vector<ll> killA(N);
    vector<ll> killB(M);
    REP(n, N) cin >> killA[n];
    REP(m, M) cin >> killB[m];

    ll deathASum = accumulate(ALL(killB), 0LL);
    ll deathBSum = accumulate(ALL(killA), 0LL);

    ll ans1 = solve1(killA, deathASum);
    ll ans2 = solve1(killB, deathBSum);
    lla ans = (ans1 * ans2) % MOD;

    return 0;
}
