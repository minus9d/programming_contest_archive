// neal_wu氏のDPを使わない解解法。
// 自分なりに読み込んでコメントを加えた

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

#include <algorithm>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <map>
#include <random>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
 
struct CentipedeSocks {
    int fewestSocks(int C, int F, vector<int> sockCounts) {
 
        // 解なしの判定
        int count = 0;
        for (int socks : sockCounts)
            count += socks / F;
        if (count < C)
            return -1;

        // countには、F個の靴下のセットを何個作れるかが入っている
 
        vector<int> mods;
        int total = 0;
        for (int socks : sockCounts)
            // Fを取れない場合は端数をすべて使う  以降無視できる
            if (socks < F)
                total += socks;
            else
                mods.push_back(socks % F);

        sort(mods.begin(), mods.end());

        cout << endl;
        cout << "mods:";
        for(auto m: mods) {
            cout << m << " ";
        }
        cout << endl;

        // 例えばF個からなる靴下のセットを17セット作る必要があり (C=17)、
        // count = 17である場合を考える。
        // この場合は端数が最も小さい色の靴下が最後にくるように
        // 靴下を取っていくことになる。
        //
        // 次にcount = 18である場合を考える。
        // この場合は作れる靴下に一個余裕がある。
        // 一個余裕が出た分、F-1個まで靴下を取ることが可能になる

        int replace = count - (C - 1);
        cout << "count: " << count << endl;
        cout << "replace: " << replace << endl;

        for (int i = 0; i < (int) mods.size() && i < replace; i++)
            mods[i] = F - 1;

        cout << endl;
        cout << "mods:";
        for(auto m: mods) {
            cout << m << " ";
        }
        cout << endl;
 
        for (int mod : mods)
            total += mod;
 
        return total + (C - 1) * F + 1;
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
