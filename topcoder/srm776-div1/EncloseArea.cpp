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

class EncloseArea {
    public:
    vector<string> enclose(int A) {
        vector<string> fail;
        if (A % 2 == 1) return fail;

        vector<string> ans;
        string line;
        REP(n, 50) line += '.';
        REP(n, 50) ans.pb(line);
        
        int box_num = A / 2;
        int used = 0;
        int x = 0;
        int y = 0;
        while(box_num > 0) {

            ans[y][x] = '/';
            ans[y][x+1] = '\\';
            ans[y+1][x] = '\\';
            ans[y+1][x+1] = '/';
            if (y == 1) {
                ans[y][x] = '.';
            }
            if (y == 0 && x != 0) {
                ans[y+1][x] = '.';
            }

            ++x;
            if (y == 0) y = 1;
            else y = 0;

            ++used;
            --box_num;
            if (used == 49) break;
        }

        x = 0;
        y = 2;
        while(box_num > 0) {
            ans[y][x] = '/';
            ans[y][x+1] = '\\';
            ans[y+1][x] = '\\';
            ans[y+1][x+1] = '/';

            if (y % 2 == 0) {
                if (x == 0) {
                    ans[y][x+1] = '.';
                }
                else if (x == 48) {
                    ans[y][x] = '.';
                }
                else {
                    ans[y][x+1] = '.';
                    ans[y][x] = '.';
                }
            }
            else {
                ans[y][x+1] = '.';
                ans[y][x] = '.';
            }

            if (y % 2 == 0) {
                if (x == 48) {
                    ++y;
                    x = 1;
                } else {
                    x += 2;
                }
            }
            else {
                if (x == 47) {
                    ++y;
                    x = 0;
                } else {
                    x += 2;
                }
            }

            ++used;
            --box_num;

            if (y == 49) break;
        }

        if (box_num > 0) return fail;

        return ans;
    }
};

// CUT begin
ifstream data("EncloseArea.sample");

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

bool do_test(int A, vector<string> __expected) {
    time_t startClock = clock();
    EncloseArea *instance = new EncloseArea();
    vector<string> __result = instance->enclose(A);
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
        int A;
        from_stream(A);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1579953609;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 350 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main() {
    EncloseArea instance;
    FOR(n, 1, 2410) {
        auto ret = instance.enclose(n);
        cout << "[" << n << "]" << endl;
        for (auto l: ret) {
            cout << l << endl;
        }
        cout << endl;
    }
}

int main2(int argc, char *argv[]) {
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
        cout << "EncloseArea (350 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
