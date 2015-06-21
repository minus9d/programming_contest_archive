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

class Bitwisdom {
public:
    // 期待値の線形性を利用  参考: pparys
    double expectedActions(vector <int> p) {
        double res = 0.0;
        double pr1 = 1.0;
        // 01または10が連続するパターンが1回増えるたび、actionの回数が1回増える
        FOR(i, 1, SIZE(p))
            res += (p[i-1] * (100 - p[i]) + (100 - p[i-1]) * p[i]) / 10000.0;
        // 1が全部続くパターンを例外的に処理
        REP(i, SIZE(p))
            pr1 *= p[i] / 100.0;
        return res + pr1;
    }

  
// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {100, 100, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.0; verify_case(0, Arg1, expectedActions(Arg0)); }
	void test_case_1() { int Arr0[] = {50, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.75; verify_case(1, Arg1, expectedActions(Arg0)); }
	void test_case_2() { int Arr0[] = {0, 40, 50, 60}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.4; verify_case(2, Arg1, expectedActions(Arg0)); }
	void test_case_3() { int Arr0[] = {37, 63, 23, 94, 12}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.6820475464; verify_case(3, Arg1, expectedActions(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  Bitwisdom ___test;
  ___test.run_test(-1);
}
// END CUT HERE

