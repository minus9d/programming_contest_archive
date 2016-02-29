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


#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;


class MoveStones {
public:

	ll solve(vector <ll>& c) {
		ll carry = 0;
		ll ret = 0;
		for (auto v : c){
			ret += abs(carry);

			//if (v == 0) {
			//	ret += abs(carry);
			//}
			//else if (v * carry < 0) {
			//	ret += min(abs(v), abs(carry));
			//}
			//else {
			//	ret += abs(carry);
			//}

			carry = v + carry;
			//cout << "  ret, carry = " << ret << "," <<  carry << endl;
		}
		return ret;
	}

	long long get(vector <int> a, vector <int> b) {

		auto size = a.size();
		auto a_sum = accumulate(ALL(a), 0LL);
		auto b_sum = accumulate(ALL(b), 0LL);

		if (a_sum != b_sum) {
			return -1;
		}


		if (size == 1) return 0;
		if (size == 2) return abs(a[0] - b[0]);
		vector<ll> diff(size);
		REP(i, size) diff[i] = (ll)a[i] - b[i];


		ll best = (ll)1e18;
		REP(offset, size) {
			vector<ll> c(size);
			int cnt = 0;
			FOR(i, offset, size) {
				c[cnt] = diff[i];
				++cnt;
			}
			REP(i, offset) {
				c[cnt] = diff[i];
				++cnt;
			}
			//for (auto v : c) cout << v << ",";
			//cout << endl;

			auto tmp = solve(c);
			//cout << "  tmp: " << tmp << endl;

			best = min(tmp, best);
		}

		return best;

	}


	// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { 12 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 12 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(0, Arg2, get(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = { 10 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 9 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = -1LL; verify_case(1, Arg2, get(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = { 0, 5 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 5, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 5LL; verify_case(2, Arg2, get(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = { 1, 2, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 3, 1, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(3, Arg2, get(Arg0, Arg1)); }
	void test_case_4() {
		int Arr0[] = { 1, 0, 1, 1, 0 }
		; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 3, 0, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 4LL; verify_case(4, Arg2, get(Arg0, Arg1));
	}
	void test_case_5() { int Arr0[] = { 1000000000, 0, 0, 0, 0, 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0, 0, 1000000000, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 3000000000LL; verify_case(5, Arg2, get(Arg0, Arg1)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main() {
	MoveStones ___test;
	___test.run_test(-1);
}
// END CUT HERE

