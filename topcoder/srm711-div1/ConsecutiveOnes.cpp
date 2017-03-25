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


class ConsecutiveOnes {
public:
    string to_str(ll n) {
        if (n == 0) return "0";

        string ret;
        while (n) {
            if (n % 2) ret += '1';
            else ret += '0';
            n /= 2;
        }
        reverse(ALL(ret));
        return ret;
    }
    bool ok(string str, int k) {
        int seq = 0;
        for (auto ch : str) {
            if (ch == '1') {
                ++seq;
                if (seq == k) return true;
            }
            else {
                seq = 0;
            }
        }
        return false;
    }

    ll bf(ll n, int k) {
        while (true) {
            auto n_str = to_str(n);
            // cout << "n, str:" << n << "," << n_str << endl;
            if (ok(n_str, k)) return n;
            else ++n;
        }
    }

    ll to_num(string str) {
        ll ret = 0;
        ll cur = 1;
        reverse(ALL(str));
        for (auto ch : str) {
            if (ch == '1') ret += cur;
            cur *= 2;
        }
        return ret;
    }

    ll solve(ll n, int k) {
        auto n_str = to_str(n);
        auto n_str_orig = n_str;
        reverse(ALL(n_str));
        REP(i, k) {
            if (i < SIZE(n_str)) {
                n_str[i] = '1';
            }
            else {
                n_str += '1';
            }
        }
        reverse(ALL(n_str));

        int cnt = 0;
        bool found = false;
        bool changed = false;
        REP(i, SIZE(n_str)) {
            auto& ch = n_str[i];
            auto idx2 = SIZE(n_str) - 1 - i;
            auto idx3 = SIZE(n_str_orig) - 1 - idx2;
            if (found && changed) {
                ch = '0';
            }
            else if (found && n_str_orig[idx3] == '0') {
                ch = '0';
            }
            else {
                if (ch == '1') {
                    cnt += 1;
                    if (cnt == k) found = true;
                    if (idx3 < SIZE(n_str_orig)) {
                        if (0 <= idx3) {
                            if (n_str_orig[idx3] == '0') {
                                changed = true;
                            }
                        }
                    }
                }
                else {
                    cnt = 0;
                }
            }
        }
        return to_num(n_str);
    }

    long long get(long long n, int k) {
        auto ans2 = solve(n, k);

        //auto ans1 = bf(n, k);
        //if (ans1 != ans2) {
        //    cout << "error! n, k, bf, solve = " << n << ", " << k << ", " << ans1 << ", " << ans2 << endl;
        //    cout << "bf str:" << to_str(ans1) << endl;
        //    cout << "my str:" << to_str(ans2) << endl;
        //    exit(0);
        //}
        //else {
        //    //cout << "ok" << endl;
        //}

        return ans2;
    }


    // BEGIN CUT HERE
public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { long long Arg0 = 1LL; int Arg1 = 2; long long Arg2 = 3LL; verify_case(0, Arg2, get(Arg0, Arg1)); }
    void test_case_1() { long long Arg0 = 5LL; int Arg1 = 2; long long Arg2 = 6LL; verify_case(1, Arg2, get(Arg0, Arg1)); }
    void test_case_2() { long long Arg0 = 7LL; int Arg1 = 2; long long Arg2 = 7LL; verify_case(2, Arg2, get(Arg0, Arg1)); }
    void test_case_3() { long long Arg0 = 364269800189924LL; int Arg1 = 33; long long Arg2 = 364273356242943LL; verify_case(3, Arg2, get(Arg0, Arg1)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main() {
    ConsecutiveOnes ___test;


    ___test.get(2, 1);

    FOR(n, 0, 10000) {
        FOR(k, 1, 6) {
            ___test.get(n, k);
        }
    }


    ___test.run_test(-1);
}
// END CUT HERE
