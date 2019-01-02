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


vector<ll> Xs;
ll L, N;

ll go_forward(int from, int to) {
	if (to >= from) {
		return Xs[to] - Xs[from];
	}
	else {
		return Xs[to] + (L - Xs[from]);
	}
}

ll go_backward(int from, int to) {
	if (to <= from) {
		return Xs[from] - Xs[to];
	}
	else {
		return Xs[from] + (L - Xs[to]);
	}
}

int main(void)
{
	cin >> L >> N;
	Xs.resize(N+1);
    Xs[0] = 0;
	REP(n, N) cin >> Xs[n+1];

    //ll best_ans = 0;
    //vector<pair<int, int>> best_Ys;
    //REP(i, (1 << N)) {
    //    // <idx, forward(+1)/backward(-1)>
    //    vector<pair<int,int>> Ys;
    //    int left = 1;
    //    int right = N;
    //    REP(j, N) {
    //        if ((1 << j) & i) {
    //            Ys.pb({ left, 1 });
    //            ++left;
    //        }
    //        else {
    //            Ys.pb({ right, -1 });
    //            --right;
    //        }
    //    }
    //    int pos = 0;
    //    ll ans = 0;
    //    for (auto e : Ys) {
    //        auto idx = e.first;
    //        auto dir = e.second;
    //        if (dir == 1) {
    //            ans += go_forward(pos, idx);
    //        }
    //        else {
    //            ans += go_backward(pos, idx);
    //        }
    //        pos = idx;
    //    }
    //    if (ans > best_ans) {
    //        best_ans = ans;
    //        best_Ys = Ys;
    //    }
    //}
    //cout << "best ans = " << best_ans << endl;



	// [a][b] 左をa個, 右をb個とって左にいる状態
    vector<vector<ll>> dp_l(N+1, vector<ll>(N+1));
	vector<vector<ll>> dp_r(N+1, vector<ll>(N+1));

    //cout << "forward" << endl;
    //FOR(from, 0, N + 1) {
    //    FOR(to, 0, N + 1) {
    //        cout << "from " << from << " to " << to << ": " << go_forward(from, to) << endl;
    //    }
    //}
    //cout << "backward" << endl;
    //FOR(from, 0, N + 1) {
    //    FOR(to, 0, N + 1) {
    //        cout << "from " << from << " to " << to << ": " << go_backward(from, to) << endl;
    //    }
    //}

    for (ll sum = 1; sum < N + 1; ++sum) {
        for(ll a = 0; a < sum; ++a) {
			auto b = (sum - 1) - a;
			//cout << "a, b = " << a <<"," << b << endl;
			// 左をa個、右をb個取った状態
			// さらに左にいく
			auto v1 = dp_l[a][b] + go_forward(a, a+1);
            ll v2 = 0;
            if (b != 0) {
                v2 = dp_r[a][b] + go_forward(N - b + 1, a + 1);
            }
			auto v3 = max(v1, v2);
			dp_l[a+1][b] = max(dp_l[a+1][b], v3);
			//cout << "dp_l[a+1][b] = " << dp_l[a+1][b] << endl;

			// 右に行く
			auto v4 = dp_l[a][b] + go_backward(a, N-(b+1)+1);
            ll v5 = 0;
            if (b != 0) {
                v5 = dp_r[a][b] + go_backward(N - b + 1, N - (b + 1) + 1);
            }
			auto v6 = max(v4, v5);
			dp_r[a][b+1] = max(dp_r[a][b+1], v6);
			//cout << "dp_r[a][b+1] = " << dp_r[a][b+1] << endl;
		}
	}
	ll ans = 0;
	REP(a, N + 1) {
		ans = max(ans, dp_l[a][N-a]);
		ans = max(ans, dp_r[a][N-a]);
	}
	cout << ans << endl;

	return 0;
}
