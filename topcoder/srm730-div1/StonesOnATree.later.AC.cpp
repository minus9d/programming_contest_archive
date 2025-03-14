// 本番ではcacheを設けていなかったせいでTLE...
// 考え方自体は合っていた

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

class StonesOnATree {
    public:

    vector<int> cache;
    int dfs(vector<int>& p, vector<int>& w, vector<vector<int>>& cs, int v) {
        if (cache[v] != -1) return cache[v];

        if (SIZE(cs[v]) == 0) return cache[v] = w[v];
        else if (SIZE(cs[v]) == 1) {
            auto c1 = cs[v][0];
            return cache[v] = max(dfs(p, w, cs, c1), w[v] + w[c1]);
        }
        else {
            auto c1 = cs[v][0];
            auto c2 = cs[v][1];
            // fprintf(stderr, "%d's children: %d, %d\n", v, c1, c2);
            auto ans1 = max(dfs(p, w, cs, c1), w[c1] + dfs(p, w, cs, c2));
            auto ans2 = max(dfs(p, w, cs, c2), w[c2] + dfs(p, w, cs, c1));
            // fprintf(stderr, "  %d's ans1: %d, ans2: %d\n", v, ans1, ans2);
            auto ans3 = w[v] + w[c1] + w[c2];
            return cache[v] = max(min(ans1, ans2), ans3);
        }
    }

    int minStones(vector<int> p, vector<int> w) {
        auto V = SIZE(w);
        cache.resize(V, -1);
        vector<vector<int>> cs(V);
        REP(i, SIZE(p)) {
            cs[p[i]].pb(i+1);
        }

        // cerr << endl;
        // REP(i, V) {
        //     cerr << "i " << i << ": " << dfs(p,w,cs,i) << endl;
        // }

        auto ans = dfs(p, w, cs, 0);
        return ans;
    }
};

// CUT begin
ifstream data("StonesOnATree.sample");

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

bool do_test(vector<int> p, vector<int> w, int __expected) {
    time_t startClock = clock();
    StonesOnATree *instance = new StonesOnATree();
    int __result = instance->minStones(p, w);
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
        vector<int> p;
        from_stream(p);
        vector<int> w;
        from_stream(w);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(p, w, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519128002;
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
        cout << "StonesOnATree (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
