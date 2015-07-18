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

void div(vector <int>& v, deque<int>& use, deque<int>& eat)
{
    REP(i, SIZE(v)){
        if(i == 0) use.pb(v[i]);
        else{
            if(v[i]==v[i-1]) eat.pb(v[i]);
            else use.pb(v[i]);
        }
    }
}

class YetAnotherCardGame {
public:
    bool is_end(deque<int>& use, deque<int>& eat) {
        return (SIZE(use) + SIZE(eat) == 0);
    }

    void update(deque<int>& use, deque<int>& eat, int exist_min, int& pile, int& ret) {
        if (!use.empty() && use[0] == exist_min) {
            pile = use[0];
            ++ret;
            use.pop_front();
			cout << pile << " is piled." << endl;
        }
        else {
            if (!eat.empty()) {
				cout << eat[0] << " is eaten." << endl;
				eat.pop_front();
			}
			// 余り物がない場合はもっとも小さいものを場に出す
			// ここに誤りがあると思われる
            else {
                pile = use[0];
                ++ret;
                use.pop_front();
				cout << pile << " is piled." << endl;
			}
        }
    }

    void update2(deque<int>& use, deque<int>& eat, int pile) {
        while(1) {
            if (SIZE(use) == 0) break;
            if (use[0] > pile) break;
            eat.pb(use[0]);
            use.pop_front();
        }
    }

    int maxCards(vector <int> p, vector <int> s) {
        sort(ALL(p));
        sort(ALL(s));

        deque <int> p_use;
        deque <int> s_use;
        deque <int> p_eat;
        deque <int> s_eat;

        div(p, p_use, p_eat);
        div(s, s_use, s_eat);

        bool p_turn = true;
        int pile = 0;
        int ret = 0;
        while(1) {
			cout << endl;
			cout << "Turn " << p_turn << endl;
			cout << "p: " << endl;
			for (auto& v : p_use) cout << v << " ";
			cout << "/ ";
			for (auto& v : p_eat) cout << v << " ";
			cout << endl;
			cout << "s: " << endl;
			for (auto& v : s_use) cout << v << " ";
			cout << "/ ";
			for (auto& v : s_eat) cout << v << " ";
			cout << endl;



            if(p_turn) {
                if(is_end(p_use, p_eat)) break;
            }
            else {
                if(is_end(s_use, s_eat)) break;
            }

            int exist_min = 1e5;
            if (!p_use.empty()) exist_min = min(p_use[0], exist_min);
            if (!s_use.empty()) exist_min = min(s_use[0], exist_min);

            if(p_turn) {
                update(p_use, p_eat, exist_min, pile, ret);
            }
            else {
                update(s_use, s_eat, exist_min, pile, ret);
            }

            update2(p_use, p_eat, pile);
            update2(s_use, s_eat, pile);
			p_turn = !p_turn;
        }
        return ret;
    }

  
// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, maxCards(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1, 1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 1, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, maxCards(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1, 4, 6, 7, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 7, 1, 5, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(2, Arg2, maxCards(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {19, 99, 86, 30, 98, 68, 73, 92, 37, 69, 93, 28, 58, 36, 86, 32, 46, 34, 71, 29}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {28, 29, 22, 75, 78, 75, 39, 41, 5, 14, 100, 28, 51, 42, 9, 25, 12, 59, 98, 83}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 28; verify_case(3, Arg2, maxCards(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  YetAnotherCardGame ___test;
  ___test.run_test(-1);
}
// END CUT HERE

