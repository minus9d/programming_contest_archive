// 本番では怪しいbitDPを実装、バグがある可能性が高いが通った
// 実際は解説 https://www.topcoder.com/2020-tco-algorithm-round-1b-editorials/
// にある通り、配列の長さだけで勝敗が決まる！

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
 
const int WIN = 1;
const int LOSE = 2;
const int DRAW = 3;
 
class EllysCandies {
    public:
 
    vector<int> cache;
 
    int dfs(vector<int>& boxes, int bitdp, int first, int second, int offset) {
 
        if (cache[bitdp] != -1) return cache[bitdp];
 
        //cout << bitdp << ", " << first << ", " << second << endl;
        int N = SIZE(boxes);
 
        int used = 0;
        REP(i, N) {
            if (bitdp & (1 << i)) used++;
        }
 
        // base
        if (used == N - 1) {
            REP(i, N) {
                if (bitdp & (1 << i)) {
                    continue;
                }
 
                int val = boxes[i];
                first += val + offset;
 
                int ans;
                if (first > second)
                    ans = WIN;
                else if (first < second)
                    ans = LOSE;
                else
                    ans = DRAW;
 
                return cache[bitdp] = ans;
            }
        }
 
        bool can_draw = false;
        REP(i, N) {
            if (bitdp & (1 << i)) {
                continue;
            }
 
            int val = boxes[i];
            int next_bitdp = bitdp;
            next_bitdp |= (1 << i);
            auto ret = dfs(boxes, next_bitdp, second, first + val + offset, val + offset);
            if (ret == LOSE) {
                return cache[bitdp] = WIN;
            } else if (ret == DRAW) {
                can_draw = true;
            }
        }
 
        if (can_draw) 
            return cache[bitdp] = DRAW;
        else 
            return cache[bitdp] = LOSE;
           
    }
 
    string getWinner(vector<int> boxes) {
        cache.resize((1 << 20), -1);
 
        auto ret = dfs(boxes, 0, 0, 0, 0);
        if (ret == WIN) {
            return "Elly";
        } else if (ret == LOSE) {
            return "Kris";
        } else {
            return "Draw";
        }
 
        return "";
    }
};

// CUT begin
ifstream data2("EllysCandies.sample");

string next_line() {
    string s;
    getline(data2, s);
    return s;
}

template <typename T> void from_stream(T& t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string& s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T>& ts) {
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

bool do_test(vector<int> boxes, string __expected) {
    time_t startClock = clock();
    EllysCandies* instance = new EllysCandies();
    string __result = instance->getWinner(boxes);
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

int run_test(bool mainProcess, const set<int>& case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<int> boxes;
        from_stream(boxes);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if (do_test(boxes, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1588071904;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-") {
            mainProcess = false;
        }
        else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "EllysCandies (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
