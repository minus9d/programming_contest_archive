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


class LongMansionDiv1 {
public:
    ll count(int x1, int x2, vector<int>& t) {
        ll ans = 0;
        int mn = min(x1, x2);
        int mx = max(x1, x2);
        FOR(x, mn, mx + 1) {
            ans += (ll)t[x];
        }
        return ans;
    }

    long long minimalTime(vector <int> t, int sX, int sY, int eX, int eY) {
        int ROW = SIZE(t);

        ll result = 1e18;
        if (sY != eY) {
            REP(x, ROW) {
                ll tmp = count(x, sX, t);
                tmp += count(x, eX, t);
                tmp += ll(abs(sY - eY) - 1) * t[x];
                result = min(result, tmp);
                // cout << "x, tmp = " << x << "," << tmp << endl;
            }
        }
        else {
            result = count(sX, eX, t);
        }
        
        return result;
    }

  
// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {5, 3, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 0; int Arg3 = 2; int Arg4 = 2; long long Arg5 = 29LL; verify_case(0, Arg5, minimalTime(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arr0[] = {5, 3, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 0; int Arg4 = 0; long long Arg5 = 15LL; verify_case(1, Arg5, minimalTime(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arr0[] = {137, 200, 184, 243, 252, 113, 162}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 4; int Arg4 = 2; long long Arg5 = 1016LL; verify_case(2, Arg5, minimalTime(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arr0[] = {995, 996, 1000, 997, 999, 1000, 997, 996, 1000, 996, 1000, 997, 999, 996, 1000, 998, 999, 995, 995, 998, 995, 998, 995, 997, 998, 996, 998, 996, 997, 1000, 998, 997, 995, 1000, 996, 997, 1000, 997, 997, 999, 998, 995, 999, 999, 1000, 1000, 998, 997, 995, 999}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 18; int Arg2 = 433156521; int Arg3 = 28; int Arg4 = 138238863; long long Arg5 = 293443080673LL; verify_case(3, Arg5, minimalTime(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; long long Arg5 = 1LL; verify_case(4, Arg5, minimalTime(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  LongMansionDiv1 ___test;
  ___test.run_test(-1);
}
// END CUT HERE
