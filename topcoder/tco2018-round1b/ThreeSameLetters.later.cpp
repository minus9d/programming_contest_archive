// 3連続する文字列を'aaa'に固定して考える
// 'aaa'直後に来る文字列の場合の数はDPで求められる
// あとは、'aaa'の直前・直後に来る文字列の数を全通り試す
//
// 本番では大まかな考え方は合っていたが間に合わなかった
// あとの復習でも、MODの計算のミスがなかなか消せなかった

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

static const int MOD = int(1e9) + 7;

// 'aaa'の後ろに文字列を連結させていくことを考える。
// 'aaa'の後ろにくる文字列をSと呼ぶ
// dp[s][t][u]としたとき
//   s: Sの文字数
//   t: Sの最後の文字 (0 ~ 25)
//   u:  0: Sの最後の文字が1文字続く
//       1: Sの最後の文字が2文字続く
ll dp[30][30][2];

struct ThreeSameLetters {
    ll L;
    ll S;
    int countStrings(int _L, int _S) {
        L = _L, S = _S;
        if (L < 3) return 0;

        cout << endl;
        memset(dp, 0, sizeof(dp));

        FOR(i, 1, 24) {
            // 'aaa' の直後には'a'以外の文字しか来ない
            if (i == 1) {
                FOR(j, 1, S) {
                    dp[i][j][0] = 1;
                }
            }
            else {
                ll sum = 0;
                REP(j, S) {
                    sum += dp[i-1][j][0];
                    sum += dp[i-1][j][1];
                }

                REP(j, S) {
                    // 直前の文字と同じ文字が2文字続く場合
                    dp[i][j][1] = dp[i-1][j][0];
                    // 直前の文字と異なる文字が来る場合
                    dp[i][j][0] = sum - dp[i-1][j][0] - dp[i-1][j][1];
                    dp[i][j][0] %= MOD;
                }
            }
        }

        // 'aaa'の直前にくる文字列の長さをb, 直後にくる文字列の長さをeとする
        int b = 0;
        int e = L - 3;
        ll ans = 0;
        while (e >= 0) {
            ll tmp = 1;
            for (auto len: {b, e}) {
                if (len != 0) {
                    ll num = 0;
                    REP(j, S) {
                        num += dp[len][j][0] + dp[len][j][1];
                        num %= MOD;
                    }
                    tmp *= num;
                    tmp %= MOD;
                }
            }

            ans += tmp;
            ans %= MOD;

            cout << "tmp: " << tmp << endl;

            ++b;
            --e;
        }

        // 'aaa'以外の文字列が来る場合を考慮
        ans *= S;
        ans %= MOD;

        cout << ans << endl;
        return ans;
    }
};


// CUT begin
ifstream data("ThreeSameLetters.sample");

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

bool do_test(int L, int S, int __expected) {
    time_t startClock = clock();
    ThreeSameLetters *instance = new ThreeSameLetters();
    int __result = instance->countStrings(L, S);
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
        int L;
        from_stream(L);
        int S;
        from_stream(S);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(L, S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1525404091;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ThreeSameLetters (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
