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
#define mt make_tuple

int main(void)
{
	cin.sync_with_stdio(false);
	int N;
	cin >> N;

	vector<int> vs(N);
	vector<int> ds(N);
	vector<int> ps(N);

	REP(n, N) {
		cin >> vs[n] >> ds[n] >> ps[n];
	}


	vector<int> childs;
	set<int> cried;

	REP(idx, N) {
		// already left
		if (ps[idx] < 0) continue;

		childs.push_back(idx);

		// cry
		auto v = vs[idx];
		auto diff = 1;
		while (idx + diff < N && v > 0) {
			if (ps[idx + diff] >= 0) {
				ps[idx + diff] -= v;
				--v;
			}
			++diff;
		}

		//cout << "after cry:" << endl;
		//for(auto e : ps) cout << e << " ";
		//cout << endl;

		FOR(i, idx + 1, N - 1) {
			// leave
			if (ps[i] < 0 && !cried.count(i)) {
				FOR(j, i + 1, N) {
					ps[j] -= ds[i];
				}
				cried.insert(i);
			}
		}

		//cout << "after leave:" << endl;
		//for(auto e : ps) cout << e << " ";
		//cout << endl;
	}

	cout << SIZE(childs) << endl;
	REP(i, SIZE(childs)) {
		auto c = childs[i] + 1;
		if (i == 0) cout << c;
		else cout << " " << c;
	}
	cout << endl;

	return 0;
}
