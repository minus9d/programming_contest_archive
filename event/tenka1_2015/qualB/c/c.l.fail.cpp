#include <complex>
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
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(ll i = 0; i < (ll)(n); ++i)
#define FOR(i,a,b) for(ll i = (a); i < (ll)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

ll mod = 1000000007;

// 1 + 2 + .. + n
ll tri(ll n) {
	ll ret = n * (n + 1) / 2;
	return ret % mod;
}

// n + (n-3) + (n-6) + ...
ll tillend(ll n) {
	ll itemnum = n / 3LL + 1LL;
	ll ini = n - n / 3 * 3;
	ll sum = (ini + n) * itemnum / 2;
	return sum % mod;
}

ll toTop(ll L) {
	ll to = (L - 1) / 4LL;
	ll sum1 = 0LL;
	if (to >= 2) {
		sum1 = tri(to - 1);
	}

	ll start = to + 1;
	ll sum2 = tillend(L - 3 * start - 2);

	return (sum1 + sum2) % mod;
}


ll large(ll L)
{
	//(i)
	ll v1 = toTop(L);
	return v1;
}

ll small(ll L)
{
	// a < b < c

	// small

	//(i) b = a + 1
	// a: [1, inf]
	// b: a+1
	// c: [a+2, min(L-2a-1, 2a)]
	ll v1 = 0;
	FOR(a, 1, L / 3 + 3) {
		ll b = a + 1;
		ll c_min = b + 1;
		ll c_max = min(L - a - b, a + b - 1);
		// printf("%lld,%lld,[%lld,%lld]\n", a, b, c_min, c_max);
		v1 += max(0LL, c_max - c_min + 1);
	}
	v1 = toTop(L);

	// (ii) c = b + 1
	ll v2 = 0;
	FOR(c, 4, L + 1) {
		ll b = c - 1;
		ll a_min = max(1LL, c - b + 1);
		ll a_max = min(L - b - c, b - 1);
		// printf("[%lld,%lld],%lld,%lld\n", a_min,a_max,b,c);
		v2 += max(0LL, a_max - a_min + 1);
	}

	// (iii) b = a + 1 && c = b + 1
	ll v3 = 0;
	FOR(a, 1, L / 3 + 3) {
		ll b = a + 1;
		ll c = a + 2;
		if (a + b + c <= L && a + b > c) {
			++v3;
		}
	}

	//cout << v1 << "," << v2 << "," << v3 << endl;

	return (v1 + v2 - v3);
}

ll bf(ll L) {
	ll ret = 0;
	FOR(a, 1, L) {
		FOR(b, a + 1, L) {
			FOR(c, b + 1, L) {
				if (
					(b == a + 1 || c == b + 1)
					&& a + b > c
					&& a + b + c <= L
					&& a > 0 && b > 0 && c > 0
					&& c > b
					)
				{
					cout << "ok:" << a << "," << b << "," << c << endl;
					++ret;
					if (a + b + c > L) break;
				}

			}
		}
	}
	return ret;
}

int main(void)
{
	cin.sync_with_stdio(false);
	ll L = 0;
	cin >> L;


	//  FOR(n, 15, 1000) {
	//      ll ret1 = small(n);
	//cout << endl;
	//      ll ret2 = bf(n);
	//      if (ret1 != ret2) {
	//          cout << "diff! n = " << n << endl;
	//          cout << "ret1, bf = " << ret1 << "," << ret2 << endl;
	//          break;
	//      }
	//  }

	ll ret = small(L);
	cout << ret % mod << endl;

	return 0;
}


