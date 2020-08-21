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

class VisitALot {
    public:
    int H;
    int W;
    int NEED;

    bool dfs(int h, int w, vector<vector<int>>& visited, vector<char>& bt, int& cnt) {
        char dirs[4] = {'N', 'S', 'E', 'W'};
        int dw[4] = {0, 0, 1, -1};
        int dh[4] = {-1, 1, 0, 0};

        if (cnt == NEED) return true;

        visited[h][w] = 1;

        REP(d, 4) {
            int h2 = h + dh[d];
            int w2 = w + dw[d];
            if (h2 < 0 || h2 >= H || w2 < 0 || w2 >= W) continue;
            if (visited[h2][w2]) continue;

            visited[h2][w2] = 1;
            bt.pb(dirs[d]);
            cnt++;

            auto res = dfs(h2, w2, visited, bt, cnt);
            if (res) return true;

            visited[h2][w2] = 0;
            bt.pop_back();
            cnt--;
        }
        return false;
    }

    string travel(int _H, int _W, vector<int> obsr, vector<int> obsc) {
        H = _H;
        W = _W;
        NEED = (_H * _W + 1) / 2;
        vector<vector<int>> visited(H, vector<int>(W));
        vector<char> bt;

        REP(i, SIZE(obsr)) {
            int h = obsr[i];
            int w = obsc[i];
            visited[h][w] = 1;
        }
        visited[0][0] = 1;
        int cnt = 1;
        
        dfs(0, 0, visited, bt, cnt);
        string s(ALL(bt));
        return s;
    }
};

// CUT begin
ifstream data("VisitALot.sample");

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

bool do_test(int R, int C, vector<int> obsr, vector<int> obsc, string __expected) {
    time_t startClock = clock();
    VisitALot *instance = new VisitALot();
    string __result = instance->travel(R, C, obsr, obsc);
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
        int R;
        from_stream(R);
        int C;
        from_stream(C);
        vector<int> obsr;
        from_stream(obsr);
        vector<int> obsc;
        from_stream(obsc);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(R, C, obsr, obsc, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1597748704;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "VisitALot (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
