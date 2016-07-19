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


class BearPasswordLexic {
public:
    string findPassword2(vector <int>& x) {
        int len = SIZE(x);
        vector<int> seqs;

        if (x[0] != len) {
            return "";
        }

        for(int i = SIZE(x)-1; i >= 0; --i) {
            while(x[i] > 0) {
                seqs.pb(len);
                int num2 = 1;
                for(int j = i; j >= 0; --j) {
                    x[j] -= num2;
                    ++num2;
                    if (x[j] < 0) {
                        return "";
                    }
                }
            }
            --len;
        }

        // cout << "seqs:";
        // for(auto e: seqs) cout << e << ",";
        // cout << endl;

        sort(ALL(seqs));
        int i = 0;
        int j = SIZE(seqs) - 1;
        char ch = 'a';
        string result;
        while(i <= j) {
            if (ch == 'a') {
                result += string(seqs[j], ch);
                --j;
                ch = 'b';
            }
            else {
                result += string(seqs[i], ch);
                ++i;
                ch = 'a';
            }
        }

        return result;
    }
    string findPassword(vector <int> x) {
        return findPassword2(x);
    }

  
// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {5,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "ababa"; verify_case(0, Arg1, findPassword(Arg0)); }
	void test_case_1() { int Arr0[] = {4,2,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "aaab"; verify_case(1, Arg1, findPassword(Arg0)); }
	void test_case_2() { int Arr0[] = {3,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(2, Arg1, findPassword(Arg0)); }
	void test_case_3() { int Arr0[] = {4,3,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "aaaa"; verify_case(3, Arg1, findPassword(Arg0)); }
	void test_case_4() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(4, Arg1, findPassword(Arg0)); }
	void test_case_5() { int Arr0[] = {4,0,3,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(5, Arg1, findPassword(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  BearPasswordLexic ___test;
  ___test.run_test(-1);
}
// END CUT HERE

