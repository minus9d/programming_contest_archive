// 解説の通りに実装
// 黒マスを頂点、黒マス同士が隣り合う辺をエッジとすると、森となる
// それぞれの部分矩形にて、頂点の数からエッジの数を引いたものが、求める連結成分の数となる
// 頂点の数、エッジの数は、事前に２次元累積和で計算しておく

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

vector<int> table;

int integral(vector<vector<int>>& Vs, int h1, int w1, int h2, int w2) {
	//cout << "debug:" << endl;
	//cout <<   Vs[h2][w2] << endl;
	//cout <<   Vs[h1 - 1][w2] << endl;
	//cout <<   Vs[h2][w1 - 1] << endl;
	//cout <<   Vs[h1 - 1][w1 - 1] << endl;
	return Vs[h2][w2] - Vs[h1 - 1][w2] - Vs[h2][w1 - 1] + Vs[h1 - 1][w1 - 1];
}
void debug_print(vector<vector<int>>& a) {
	int H = SIZE(a);
	int W = SIZE(a[0]);
	REP(h, H) {
		REP(w, W) cout << a[h][w] << " ";
		cout << endl;
	}
	cout << endl;
}

int main(void)
{
	cin.sync_with_stdio(false);
	int N, M, Q;
	cin >> N >> M >> Q;
	vector<string> cells(N);
	REP(n, N) cin >> cells[n];

	// 黒マスの数、上下に連結する黒マスの数、左右に連結する黒マスの数を2次元累積和で
	vector<vector<int>> Vs(N + 1, vector<int>(M + 1));
	vector<vector<int>> ver(N + 1, vector<int>(M + 1));
	vector<vector<int>> hor(N + 1, vector<int>(M + 1));

	// まず各セルの値をカウントした後、横に累積をとり、縦に累積をとる
	REP(n, N) {
		REP(m, M) {
			Vs[n + 1][m + 1] = (cells[n][m] == '1');
			if (m > 0) {
				hor[n + 1][m] = (cells[n][m] == '1' && cells[n][m - 1] == '1');
			}
			if (n > 0) {
				ver[n][m + 1] = (cells[n][m] == '1' && cells[n - 1][m] == '1');
			}
		}
	}

	REP(n, N) {
		REP(m, M) {
			Vs[n + 1][m + 1] += Vs[n + 1][m];
			hor[n + 1][m + 1] += hor[n + 1][m];
			ver[n + 1][m + 1] += ver[n + 1][m];
		}
	}
	REP(m, M) {
		REP(n, N) {
			Vs[n + 1][m + 1] += Vs[n][m + 1];
			hor[n + 1][m + 1] += hor[n][m + 1];
			ver[n + 1][m + 1] += ver[n][m + 1];
		}
	}

	//cout << "Vs" << endl;
	//debug_print(Vs);
	//cout << "hors" << endl;
	//debug_print(hor);
	//cout << "vers" << endl;
	//debug_print(ver);

	REP(q, Q) {
		int h1, w1, h2, w2;
		cin >> h1 >> w1 >> h2 >> w2;

		auto v_num = integral(Vs, h1, w1, h2, w2);
		auto edge1_num = integral(hor, h1, w1, h2, w2 - 1);
		auto edge2_num = integral(ver, h1, w1, h2 - 1, w2);
		cout << (v_num - edge1_num - edge2_num) << endl;
	}

	return 0;
}
