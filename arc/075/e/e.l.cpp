// �������̒ʂ�Ɏ���
// �����10 20 30 40 30 20 10, ���ϒl��26�Ƃ���
// �܂��A����̊e�l���畽�ϒl�������@-16 -6 4 14 4 -6 -16 �i����A�Ƃ����j�@����ɂ���̈������ȒP�ɂȂ�
// �ݐϘa�̔z����쐬����@0 -16 -22 -18 -4 0 -6 -22 (����B�Ƃ���)�@������0�Ȃ̂ɒ���
// �ݐϘa�̔z��ɂ� i<j�Ƃ��� b_j����b_i�������ƁA����A�ɂ�����a_(i+1)����b_j�܂ł̗ݐϘa�ɂȂ��Ă���
// b_j >= b_i �ł���悤�� i, j�̃y�A�̐����A���߂�͈͂̐��ɂȂ�B
// ����B�ɍ��W���k���s���A5 2 0 1 4 5 3 0  (����C�Ƃ���)
// BIT�Ȃǂ�p���āAc_j >= c_i�ł���悤�ȃy�A�̐������߂�

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

// 1 origin�Ȃ̂Œ���!!
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

	// �ݐϘa���Ƃ�@������0�Ȃ̂ɒ���
    vector<ll> Bs(N+1);
    REP(n, N) {
	    Bs[n+1] = Bs[n] + As[n];
    }

	// ���W���k�̂��߂̃e�[�u���쐬
	set<ll> nums;
	for (auto b : Bs) nums.insert(b);
	map<ll, int> table;
	int idx = 0;
	for (auto n : nums) {
		table[n] = idx;
		++idx;
	}

	// ���W���k
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
