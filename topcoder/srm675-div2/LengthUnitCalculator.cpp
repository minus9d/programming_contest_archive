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


class LengthUnitCalculator {
public:
    struct Entry {
        string from;
        string to;
        int mul;
    };


    double calc(int amount, string fromUnit, string toUnit) {
        map<string, ll> table;
        table["in"] = 1;
        table["ft"] = 12;
        table["yd"] = 12 * 3;
        table["mi"] = 12 * 3 * 1760;

        ll num = (ll)amount * table[fromUnit];
        double ans = (double)num / table[toUnit];
        return ans;
    }

  
// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; string Arg1 = "mi"; string Arg2 = "ft"; double Arg3 = 5280.0; verify_case(0, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; string Arg1 = "ft"; string Arg2 = "mi"; double Arg3 = 1.893939393939394E-4; verify_case(1, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 123; string Arg1 = "ft"; string Arg2 = "yd"; double Arg3 = 41.0; verify_case(2, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 1000; string Arg1 = "mi"; string Arg2 = "in"; double Arg3 = 6.336E7; verify_case(3, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1; string Arg1 = "in"; string Arg2 = "mi"; double Arg3 = 1.5782828282828283E-5; verify_case(4, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 47; string Arg1 = "mi"; string Arg2 = "mi"; double Arg3 = 47.0; verify_case(5, Arg3, calc(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  LengthUnitCalculator ___test;
  ___test.run_test(-1);
}
// END CUT HERE

