// 本番ではWA
// 本番では、Cが3以下のときに数列が作れなくなることを考慮していなかった
// ここで単純に C <= 3 のときを場合分けで処理すると、
// 今度は N = 100, C = K = 1の場合に失敗する
// 正しくは、まず数列を構成し、
// その後、数列が条件を満たすかをチェックするのがよかった

#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

using namespace std;

struct StablePairsDiv1 {
    int N;
    int C;
    int K;
    
    vector<int> findMaxStablePairs(int _n, int _c, int _k) {
        N = _n, C = _c, K = _k;
        vector<pair<int,int>> ans;

        int prev1 = -1;
        int prev2 = -1;
        REP(k, K) {
            if (k == 0) {
                ans.push_back(mp(N-1, N));
                prev1 = N-1;
                prev2 = N;
            }
            else {
                auto new1 = 0;
                auto new2 = 0;
                if (C % 2 == 0) {
                    new1 = prev1 - C / 2;
                    new2 = prev2 - C / 2;
                }
                else {
                    auto diff = abs(prev2 - prev1);
                    if (diff == 1) {
                        new1 = prev1 - C / 2 - 1;
                        new2 = prev2 - C / 2;
                    } else {
                        new1 = prev1 - C / 2;
                        new2 = prev2 - C / 2 - 1;
                    }
                }
                ans.push_back(mp(new1, new2));
                prev1 = new1;
                prev2 = new2;
            }
        }

        reverse(ALL(ans));
        vector<int> ans2;
        for(auto e: ans) {
            ans2.push_back(e.first);
            ans2.push_back(e.second);
            // cout << e.first << " " << e.second << " ";
        }

        // 数列が条件を満たさない場合を排除
        if (ans2[0] < 1) {
            return vector<int>();
        }
        REP(i, SIZE(ans2)-1) {
            if (ans2[i] >= ans2[i+1]) return vector<int>();
        }

        return ans2;
    }
};

// CUT begin
ifstream data("StablePairsDiv1.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(int n, int c, int k, vector<int> __expected) {
    time_t startClock = clock();
    StablePairsDiv1 *instance = new StablePairsDiv1();
    vector<int> __result = instance->findMaxStablePairs(n, c, k);
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
        int n;
        from_stream(n);
        int c;
        from_stream(c);
        int k;
        from_stream(k);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, c, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1525401905;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "StablePairsDiv1 (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
