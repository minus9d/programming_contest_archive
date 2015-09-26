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
#include <cassert>

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


// 条件に合う最小の移動量kを二分探索で求める。
// このコードでは0-originで統一しているのに注意。

// この関数では移動量kで条件を満たすかどうかを判定する。
// 判定方法：
//   左の方のマス目から順番にカバーしていくことを考える。
//   もっとも左の乗務員から順番に見ていく。
//   この乗務員が到達すべきもっとも左のマス目番号をnextとする。初めは0。
//   この乗務員は、nextまで到達する条件を満たしたうえで、できるだけ右のマス目まで足を踏み入れたい。
//   可能性は2通り：先に左に行くか、先に右に行くか。
//   このうち、もっとも右のマス目まで到達できる方を採用。
//   nextを、この乗務員が到達したもっとも右のマス目の一つ右のマス目とする。
//   以下繰り返し
bool Check(ll k, vector<ll>& Xs, ll N)
{
	ll next = 0; // 今着目している乗務員が到達すべきマス目
	for (auto x : Xs) {
		if (next < x) {
			// nextに到達不可
			if (x - next > k) return false;

			// 先に左に行ったあと、右に行く
			ll next1 = x + 1 + max(0LL, k - 2 * (x - next));

			// 先に右に行った後、右に行く
			ll next2 = x + (k - (x - next)) / 2 + 1;

			next = max(next1, next2);
		}
		else {
			next = max(next, x + k + 1);
		}
	}

	return (next >= N);

}

ll solve(ll N, ll M, vector<ll>& Xs)
{
	// bisect
	ll lo = 0;
	ll hi = 1e10;
	while (lo < hi) {
		auto k = (lo + hi) / 2;
		if (Check(k, Xs, N))
			hi = k;
		else
			lo = k + 1;
	}
	return lo;
}


int main(void)
{
	cin.sync_with_stdio(false);
	ll N, M;
	cin >> N >> M;
	vector<ll> Xs(M);
	REP(m, M) {
		ll tmp;
		cin >> tmp;
		Xs[m] = tmp - 1;
	}

	auto ans = solve(N, M, Xs);
	cout << ans << endl;

	return 0;
}
