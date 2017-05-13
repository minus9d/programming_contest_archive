#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
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

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, K;
    cin >> N >> K;
    map<ll, ll> m;
    REP(n, N) {
        ll a, b;
        cin >> a >> b;
        m[a] += b;
    }
    ll cnt = 0;
    for(auto p: m) {
        auto a = p.first;
        auto b = p.second;
        cnt += b;
        if (cnt >= K) {
            cout << a << endl;
            return 0;
        }
    }

    return 0;
}
