// igor kudryshov氏の実装を参考に実装
// N^2ループを回してシミュレートするだけ!!
// ただし各足場について次の足場がどこになるかの前計算は必要
//
// 本番中は、パスをたどる途中で過去に見つけたパスに合流したり、
// ループを見つけたりしたときの複雑な処理を実装して時間切れ

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


class EllysTeleport {
    public:

    int getMax(int N, int H1, int A, int B, int P, int Q, int M) {
        vector<int> hs;
        hs.pb(H1);
        REP(n, N - 1) {
            ll h = (hs.back() * 1LL * A + B) % M;
            hs.pb(h);
        }
        sort(ALL(hs));  // もとのindexを保つ意味はないのでソートしてよい

        // i番目のplatformにいるときの次のplatformへのtableを前計算
        // -1はどのplatformにもいけないことを意味する
        // 参考にしたコードはこの前計算がないせいでTLEしていた
        vector<int> next_table(N);
        REP(i, N) {
            int next_h = (hs[i] * 1LL * P + Q) % M;

            // 参考にした解答
            // int idx = lower_bound(ALL(hs), next_h + 1) - hs.begin() - 1;
            // 自分の実装で採用した以下でもOK
            int idx = upper_bound(ALL(hs), next_h) - hs.begin() - 1;

            next_table[i] = idx;
        }

        int ans = 0;
        REP(i, N) {
            vector<int> used(N);  // ループ検出用 通ったplatformのindexを1にする
            int j = i;            // 今いるplatformのindexをjとする
            int cnt = 0;
            while (!used[j]) {
                used[j] = 1;
                cnt++;
                ans = max(ans, cnt);

                // 次の足場を調べる
                int idx = next_table[j];
                if (idx < 0 || used[idx]) break;
                j = idx;
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("EllysTeleport.sample");

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

bool do_test(int N, int H1, int A, int B, int P, int Q, int M, int __expected) {
    time_t startClock = clock();
    EllysTeleport *instance = new EllysTeleport();
    int __result = instance->getMax(N, H1, A, B, P, Q, M);
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
        int N;
        from_stream(N);
        int H1;
        from_stream(H1);
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        int P;
        from_stream(P);
        int Q;
        from_stream(Q);
        int M;
        from_stream(M);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, H1, A, B, P, Q, M, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1556708916;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "EllysTeleport (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end

