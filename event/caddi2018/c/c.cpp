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

map<ll, int> getFactorsMap(ll N){
    map<ll, int> ret;
    while(!(N % 2)){
        N /= 2;
        ++ret[2];
    }
    for (ll p = 3; p*p <= N; p += 2) {
        while (N % p == 0) {
            N /= p;
            ++ret[p];
        }
    }
    if (N > 1) ++ret[N];
    return ret;
}

ll pow(ll n, ll k) {
    ll ret = 1;
    REP(i, k) ret *= n;
    return ret;
}

int main(void)
{
    ll N, P;
    cin >> N >> P;
    auto m = getFactorsMap(P);

    ll ans = 1;
    for (auto kv: m) {
        auto appear = kv.second / N;
        if (appear > 0) {
            ans *= pow(kv.first, appear);
        }
    }
    cout << ans << endl;
    return 0;
}
