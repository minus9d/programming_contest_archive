// 解説動画の通りに実装
// 数列を10 20 30 40 30 20 10, 平均値を26とする
// まず、数列の各値から平均値を引く　-16 -6 4 14 4 -6 -16 （数列Aとおく）　これにより後の扱いが簡単になる
// 累積和の配列を作成する　0 -16 -22 -18 -4 0 -6 -22 (数列Bとおく)　初項は0なのに注意
// 累積和の配列にて i<jとして b_jからb_iを引くと、数列Aにおけるa_(i+1)からb_jまでの累積和になっている
// b_j >= b_i であるような i, jのペアの数が、求める範囲の数になる。
// 数列Bに座標圧縮を行い、5 2 0 1 4 5 3 0  (数列Cとおく)
// BITなどを用いて、c_j >= c_iであるようなペアの数を求める

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <list>
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


ll N, K;

// 1 originなので注意!!
class Bit
{
private:
	int m_n;
	vector<int> m_bit;

public:
	void init(int n) {
		m_n = n;
		m_bit.resize(n + 1);
	}

	int sum(int i) {
		int s = 0;
		while (i > 0) {
			s += m_bit[i];
			i -= i & -i;
		}
		return s;
	}

	void add(int i, int x) {
		while (i <= m_n) {
			m_bit[i] += x;
			i += i & -i;
		}
	}
};

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> K;
    vector<ll> As(N);
    REP(n, N) {
        cin >> As[n];
        As[n] -= K;
    }

	// 累積和をとる　初項は0なのに注意
    vector<ll> Bs(N+1);
    REP(n, N) {
	    Bs[n+1] = Bs[n] + As[n];
    }

	// 座標圧縮のためのテーブル作成
	set<ll> nums;
	for (auto b : Bs) nums.insert(b);
	map<ll, int> table;
	int idx = 0;
	for (auto n : nums) {
		table[n] = idx;
		++idx;
	}

	// 座標圧縮
	vector<ll> Cs(N+1);
	REP(i, SIZE(Bs)) {
		Cs[i] = table[Bs[i]];
	}

	// BIT
	Bit bit;
	bit.init(idx+1);
	ll ans = 0;
	for (auto c : Cs) {
		ans += bit.sum(c + 1);
		bit.add(c + 1, 1);
	}

	cout << ans << endl;
    return 0;
}
