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



ll solve(){
	int B, N;
	cin >> B >> N;
	vector<int> Ms(B);
	REP(b, B) {
		cin >> Ms[b];
	}

	ll lo = 0;
	ll hi = (ll)1e15;
	
	while (lo < hi) {
		ll mid = (lo + hi) / 2;
		ll done = 0;
		for (auto M : Ms) {
			done += (mid / (ll)M) + 1;
		}

		if (done >= N)
		{
			hi = mid;
		}
		else {
			lo = mid + 1;
		}

		//cout << "(time, done) = " << mid << ", " << done << endl;
	}

	// 「カット済の客　＋　現在カット中の客　＋　直後にカット開始できる客」
	// の合計がN以上となる最小の時間が"lo"

	// simulation
	int ans = 0;
	REP(i, B) {
		// 「カット済の客　＋　現在カット中の客」の和を引く
		N -= (lo + Ms[i] - 1) / Ms[i];
	}
	// 「直後にカット開始できる」店を順に探していく
	REP(i, B) {
		if (lo % Ms[i] == 0)
		{
			if (N == 1)
			{
				return (i + 1);
				break;
			}
			else {
				--N;
			}
		}
	}

	return -1;
}

int main(void)
{
	int TEST_NUM;
	cin >> TEST_NUM;

	for (int test = 0; test < TEST_NUM; ++test){
		cout << "Case #" << (test + 1) << ": " << solve() << endl;
	}

	return 0;
}
