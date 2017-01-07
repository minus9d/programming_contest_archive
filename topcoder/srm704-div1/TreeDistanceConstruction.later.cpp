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


class TreeDistanceConstruction {
public:
    vector <int> construct(vector <int> d) {
        vector <int> result;
        vector<int> fail;
        auto size = SIZE(d);
        auto mx = *max_element(ALL(d));
        auto mn = *min_element(ALL(d));
        map<int,vector<int>> table;
        REP(i, size) {
            table[d[i]].pb(i);
        }

        if (mx == 1) {
            if (size != 2) return fail;
            if (SIZE(table[1]) != 2) return fail;
            return vector<int>{0,1};
        }
        else if (mx % 2 == 0) {
            if (mn != (mx / 2)) return fail;
            if (SIZE(table[mn]) != 1) return fail;
            FOR(i,mn+1,mx+1) {
                if (SIZE(table[i]) < 2) return fail;
            }
            // center to left
            printf("mn,mx = %d,%d\n",mn,mx);
            FOR(i,mn,mx) {
                // printf("%d: %d <-> %d\n", i, table[i][0], table[i+1][0]);
                result.pb(table[i][0]);
                result.pb(table[i+1][0]);
            }
            // center to right
            FOR(i,mn,mx) {
                // printf("%d: %d <-> %d\n", i, table[i][0], table[i+1][1]);
                if (i == mn) {
                    result.pb(table[i][0]);
                }
                else {
                    result.pb(table[i][1]);
                }
                result.pb(table[i+1][1]);
            }
            // others
            FOR(i,mn+1,mx+1) {
                FOR(j,2,SIZE(table[i])) {
                    result.pb(table[i-1][0]);
                    result.pb(table[i][j]);
                }
            }
        }
        else if (mx % 2 == 1) {
            if (mn != ((mx+1) / 2)) return fail;
            if (SIZE(table[mn]) != 2) return fail;
            FOR(i,mn+1,mx+1) {
                if (SIZE(table[i]) < 2) return fail;
            }
            // two centers
            result.pb(table[mn][0]);
            result.pb(table[mn][1]);

            // center to left
            FOR(i,mn,mx) {
                result.pb(table[i][0]);
                result.pb(table[i+1][0]);
            }
            // center to right
            FOR(i,mn,mx) {
                result.pb(table[i][1]);
                result.pb(table[i+1][1]);
            }
            // others
            FOR(i,mn+1,mx+1) {
                FOR(j,2,SIZE(table[i])) {
                    result.pb(table[i-1][0]);
                    result.pb(table[i][j]);
                }
            }
        }

        return result;
    }

  
// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {3,2,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 1, 0, 2, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, construct(Arg0)); }
	void test_case_1() { int Arr0[] = {1,2,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 0, 2, 0, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, construct(Arg0)); }
	void test_case_2() { int Arr0[] = {1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, construct(Arg0)); }
	void test_case_3() { int Arr0[] = {1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, construct(Arg0)); }
	void test_case_4() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, construct(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  TreeDistanceConstruction ___test;


  // auto ans = ___test.construct(vector<int>{2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4});
  auto ans = ___test.construct(vector<int>{3,4,4,4,4,5,5,5,5});

  if (SIZE(ans) == 0) {
      cout << "empty!" << endl;
  }
  REP(i,SIZE(ans)/2) {
      printf("%d <-> %d\n", ans[i*2], ans[i*2+1]);
  }

  // ___test.run_test(-1);


}
// END CUT HERE
