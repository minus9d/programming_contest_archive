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

// int get_min(int n) {
// 	return n - n / 10;
// }
// int get_max(int n) {
// 	return n + n / 10;
// }

bool can_divide(int a, int b) {
	return (a / b * b == a);
}
int get_range_min(int a, int b) {
	if (can_divide(a, b)) return a / b;
	else return a / b + 1;
}
int get_range_max(int a, int b) {
	if (can_divide(a, b)) return a / b;
	else return a / b;
}

int calc_range_min(int pack, int need) {
	return get_range_min(10 * pack, 11 * need);
}
int calc_range_max(int pack, int need) {
	return get_range_max(10 * pack, 9 * need);
}

void solve()
{
    int N, P;
    cin >> N >> P;
    vector<int> Rs(N);
	REP(n, N) {
		cin >> Rs[n];
	}
    vector<vector<int>> Qs(N);
    REP(n, N) {
		vector<int> tmpvec;
        REP(p, P) {
			int tmp;
			cin >> tmp;
			auto mn = calc_range_min(tmp, Rs[n]);
			auto mx = calc_range_max(tmp, Rs[n]);
			if (mn <= mx) tmpvec.pb(tmp);
		}
		sort(ALL(tmpvec));
		Qs[n] = tmpvec;
    }

	for (auto& vec : Qs) {
		if (SIZE(vec) == 0) {
			cout << 0;
			return;
		}
	}


	//// debug
	//REP(n, N) {
	//	cout << "n:" << n << endl;
	//	REP(p, SIZE(Qs[n])) {
	//		auto pack = Qs[n][p];
	//		cout << "  range " << get_range_min(10 * pack, 11 * Rs[n]) << ", " << get_range_max(10 * pack, 9 * Rs[n]) << endl;

	//	}
	//}

	int ans = 0;
	vector<int> cur_poses(N);
	while (1) {
		int next_idx = -1;
		int range_min_min = 1e9;

		int n_min = -1e9;
		int n_max = 1e9;

		int pos_min;

		REP(n, N) {
			auto pos = cur_poses[n];
			auto pack = Qs[n][pos];
			auto range_min = get_range_min(10 * pack, 11 * Rs[n]);
			auto range_max = get_range_max(10 * pack, 9 * Rs[n]);

			if (range_min < range_min_min) {
				range_min_min = range_min;
				next_idx = n;
			}
			n_min = max(n_min, range_min);
			n_max = min(n_max, range_max);
			printf("");
		}

		bool finish = false;
		if (n_min <= n_max && n_min >= 1) {
			++ans;
			REP(n, N) {
				cur_poses[n] += 1;
				if (cur_poses[n] == SIZE(Qs[n])) finish = true;
			}
		}
		else {
			cur_poses[next_idx] += 1;
			if (cur_poses[next_idx] == SIZE(Qs[next_idx])) finish = true;
		}
		if (finish) break;
	}
	cout << ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
