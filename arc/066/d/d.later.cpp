// 参考：解説放送
// 以下の3つを満たすペア(a, b)の数をfunc(S, X)とする
//   1. a + b <= S
//   2. a xor b <= X
//   3. aとb, どちらにビットを立ててもいいときは、aに立てる

// この後は典型的なdigit DP
// func(S, X) = func(S/2, X/2) 　　    // a, bともに偶数
//            + func((S-1)/2, (X-1)/2) // aが奇数, bが偶数
//            + func((S-2)/2, X/2)     // a, bともに奇数
// 
// func(N, N)が答

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
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
map<pair<ll,ll>, ll> cache;
ll func(ll S, ll X) {
    if (cache.count(mp(S,X))) return cache[mp(S,X)];
    if (S == 0 && X == 0) return 1;
    if (S == 1 && X == 0) return 1;
    if (S == 0 && X == 1) return 1;
    ll ans = func(S/2, X/2) % MOD;
    if (S >= 1 && X >= 1) {
        ans = (ans + func((S-1)/2, (X-1)/2)) % MOD;
    }
    if (S >= 2) {
        ans = (ans + func((S-2)/2, X/2)) % MOD;
    }
    cache[mp(S,X)] = ans;
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N;
    cin >> N;
    cout << func(N,N) << endl;

    return 0;
}
