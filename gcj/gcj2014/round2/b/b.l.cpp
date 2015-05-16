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


// もっとも大きい数字をどこに移動するか決めて、そのときの左右をそれぞれバブルソートする方法は失敗
// 失敗例：8 10 7 1 9 6 5 3 2 4
// この場合、以下の並び替えが正解
//         1 8 10 9 7 6 5 4 3 2

// 最小要素を、先頭または末尾の近い方に移動させることを繰り返す解法
// AC
ll solve_large(vector<int>& As)
{
	int s = 0;
	int t = SIZE(As) - 1;
	int swap = 0;
	while (s != t) {
		// 最小要素のidxを探す
		auto min_idx = min_element(As.begin() + s, As.begin() + t + 1) - As.begin();

		// 最小要素を先頭に持っていくとき、末尾に持って行く時の移動回数
		auto move_to_head = min_idx - s;
		auto move_to_tail = t - min_idx;
		auto val = As[min_idx];

		//cout << "min val: " << val << endl;
		//cout << "A: ";
		//for (auto e : As) cout << e << ",";
		//cout << endl;

		// 最小要素を先頭まで持っていく方が近い場合
		if (move_to_head < move_to_tail) {
			for (int i = min_idx; i > s; --i) {
				As[i] = As[i - 1];
			}
			As[s] = val;
			swap += move_to_head;
			++s;
		}
		// 最小要素を末尾まで持っていく方が近い場合
		else {
			FOR(i, min_idx, t) {
				As[i] = As[i+1];
			}
			As[t] = val;
			swap += move_to_tail;
			--t;
		}
	}
	return swap;
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        int N;
        cin >> N;
        vector<int> As(N);
        REP(n,N) cin >> As[n];

        auto ret = solve_large(As);
        cout << "Case #" << (test+1) << ": " << ret << endl;
    }

    return 0;
}
