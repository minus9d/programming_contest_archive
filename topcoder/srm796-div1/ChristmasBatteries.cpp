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

class ChristmasBatteries {
    public:
    int mostFun(int B_, int N_, int X_, int Y_, int Z_, int M_) {
        ll B = B_;
        ll N = N_;
        ll X = X_;
        ll Y = Y_;
        ll Z = Z_;
        ll M = M_;

        vector<vector<ll>> dp(N + 1, vector<ll>(B + 1));

        REP(n_, N) {
            ll n = n_;
            ll battery = n % 5;
            ll fun = (X * n * n + Y * n + Z) % M;
            REP(b, B + 1) {
                dp[n + 1][b] = max(dp[n][b],
                                   dp[n + 1][b]);
                if (b - battery >= 0) {
                    dp[n + 1][b] = max(dp[n + 1][b],
                                       dp[n][b - battery] + fun);
                }
            }                                   
        }

        ll ans = 0;
        REP(b, B + 1) ans = max(ans, dp[N][b]);
        return ans;
    }
};

// CUT begin
ifstream data("ChristmasBatteries.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
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

bool do_test(int B, int N, int X, int Y, int Z, int M, int __expected) {
    time_t startClock = clock();
    ChristmasBatteries *instance = new ChristmasBatteries();
    int __result = instance->mostFun(B, N, X, Y, Z, M);
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
        int B;
        from_stream(B);
        int N;
        from_stream(N);
        int X;
        from_stream(X);
        int Y;
        from_stream(Y);
        int Z;
        from_stream(Z);
        int M;
        from_stream(M);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(B, N, X, Y, Z, M, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1608725101;
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
        cout << "ChristmasBatteries (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
