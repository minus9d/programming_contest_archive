#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

//string best_move1(vector<char> cs1, vector<char> cs2, string name);
//string best_move2(vector<char> cs1, vector<char> cs2, string name);

bool no_question(string& name){
    return name.find('?') == string::npos;
}


map<string, set<string>> backtrace;

string solve_bf(vector<char>& cs1, vector<char>& cs2, string name, bool cs1_is_oleg) {
	if (no_question(name)) {
		return name;
	}

	string ret = "";
	REP(i, SIZE(cs1)) {
		vector<char> new_cs1;
		REP(j, SIZE(cs1)) {
			if (j != i) new_cs1.pb(cs1[j]);
		}
		REP(j, SIZE(name)) {
			if (name[j] == '?') {
				string new_name = name;
				new_name[j] = cs1[i];

				auto cand = solve_bf(cs2, new_cs1, new_name, !cs1_is_oleg);

				if (ret == "") {
					ret = cand;
				}
				else {
					if (cs1_is_oleg) {
						ret = min(ret, cand);
					}
					else {
						ret = max(ret, cand);
					}
				}
			}
		}
	}
	backtrace[ret].insert(name);
	return ret;

}

string solve_fast(vector<char>& cs1, vector<char>& cs2, string ans) {
    bool player1 = true;

    int s1 = 0;
    int e1 = SIZE(cs1)-1;
    int s2 = 0;
    int e2 = SIZE(cs2)-1;

    int sq = 0;
    int eq = SIZE(ans)-1;

    REP(i, SIZE(ans)) {
		if (player1 && i == SIZE(ans) - 1) {
			ans[eq] = cs1[s1];
		}
        else if (player1) {
            if (cs1[s1] >= cs2[e2]) {
                ans[eq] = cs1[e1];
                --e1;
                --eq;
            }
            else {
                ans[sq] = cs1[s1];
                ++s1;
                ++sq;
            }
        }
        else {
            if (cs1[s1] >= cs2[e2]) {
                ans[eq] = cs2[s2];
                ++s2;
                --eq;
            }
            else {
                ans[sq] = cs2[e2];
                --e2;
                ++sq;
            }
        }
        player1 = !player1;
    }
    return ans;
}

string solve(string s1, string s2) {
    int n2 = SIZE(s1) / 2;
    int n1 = SIZE(s1) - n2;
    string name(SIZE(s1), '?');

    sort(ALL(s1));
    sort(ALL(s2));
	reverse(ALL(s2));
    vector<char> cs1;
    vector<char> cs2;
    REP(i, n1) cs1.pb(s1[i]);
    REP(i, n2) cs2.pb(s2[i]);
	sort(ALL(cs2));

    auto ret_fast = solve_fast(cs1, cs2, name);

	// for debug
	//auto ret = solve_bf(cs1, cs2, name, true);
 //   if (ret != ret_fast) {
	//	cout << "error!" << endl;
	//	cout << "  bf, fast = " << ret << "," << ret_fast << endl;
	//	cout << "  s1, s2 = " << s1 << "," << s2 << endl;
 //   }
	//else {
	//	cout << "ok" << endl;
	//}

	return ret_fast;
}

string make_random(int n) {
	string ret = "";
	REP(i, n) ret += 'a' + rand() % 26;
	return ret;
}

int main(void)
{
	// for debug
	//while (true) {
	//	int n = 6;
	//	if (rand() % 2) n += 1;
	//	auto s1 = make_random(n);
	//	auto s2 = make_random(n);
	//	solve(s1, s2);
	//}


    cin.sync_with_stdio(false);
    string s1, s2;
    cin >> s1 >> s2;
    int N;
    cin >> N;
    cout << solve(s1, s2);

    return 0;
}
