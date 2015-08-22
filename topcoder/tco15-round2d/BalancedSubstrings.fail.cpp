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


class BalancedSubstrings {
public:
    
    int findzero(string& s, int i, int l, bool toright){
        int offset = 0;
        int ret = 0;
        while(1) {
            auto idx = i + (l + offset) * (toright ? 1 : -1);
            if (idx < 0 || idx >= SIZE(s)) return ret;
            if (s[idx] == '0') {
                ++ret;
                ++offset;
            }
            else return ret;
        }
    }

	vector<int> lv(string& s, int i){
		vector<int> ret;
		auto idx = i - 1;
		auto offset = 1;
		while (idx >= 0) {
			if (s[idx] == '1') { ret.push_back(offset); }
			++offset;
			--idx;
		}
		return move(ret);
	}

	vector<int> rv(string& s, int i){
		vector<int> ret;
		auto idx = i + 1;
		auto offset = 1;
		auto len = SIZE(s);
		while (idx <= len-1) {
			if (s[idx] == '1') { ret.push_back(offset); }
			++offset;
			++idx;
		}
		return move(ret);
	}



    int func(string& s, int i) {
        int ret = 1;
        int l = 1;
        int r = 1;
        bool cont = true;
		auto len = SIZE(s);


		auto v1 = lv(s, i);
		auto v2 = rv(s, i);


        while(cont) {
            int l_zeronum = findzero(s,i,l,false);
            int r_zeronum = findzero(s,i,r,true);
			ret += (l_zeronum + 1) * (r_zeronum + 1) - 1;

            //printf("zeronum : (%d,%d)\n", l_zeronum, r_zeronum);

			if (l_zeronum == 0 && r_zeronum == 0 && (i - l == -1 || i + r == len)) break;

            l += l_zeronum;
            r += r_zeronum;

			bool cont2 = true;
			while (cont2) {
				// till balance
				if (i - l == -1 || i + r == len) {
					cont2 = false;
					break;
				}

				if (l == r) {
					++ret;
					++l;
					++r;
					continue;
				}


				auto l_weight = l;
				auto r_weight = r;
				while (cont2 && l_weight != r_weight) {
					if (l < r) {
						++l;
						if (i - l == -1) {
							cont2 = false;
							break;
						}
						l_weight += (s[i - l] - '0') * l;
					}
					else {
						++r;
						if (i + r == len) {
							cont2 = false;
							break;
						}
						r_weight += (s[i + r] - '0') * r;
					}
				}

				if (cont2) ++ret;
			}
        }

		return ret;
    }

    int countSubstrings(string s) {

		string s1 = "011";
		assert(func(s1, 0) == 1);
		assert(func(s1, 1) == 2);
		assert(func(s1, 2) == 1);
		string s2 = "10111";
		assert(func(s2, 0) == 2);
		assert(func(s2, 1) == 2);
		assert(func(s2, 2) == 2);
		assert(func(s2, 3) == 3);
		assert(func(s2, 4) == 1);
		string s3 = "00000";
		assert(func(s3, 0) == 5);
		assert(func(s3, 1) == 8);
		assert(func(s3, 2) == 2);
		assert(func(s3, 3) == 3);
		assert(func(s3, 4) == 1);

        int result = 0;
        REP(i,SIZE(s)) result += func(s,i);
        return result;
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

