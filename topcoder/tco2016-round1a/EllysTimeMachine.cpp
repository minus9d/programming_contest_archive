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


class EllysTimeMachine {
public:
    int toi(char ch) {
        return (ch - '0');
    }

    string getTime(string time) {
        int h = toi(time[0])*10 + toi(time[1]);
        int m = toi(time[3])*10 + toi(time[4]);
        int newh = m / 5;
        int newm = h * 5;
        if (newh == 0) newh = 12;
        if (newm == 60) newm = 0;

        string result;
        char ret[30];
        sprintf(ret, "%02d:%02d", newh, newm);
        return string(ret);
    }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "11:20"; string Arg1 = "04:55"; verify_case(0, Arg1, getTime(Arg0)); }
	void test_case_1() { string Arg0 = "02:25"; string Arg1 = "05:10"; verify_case(1, Arg1, getTime(Arg0)); }
	void test_case_2() { string Arg0 = "06:30"; string Arg1 = "06:30"; verify_case(2, Arg1, getTime(Arg0)); }
	void test_case_3() { string Arg0 = "05:55"; string Arg1 = "11:25"; verify_case(3, Arg1, getTime(Arg0)); }
	void test_case_4() { string Arg0 = "03:45"; string Arg1 = "09:15"; verify_case(4, Arg1, getTime(Arg0)); }
	void test_case_5() { string Arg0 = "01:00"; string Arg1 = "12:05"; verify_case(5, Arg1, getTime(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  EllysTimeMachine ___test;
  ___test.run_test(-1);
}
// END CUT HERE

