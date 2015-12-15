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


class DevuAndPlantingTrees {
public:
    int maximumTreesDevuCanGrow(vector <string> garden) {
        int col = garden[0].size();

        vector<int> filled(col);
        REP(i,col) {


            char tree = '*';
            char empty = '.';

            int num = 0;
            REP(k,2) {
                if (garden[k][i] == empty) {
                }
                else if (garden[k][i] == tree) {
                    ++num;
                }
            }

            filled[i] = num;

            // fail.. why?
            // if (garden[0][col] == tree || garden[1][col] == tree) {
            //     filled[i] = 1;
            // }
        }

        // REP(i,col) {
        //     cout << filled[i] << ",";
        // }
        // cout << endl;

        if (col == 1){
            return 1;
        }
        
        int ret = 0;
        REP(i,col) {
            if (filled[i]){
                ++ret;
            }
            else {
                if (i == 0) {
                    if (!filled[i+1]) {
                        ++ret;
                        filled[i] = 1;
                    }
                }
                else if (i == col-1) {
                    if (!filled[i-1]) {
                        ++ret;
                        filled[i] = 1;
                    }
                }
                else {
                    if (!filled[i-1] && !filled[i+1]) {
                        ++ret;
                        filled[i] = 1;
                    }
                }
            }
        }

        return ret;
    }

  
// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"..", ".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, maximumTreesDevuCanGrow(Arg0)); }
	void test_case_1() { string Arr0[] = {"..", ".*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, maximumTreesDevuCanGrow(Arg0)); }
	void test_case_2() { string Arr0[] = {"...",
                                          "..*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, maximumTreesDevuCanGrow(Arg0)); }
	void test_case_3() { string Arr0[] = {".....*..........",
                                          ".*.......*.*..*."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(3, Arg1, maximumTreesDevuCanGrow(Arg0)); }
	void test_case_4() { string Arr0[] = {"....*.*.*...........*........",
                                          "*..........*..*.*.*....*...*."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(4, Arg1, maximumTreesDevuCanGrow(Arg0)); }
	void test_case_5() { string Arr0[] = {".....*..*..........*............................*",
                                          "*..*.............*...*.*.*.*..*.....*.*...*...*.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 23; verify_case(5, Arg1, maximumTreesDevuCanGrow(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  DevuAndPlantingTrees ___test;
  ___test.run_test(-1);
}
// END CUT HERE
