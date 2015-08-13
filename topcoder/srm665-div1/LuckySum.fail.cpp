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
#include <climits>

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

const ll INF = LLONG_MAX;

ll shift(ll num, int idx) {
    ll ret = 1;
    REP(i,idx) {
        ret *= 10;
    }
    return num * ret;
}

ll f(int l1, int l2, string rev) {
    // [carry][flag] = min sum
    vector<vector<ll>> dp(10, vector<ll>(2, INF));
    bool flag = 0;
       
    // init
    REP(d,10) dp[d][flag] = 0;

    REP(i, SIZE(rev)+1) {
        flag = !flag;

        if (i == 0) {
            if (rev[i] == '?') {
                dp[0][flag] = 8;  // 4 + 4
                dp[1][flag] = 11; // 4 + 7
            }
            else {
                if (rev[i] == '8') dp[0][flag] = 8;  // 4 + 4
                else if (rev[i] == '4') dp[1][flag] = 14; // 7 + 7
                else if (rev[i] == '1') dp[1][flag] = 11; // 4 + 7
                else {
                    return INF;
                }
            }
        }
        else if (i == SIZE(rev)) {
            printf ("here! ret = ");
            cout << dp[0][flag] << endl;
            return dp[0][flag];
            // ll ret = INF;
            // if (rev[i] == '?') {
            //     REP(d,10) {
            //         ret = min(ret, dp[d][!flag]);
            //     }
            // }
            // else {
            //     ret = dp[ (int)rev[i] - '0' ][!flag];
            // }
            // if (ret == INF) return -1;
            // else return ret;
        }
        else {
            REP(d,10) {
                if (dp[d][!flag] == INF) continue;

                vector<ll> sum;
                if (i >= min(l1,l2)) sum = vector<ll>{4,7};
                else sum = vector<ll>{8,14,11};

                REP(j,SIZE(sum)) {

                    auto s = sum[j] + d;
                    auto new_carry = s / 10;
                    auto new_digit = s % 10;

                    auto num = dp[d][!flag] + shift(new_digit, i);
                    cout << "num: " << num << endl;

                    if (rev[i] == '?')
                    {
                        dp[new_carry][flag] = min(dp[d][flag], num);
                    }
                    else
                    {
                        char rev_ch = rev[i];
                        if (new_digit == rev_ch - '0') {
                            dp[new_carry][flag] = min(dp[d][flag], num);
                        }
                    }
                }
            }
        }

        cout << "===========" << endl;
        cout << "dp[True]: " << endl;
        REP(d,10) cout << dp[d][1] << " ";
        cout << endl;
        cout << "dp[False]: " << endl;
        REP(d,10) cout << dp[d][0] << " ";
        cout << endl;

    }
}

class LuckySum {
public:
    long long construct(string note) {
        auto rev = note;
        reverse(ALL(note));
        auto len = SIZE(note);

        ll ans = INF;
        FOR(l1, 1, len) {
            FOR(l2, l1, len+1) {
                ll local_ans = f(l1, l2, rev);
                // cerr << "local ans: " << local_ans << endl;
                ans = min(ans, local_ans);
            }
        }
        
        if (ans == INF) {
            return -1;
        }
        else {
            return ans;
        }
    }

  
// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "?"; long long Arg1 = 8LL; verify_case(0, Arg1, construct(Arg0)); }
	void test_case_1() { string Arg0 = "?1"; long long Arg1 = 11LL; verify_case(1, Arg1, construct(Arg0)); }
	void test_case_2() { string Arg0 = "4?8"; long long Arg1 = 448LL; verify_case(2, Arg1, construct(Arg0)); }
	void test_case_3() { string Arg0 = "2??"; long long Arg1 = -1LL; verify_case(3, Arg1, construct(Arg0)); }
	void test_case_4() { string Arg0 = "??????????????"; long long Arg1 = 11888888888888LL; verify_case(4, Arg1, construct(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  LuckySum ___test;
  ___test.run_test(-1);
}
// END CUT HERE
