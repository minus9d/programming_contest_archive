// 解説PDFの通り実装
// K個の列を選んで長さを変えるのと、K個の列をなくすのとが同じことにまず気付く必要があった

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
    int N, K;
    cin >> N >> K;
    vector<int> Hs(N);
    REP(n, N) cin >> Hs[n];

    // dp[x][y]
    //   x: もっとも右の項の番号
    //   y: サイズ
    vector<vector<ll>> dp(N + 1, vector<ll>(N + 1));

	REP(x, N) {
		dp[x][1] = Hs[x];
	}

	FOR(y, 2, N + 1) {
		FOR(x, y - 1, N) {
			ll tmp = 1e18;
			//REP(i, x - 1) {
			FOR(i, y - 2, x) {
				auto prev = Hs[i];
				auto curr = Hs[x];
				tmp = min(tmp, dp[i][y - 1] + max(0, curr - prev));
			}
			dp[x][y] = tmp;
		}

		//REP(y1, N + 1) {
		//	cout << "y " << y1 << ": ";
		//	REP(x1, N) {
		//		cout << dp[x1][y1] << " ";
		//	}
		//	cout << endl;
		//}
		//cout << endl;
	}

	// コーナーケース!!
	// N = Kの場合は明らかにゼロ
	if (N == K) {
		cout << 0 << endl;
	}
	else {
		ll ans = 1e18;
		ll y = N - K;
		FOR(x, y - 1, N) {
			ans = min(ans, dp[x][y]);
		}
		cout << ans << endl;
	}

    return 0;
}
