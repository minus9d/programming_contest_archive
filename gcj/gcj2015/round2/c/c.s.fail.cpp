#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>
#include <complex>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

set<string> split(const string &s, char delim = ' ') {
	set<string> elems;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.insert(item);
		}
	}
	return elems;
}

int idx = 0;
map<string, int> seen;

void solve(void)
{
    int N;
    cin >> N;
	cin.ignore();

	vector<set<int>> strs(N);
	REP(n, N) {
		string tmp;
		getline(cin, tmp);
		auto words = split(tmp);
		for (auto w : words) {
			if (seen.count(w)) {
				strs[n].insert(seen[w]);
			}
			else {
				seen[w] = idx;
				strs[n].insert(idx);
				++idx;
			}
		}
	}

	set<int> en;
	set<int> fr;

	en = strs[0];
	fr = strs[1];

	int remain = N - 2;
	int ret = 1e9;
	REP(i, (1 << remain)) {
		auto en_copy = en;
		auto fr_copy = fr;

		REP(j, remain) {
			auto& words = strs[j + 2];
			if ((1 << j) & i) {
				for (auto w : words) {
					en_copy.insert(w);
				}
			}
			else {
				for (auto w : words) {
					fr_copy.insert(w);
				}
			}
		}

		set<int> amb;
		set_intersection(ALL(en_copy), ALL(fr_copy), std::inserter(amb, amb.begin()));
		ret = min(ret, SIZE(amb));
	}
	cout << ret;
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": ";
        solve();
        cout << endl;
    }

    return 0;
}
