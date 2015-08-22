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


// 参考：LayCurse氏のコード
class BalancedSubstrings {
public:
    int countSubstrings(string S) {
		auto N = SIZE(S);
		int res = 0;

		REP(i, N) { // i: 左端？
			int cnt = 0;  // 登場した1の数
			int now = 0;  // 支点より左側のモーメント -  支点より右側のモーメント？
			int j = i;      // 支点？
			FOR(k, i, N) {  // k: 右端？
				if (S[k] == '1') {
					++cnt;
					now += j - k;
				}
				while (now < 0) { // 支点より左側のモーメントが小さい
					++j;     // 支点を一つ右にずらし？
					now += cnt; // 1の位置がすべて左側よりに1個移動
				}
				if (now == 0) { // ちょうどバランスがとれた状態
					printf("found. (i,j,k = %d,%d,%d)\n", i, j, k);
					++res;
				}
			}
		}
		return res;
    }

  
// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "011"; int Arg1 = 4; verify_case(0, Arg1, countSubstrings(Arg0)); }
	void test_case_1() { string Arg0 = "10111"; int Arg1 = 10; verify_case(1, Arg1, countSubstrings(Arg0)); }
	void test_case_2() { string Arg0 = "00000"; int Arg1 = 15; verify_case(2, Arg1, countSubstrings(Arg0)); }
	void test_case_3() { string Arg0 = "0000001000000"; int Arg1 = 91; verify_case(3, Arg1, countSubstrings(Arg0)); }
	void test_case_4() { string Arg0 = "100110001001"; int Arg1 = 49; verify_case(4, Arg1, countSubstrings(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    //BalancedSubstrings BS;
    //BS.countSubstrings("10010000");

  BalancedSubstrings ___test;
  ___test.run_test(-1);
}
// END CUT HERE

