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

int main(void)
{
    int N;
    cin >> N;
    vector<int> As(N);
    REP(n,N) cin >> As[n];

	auto mx = *max_element(ALL(As));

	map<int, pair<int, int>> ranges;


	REP(idx, N) {
		auto a = As[idx];

		if (idx == 0 && a == mx) continue;

		if (ranges.count(a)) {
			ranges[a].second = idx;
		}
		else {
			ranges[a] = mp(idx, idx);
		}
	}




	int prev_range_e = -1;
	int ans = 1;
	for (auto e : ranges) {
		auto a = e.first;
		auto range_s = e.second.first;
		auto range_e = e.second.second;

		if (range_s <= prev_range_e) {
			++ans;
		}
		prev_range_e = range_e;
	}

	cout << ans << endl;

    return 0;
}
