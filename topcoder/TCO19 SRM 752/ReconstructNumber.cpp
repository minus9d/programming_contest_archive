// 本番中にAC
//
// 最初はDFSで実装。
// ><<>><=<=>=>><<>><=<=>=><<<<<<<>>>>>>>>><=<=>=>><<>><=<=>=><<<<<<<>>>>>>>!<<<<<<<<<>>>>>>>>>>
// のように、末尾に構築不可能な記号列がある場合の探索が終わらないバグを発見し、
// "corner" の部分を追加。
// この部分では、'>'や'<'が10回以上続くなど、構築不可能な記号列を
// 発見し、-1を返す。
//
// 先頭には0が来れないことや、"!"がある場合は、
// '>'や'<'が最大でも8回しか続けないことがあるのが厄介。
// 
// 例えば '>'が9回, '<'が9回続く場合は
//  98..21012..89
// という文字列の構築が可能だが
// '>'が9回, '!' が1回, '<'が9回続く場合は
// 文字列構築が不可能。
// このことをcapacityという変数を使ってうまく表した。
//
// この実装を追加してresubmitすることでACできた。
//
// しかし、今にして思うと '<' が 9回続くような場合は
// "corner"の部分で-1を返さないといけないが、そうできておらず、不完全


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

class ReconstructNumber {
    public:


    const string FAIL = "fail";
    string dfs(int idx, string& comparisons, int num) {
        if (idx == SIZE(comparisons)) return "";  // string(1, '0' + num);

        char ch = comparisons[idx];
        if (ch == '<') {
            FOR(next_num, num + 1, 10) {
                string ret = dfs(idx + 1, comparisons, next_num);
                if (ret != FAIL) {
                    return string(1, '0' + next_num) + ret;
                }
            }
            return FAIL;
        }
        else if (ch == '>') {
            REP(next_num, num) {
                string ret = dfs(idx + 1, comparisons, next_num);
                if (ret != FAIL) {
                    return string(1, '0' + next_num) + ret;
                }
            }
            return FAIL;
        }
        else if (ch == '=') {
            auto ret = dfs(idx + 1, comparisons, num);
            if (ret == FAIL) return FAIL;
            else return string(1, '0' + num) + ret;
        }
        else {
            REP(next_num, 10) {
                if (next_num == num) continue;
                string ret = dfs(idx + 1, comparisons, next_num);
                if (ret != FAIL) {
                    return string(1, '0' + next_num) + ret;
                }
            }
            return FAIL;

        }
        
    }
    string smallest(string comparisons) {
        // corner
        int lt = 0;
        int mt = 0;
        int cont = 0;
        bool fail = false;
        int capacity = 8;
        for (auto ch : comparisons) {
            if (ch == '<') {
                ++lt;
                mt = 0;
                cont = lt;
                if (lt > capacity) fail = true;
                if (lt == 1) capacity = 9;
            }
            else if (ch == '>') {
                ++mt;
                cont = mt;
                lt = 0;
                if (mt > capacity) fail = true;
                if (mt == 1) capacity = 9;
            }
            else if (ch == '!') {
                if (lt == capacity || mt == capacity) {
                    capacity = 8;
                }
                else {
                    capacity = 9;
                }
                lt = mt = cont = 0;
            }

         }
        if (fail) return "";

        FOR(num, 1, 10) {
            auto ans = dfs(0, comparisons, num);
            if (ans != FAIL) {
                return string(1, '0' + num) + ans;
            }
        }
        return "";

    }
};

// CUT begin
ifstream data2("ReconstructNumber.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string comparisons, string __expected) {
    time_t startClock = clock();
    ReconstructNumber *instance = new ReconstructNumber();
    string __result = instance->smallest(comparisons);
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
        string comparisons;
        from_stream(comparisons);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(comparisons, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1551873620;
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
        cout << "ReconstructNumber (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
