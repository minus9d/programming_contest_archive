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


class AlmostFibonacciKnapsack {
public:
  vector <int> getIndices(long long x) {
      auto save = x;

      vector<ll> fib;
      fib.pb(2);
      fib.pb(3);
      FOR(i,2,1000000) {
          if (fib[i-2] > ll(1e18) - fib[i-1] + 1) break;
          fib.pb(fib[i-2] + fib[i-1] - 1);
      }

      // cout << "--------" << endl;
      // for(auto v: fib) cout << v << ",";
      
      vector<ll> used;
      while(x > 32LL) {
          // cout << "x: " << x << endl;
          auto idx = upper_bound(ALL(fib), x);
          auto n = *(--idx);

          // cout << "n:" <<  n << endl;
          if (x == n+1) {
              --idx;
              n = *idx;
          }

          used.pb(n);
          x -= n;
      }

      // use only 2,3,4,6,9,14
      map<ll,set<ll>> table;
      REP(i, 1<<6) {
          ll t = 0;
          set<ll> e;
          if (i == 0) continue;
          REP(j, 6) {
              if ((1 << j) & i) {
                  t += fib[j];
                  e.insert(fib[j]);
              }
          }
          table[t] = e;
      }
      // for(auto e: table) cout << e.first << ",";
      // cout << endl;

      for(auto e: table[x]) {
          used.pb(e);
      }
      
      // for(auto e: used) cout << e << ",";
      // cout << endl;


      vector <int> result;
      for(auto e: used) {
          auto idx = (int)(lower_bound(ALL(fib), e) - fib.begin());
          result.pb(idx+1);
      }

      ll sum = 0;
      for(auto e: result) {
          sum += fib[e-1];
      }
      if(sum != save) {
          cout << save << ": fail!!!!" << endl;
          cout << "indexes:" << endl;
          for(auto e : result) cout << e << ",";
          cout << endl;
          exit(0);
      }

      return result;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { long long Arg0 = 148LL; int Arr1[] = {6, 10, 8, 5 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getIndices(Arg0)); }
	void test_case_1() { long long Arg0 = 2LL; int Arr1[] = {1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getIndices(Arg0)); }
	void test_case_2() { long long Arg0 = 13LL; int Arr1[] = {2, 3, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getIndices(Arg0)); }
	void test_case_3() { long long Arg0 = 3LL; int Arr1[] = {2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getIndices(Arg0)); }
	void test_case_4() { long long Arg0 = 86267769395LL; int Arr1[] = {3, 14, 15, 9, 26, 53, 5, 8 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, getIndices(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  AlmostFibonacciKnapsack ___test;
  ___test.run_test(-1);
}
// END CUT HERE

