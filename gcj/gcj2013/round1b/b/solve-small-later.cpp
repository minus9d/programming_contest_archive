#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <string>
#include <cmath>
#include <cassert>

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

int number_of_blocks_of_layer(int layer) {
    return layer * 4 - 3;
}

// @retval  <何層目か(1始まり), 該当層で何個目か, この層は頂点含め最大何個か>
tuple<int,int,int> get_layer(int n) {
    int sum = 0;
    int layer = 1;
    while(1) {
        auto add = layer * 4 - 3;
        auto idx = n - sum;
        sum += add;
        if (n <= sum) {
            return make_tuple(layer, idx, add);
        }
        ++layer;
    }
}

int get_layer(int x, int y) {
    return (x + y) / 2 + 1;
}

// あるlayerにて、
// n個のダイアが降った時、右側が「ちょうど」r個埋まっている確率。mxは右側に積もれるmaxの数（頂点除く）
double prob_strict(int n, int r, int mx)
{
	int l = n - r;
	if (l == r && l == mx) return 1.0;
	if (l < r) swap(l, r); // 常にrは小さい方と約束

	// ダイアが多すぎて溢れる場合
	if (n - mx > r) return 0.0;

	if (n == 0) return 0.0;
	if (n == 1) {
		if (r == 0 || r == 1) return 0.5;
		else return 0.0;
	}
	if (l == mx) {
		return prob_strict(n - 1, r - 1, mx) + prob_strict(n - 1, r, mx) * 0.5;
	}
	else {
		return prob_strict(n - 1, r - 1, mx) * 0.5 + prob_strict(n - 1, r, mx) * 0.5;
	}
}

// あるlayerにて、
// n個のダイアが降った時、右側が少なくともr個埋まっている確率。mxは右側に積もれるmaxの数（頂点除く）
double prob(int n, int r, int mx)
{
	double ret = 0.0;
	FOR(i, r, mx + 1) {
		ret += prob_strict(n, i, mx);
	}
	return ret;
}

double solve(void)
{
    int N, X, Y;
    cin >> N >> X >> Y;

    auto info = get_layer(N);
    auto dia_layer = get<0>(info);
    auto dia_num = get<1>(info);
    auto dia_mx = get<2>(info);
    auto interest_layer = get_layer(abs(X), Y);

    if (interest_layer > dia_layer) return 0.0;
    if (interest_layer < dia_layer) return 1.0;

	// 求める点が頂点の場合は再帰なしで求める
	if (Y == (dia_layer - 1) * 2) {
		return dia_num == dia_mx;
	}
	if (dia_mx == dia_num) return 1.0;

    return prob(dia_num, Y+1, (dia_mx - 1) / 2);
}

int main(void)
{
	assert(prob_strict(0, 1, 2) == 0.0);
	assert(prob_strict(0, 2, 2) == 0.0);

	assert(prob_strict(1, 1, 2) == 0.5);
	assert(prob_strict(1, 2, 2) == 0.0);

	assert(prob_strict(2, 1, 2) == 0.5);
	assert(prob_strict(2, 2, 2) == 0.25);

	assert(prob_strict(3, 1, 2) == 0.5);
	assert(prob_strict(3, 2, 2) == 0.5);

	assert(prob_strict(4, 1, 2) == 0.0);
	assert(prob_strict(4, 2, 2) == 1.0);

	assert(prob_strict(0, 1, 3) == 0.0);
	assert(prob_strict(0, 2, 3) == 0.0);
	assert(prob_strict(0, 3, 3) == 0.0);

	assert(prob_strict(1, 1, 3) == 0.5);
	assert(prob_strict(1, 2, 3) == 0.0);
	assert(prob_strict(1, 3, 3) == 0.0);

	assert(prob_strict(2, 1, 3) == 0.5);
	assert(prob_strict(2, 2, 3) == 0.25);
	assert(prob_strict(2, 3, 3) == 0.0);

	assert(prob_strict(3, 1, 3) == 3.0 / 8.0);
	assert(prob_strict(3, 2, 3) == 3.0 / 8.0);
	assert(prob_strict(3, 3, 3) == 0.125);

	assert(prob_strict(4, 1, 3) == 5.0 / 16.0);
	assert(prob_strict(4, 2, 3) == 6.0 / 16.0);
	assert(prob_strict(4, 3, 3) == 5.0 / 16.0);

	assert(prob_strict(5, 1, 3) == 0.0);
	assert(prob_strict(5, 2, 3) == 0.5);
	assert(prob_strict(5, 3, 3) == 0.5);

	assert(prob_strict(1, 1, 3) == 0.5);
	assert(prob_strict(5, 2, 3) == 0.5);
	assert(prob_strict(5, 3, 3) == 0.5);



	assert(prob(1, 1, 2) == 0.5);
	assert(prob(1, 2, 2) == 0.0);

	assert(prob(2, 1, 2) == 0.75);  /// 0.75になるはず???
	assert(prob(2, 2, 2) == 0.25);

	assert(prob(3, 1, 2) == 1.0);
	assert(prob(3, 2, 2) == 0.5);

	assert(prob(4, 1, 2) == 1.0);
	assert(prob(4, 2, 2) == 1.0);


	//assert(prob(1, 1, 3) == 0.5);
	//assert(prob(1, 2, 3) == 0.0);
	//assert(prob(1, 3, 3) == 0.0);

	//assert(prob(2, 1, 3) == 0.75);
	//assert(prob(2, 2, 3) == 0.25);
	//assert(prob(2, 3, 3) == 0.0);
	//
	//assert(prob(3, 1, 3) == 1.0 - 0.125);
	//assert(prob(3, 2, 3) == 0.125 + xxx);
	//assert(prob(3, 3, 3) == 0.125);


	FOR(n, 1, 100) {
        auto ret = get_layer(n);
        //cout << ret.first << ", " << ret.second << endl;
    }
    
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": " << solve() << endl;
    }

    return 0;
}
