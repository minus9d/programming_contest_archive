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

void solve()
{
    int N, P;
    cin >> N >> P;
    vector<int> Rs(N);
    REP(n, N) cin >> Rs[n];
    vector<vector<int>> Qs(N);
    REP(n, N) {
        Qs[n].resize(P);
        REP(p, P) {
            cin >> Qs[n][p];
        }
    }

	// N must be 2
	if (N == 1) {
		int ans = 0;
		REP(p, P) {
			auto a = Qs[0][p];
			auto na_min = get_range_min(10 * a, 11 * Rs[0]);
			auto na_max = get_range_max(10 * a, 9 * Rs[0]);
			if (na_max >= na_min && na_min >= 0) ans += 1;
		}
		cout << ans;
	}
	if (N == 2) {
		int ans = 0;
		vector<int> shff(P);
		REP(p, P) shff[p] = p;
		do {
			int local_ans = 0;
			REP(p, P) {
				auto a = Qs[0][p];
				auto b = Qs[1][shff[p]];

				auto na_min = get_range_min(10 * a, 11 * Rs[0]);
				auto na_max = get_range_max(10 * a, 9 * Rs[0]);

				auto nb_min = get_range_min(10 * b, 11 * Rs[1]);
				auto nb_max = get_range_max(10 * b, 9 * Rs[1]);

				if (na_max < nb_min) continue;
				if (nb_max < na_min) continue;

                auto mn = max(na_min, nb_min);
                auto mx = min(na_max, nb_max);
                if (mn <= mx && mn >= 1) {
                    local_ans += 1;
                }
			}
			ans = max(ans, local_ans);
		} while (next_permutation(ALL(shff)));
		cout << ans;
	}
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
