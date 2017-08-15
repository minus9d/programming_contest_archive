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


ll N, A, B, C;

bool check(ll n, vector<ll>& Hs) {
    ll extra = 0;
    ll base = n * B;

	auto it = upper_bound(ALL(Hs), base);
	while (it != Hs.end()) {
		auto h = *it;
		if (h > base) {
			ll remain = h - base;
			extra += (remain + (C - 1)) / C;
		}
		++it;
	}
    return n >= extra;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> A >> B;
    vector<ll> Hs(N);
    C = A - B;
    ll lo = 0;
    ll hi = 0;
    REP(n, N) {
        cin >> Hs[n];
        hi += Hs[n] / A + 1;
    }
    sort(ALL(Hs));

    while(lo < hi) {
        ll k = (lo + hi) / 2;
        if (check(k, Hs)) {
            hi = k;
        } else {
            lo = k + 1;
        }
    }
    cout << lo << endl;

    return 0;
}
