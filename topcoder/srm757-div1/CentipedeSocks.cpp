// 本番中は解ききれず本番後に時間をかけて実装
//
// DP。
// sockCounts色の靴下から、C個を選ぶ問題だとしてDPする。
// ある色の靴下からkセット作ると決めたときは、できるだけ余りが多くなるようにする。
// ただし、最後のセットを作る靴下からはあまりなしでしか靴下をとれないという
// 問題があるので、最後に作る靴下をどれにするか (last_pick) をすべて試す。


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
#include <cstring>
#include <fstream>

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

using namespace std;

class CentipedeSocks {
    public:

    int fewestSocks(int C, int F, vector<int> sockCounts) {
        int mx = 0;
        for(auto s: sockCounts) {
            mx += s / F;
        }
        if (mx < C) return -1;
        //cout << "mx, C = "<< mx << "," << C << endl;

        cout << "C:" << C << endl;
        cout << "F:" << F << endl;
        cout << "sc:" << endl;
        for(auto s: sockCounts) cout << s << "," ;
        cout << endl;


        int ans = 0;
        int color_num = SIZE(sockCounts);

        REP(last_pick, color_num) {

            // [位置][とれた靴下セットの数]
            vector<vector<int>> dp(101, vector<int>(101, -1));

            if (sockCounts[last_pick] < F) continue;

            cout << "=========" << endl;
            cout << "last_pick = " << last_pick << endl;
            cout << "=========" << endl;
            
            REP(i, color_num) {
                cout << "[ i = " << i << " ] " << endl;

                if (last_pick == i) {
                    if (i == 0) {
                        REP(j, min(sockCounts[i] / F + 1, C + 1)) {
                            dp[i][j] = F * j;
                        }
                    } else {
                        REP(j, min(sockCounts[i] / F + 1, C + 1)) {
                            REP(c, C + 1) {
                                if (j > c) continue;
                                if (dp[i - 1][c - j] < 0) continue;

                                cout << "max(" << dp[i][c] << ", "
                                     << dp[i - 1][c - j] + F * j << endl;

                                dp[i][c] = max(dp[i][c],
                                               dp[i - 1][c - j] + F * j);

                                
                            }
                        }
                    }
                }
                else {
                    if (i == 0) {
                        REP(j, min(sockCounts[i] / F + 1, C + 1)) {
                            dp[i][j] = F * j + min(F - 1, sockCounts[i] - F * j);
                        }
                    } else {
                        REP(j, min(sockCounts[i] / F + 1, C + 1)) {
                            REP(c, C + 1) {
                                if (j > c) continue;
                                if (dp[i - 1][c - j] < 0) continue;
                                dp[i][c] = max(dp[i][c],
                                               dp[i - 1][c - j]
                                               + F * j
                                               + min(F - 1, sockCounts[i] - F * j));
                                cout << "add " << dp[i - 1][c - j] << " + "
                                     << F * j << " + "
                                     << min(F - 1, sockCounts[i] - F * j) << endl;
                             
                            }
                        }
                    }
                }

                cout << "====" << endl;
                REP(c, C + 1) {
                    cout << "dp[" << i << "][" << c << "] =" << dp[i][c] << endl;
                }
                cout << "====" << endl;
            }

            //cout << "::-> dp[" << color_num - 1 << "][" << C << "]" << endl;

            cout << "last_pick, ans = " << last_pick << ", " << dp[color_num - 1][C] << endl;
            ans = max(ans, dp[color_num - 1][C]);
        }

        return ans;
    }
};


// CUT begin
ifstream data2("CentipedeSocks.sample");

string next_line() {
    string s;
    getline(data2, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int C, int F, vector<int> sockCounts, int __expected) {
    time_t startClock = clock();
    CentipedeSocks *instance = new CentipedeSocks();
    int __result = instance->fewestSocks(C, F, sockCounts);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        int C;
        from_stream(C);
        int F;
        from_stream(F);
        vector<int> sockCounts;
        from_stream(sockCounts);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(C, F, sockCounts, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1556586000;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "CentipedeSocks (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
