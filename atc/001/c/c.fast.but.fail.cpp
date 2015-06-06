#include <complex>
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
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric>

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

typedef complex<double> comp_d;
const double PI = acos(-1);

vector<comp_d> dft(const vector<comp_d>& f, int n)
{
	if (n == 1) return f;
	vector<comp_d> f0, f1;
	REP(i, n / 2) {
		f0.pb(f[2 * i + 0]);
		f1.pb(f[2 * i + 1]);
	}

	f0 = dft(f0, n / 2);
	f1 = dft(f1, n / 2);

	auto zeta = comp_d(cos(2 * PI / n), sin(2 * PI / n));
	auto pow_zeta = comp_d(1.0, 0.0);
	auto ret = f;
	REP(i, n) {
		ret[i] = f0[i % (n / 2)] + pow_zeta * f1[i % (n / 2)];
		pow_zeta *= zeta;
	}
	return ret;
}

// http://www.dsprelated.com/showthread/comp.dsp/25408-1.php
vector<comp_d> inverse_dft(vector<comp_d>& f, int n)
{
	auto conjed = f;
	for (auto& e : conjed) e = conj(e);
	auto ffted = dft(conjed, n);

	vector<comp_d> ret;
	for (auto& e : ffted) {
		ret.pb(conj(e) / (double)n);
	}
	return ret;
}


int pow_2_at_least(int n) {
	int ret = 1;
	while (true) {
		if (ret >= n) return ret;
		else ret *= 2;
	}
}

vector<comp_d> padding_zero(vector<comp_d>& array, int n)
{
	vector<comp_d> ret{ array };
	REP(i, n - SIZE(array)) ret.pb(0);
	return ret;
}

vector<comp_d> multiply(vector<comp_d>& g, vector<comp_d> h)
{
	auto n = pow_2_at_least(SIZE(g) + SIZE(h) + 1);
	auto g2 = padding_zero(g, n);
	auto h2 = padding_zero(h, n);
	auto gg = dft(g2, n);
	auto hh = dft(h2, n);
	vector<comp_d> ff;
	REP(i, n) ff.pb(gg[i] * hh[i]);
	return inverse_dft(ff, n);
}

int main(void)
{
	cin.sync_with_stdio(false);
	int N;
	cin >> N;
	vector<comp_d> As(N), Bs(N);
	REP(n, N) {
		cin >> As[n] >> Bs[n];
	}

	auto table = multiply(As, Bs);
	cout << 0 << endl;
	REP(i, 2 * N - 1) {
		cout << round(real(table[i])) << endl;
	}

	return 0;
}


