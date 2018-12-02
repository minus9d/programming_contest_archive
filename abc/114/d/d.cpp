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
	ll N;
	cin >> N;

	vector<int> primes{ 2 };
	map<int, int> factors_map;
	FOR(n, 1, N + 1) {
		int n2 = n;
		for (auto p : primes) {
			while (n2 % p == 0) {
				n2 /= p;
				factors_map[p]++;
			}
		}
		if (n2 != 1) {
			factors_map[n2]++;
			primes.pb(n2);
		}
	}
	//for (auto p : primes) cout << p << ","; cout << endl;
	//for (auto kv : factors_map) cout << kv.first << ": " << kv.second << endl;

	vector<pair<int, int>> factors;
	for (auto kv : factors_map) factors.push_back(kv);

	auto ans = 0;
	// 75
	for (auto kv : factors) {
		auto num = kv.second;
		if (num >= 74) ++ans;
	}
	// 25, 3
	for (auto kv : factors) {
		auto factor = kv.first;
		auto num = kv.second;
		if (num >= 24) {
			for (auto kv2 : factors) {
				auto factor2 = kv2.first;
				auto num2 = kv2.second;
				ans += (factor != factor2) && num2 >= 2;
			}

		}
	}
	// 15, 5
	for (auto kv : factors) {
		auto factor = kv.first;
		auto num = kv.second;
		if (num >= 14) {
			for (auto kv2 : factors) {
				auto factor2 = kv2.first;
				auto num2 = kv2.second;
				ans += (factor != factor2) && num2 >= 4;
			}

		}
	}
	// 3, 5, 5
	REP(i, SIZE(factors)) {
		auto factor1 = factors[i].first;
		auto num1 = factors[i].second;
		REP(j, SIZE(factors) - 1) {
			auto factor2 = factors[j].first;
			auto num2 = factors[j].second;
			FOR(k, j + 1, SIZE(factors)) {
				auto factor3 = factors[k].first;
				auto num3 = factors[k].second;
				if (i == j || i == k) continue;
				if (num1 >= 2 && num2 >= 4 && num3 >= 4) {
					++ans;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
