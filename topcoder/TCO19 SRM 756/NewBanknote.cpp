// 解説を見る
// 新紙幣は多くとも5万回以下しか使われないことが証明できるので
// 新紙幣を使う枚数を変えて全探索

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

class NewBanknote {
    public:
    ll get_base(ll pay, vector<ll>& kinds) {
        ll ans = 0;
        for(auto k: kinds) {
            ans += pay / k;
            pay -= (pay / k) * k;
        }
        return ans;
    }

    ll solve_fast(ll pay, ll newBanknote, vector<ll>& kinds) {
        ll ans = 1e18;
        REP(n, 50001) {
            ll local_ans = n;
            ll remain = pay - (newBanknote * n);
            if (remain < 0) break;
            local_ans += get_base(remain, kinds);
            ans = min(ans, local_ans);
        }
        return ans;
    }

    vector<int> fewestPieces(int newBanknote_, vector<int> amountsToPay) {
        ll newBanknote = newBanknote_;
        vector<ll> kinds = {
            1, 2, 5, 10, 20, 50, 100, 200,
            500, 1000, 2000, 5000, 10000, 20000, 50000};
        reverse(ALL(kinds));

        vector<int> ret;
        for(auto pay_: amountsToPay) {
            ll pay = pay_;
            auto ans = solve_fast(pay, newBanknote, kinds);
            ret.pb(ans);
        }
        return ret;
    }
};

// CUT begin
ifstream data("NewBanknote.sample");

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

bool do_test(int newBanknote, vector<int> amountsToPay, vector<int> __expected) {
    time_t startClock = clock();
    NewBanknote *instance = new NewBanknote();
    vector<int> __result = instance->fewestPieces(newBanknote, amountsToPay);
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
        int newBanknote;
        from_stream(newBanknote);
        vector<int> amountsToPay;
        from_stream(amountsToPay);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(newBanknote, amountsToPay, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1556190005;
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
        cout << "NewBanknote (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
