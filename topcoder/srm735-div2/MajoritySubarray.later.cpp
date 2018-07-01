// 公式解答を見た
//   https://www.topcoder.com/blog/single-round-match-735-editorials/

// 配列Aの構成要素はせいぜい50なので、各構成要素ごとに考えればよい。
// 次のような配列Aで、'o'が支配的になる部分配列の数を考える
// 
//   oxxooxo
//   0123456 (idx)
//
// 配列Bを以下のように構成する。
//   B[0]=7  (すべての要素が0以上になるよう下駄を履かせる)
//   a[i]が'o'であればb[i+1]=b[i]+1, 'o'以外であればb[i+1]=b[i]-1
// すると配列Bは以下のようになる
//  78767878
//  01234567 (idx)
// b[j] < b[i]となるj < iのペアを探す。このとき aの部分文字列[j, i)は'o'が支配的になっていることがわかる。
// 列挙すると以下のようになる。
// (j, i) = (0, 1), (0, 5), (0, 7),
//          (2, 5), (2, 7),
//          (3, 4), (3, 5), (3, 6), (3, 7),
//          (4, 5), (4, 7),
//          (6, 7)
//
// このようなペアの数は、BITを使うと効率的に求められる。
// たとえば B[5]に注目すると、これより左にある、B[5]より小さい値であるようなidxの数が、BITにより効率的に求められる

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

class MajoritySubarray {
public:
    vector<ll> F;
    int fenwick_sum(int i) { // BITのこと。実装は蟻本と同じ
        int s = 0;
        while (i > 0) {
            s += F[i];
            i -= i & -i;  // i & -i: 1, 2, 4, 8, 16, ...のうち、iを割れる最大の数
                          //         言い換えると、iの一番右に立っているビットに等しい
        }
        return s;
    }
    void fenwick_add(int i, int val) {
        while(i < (1<<18)) {
            F[i] += val;
            i += i & -i;
        }
    }

    long long solve(ll N, ll seed, ll MOD) {
        vector<ll> As(N);
        REP(i, N) {
            As[i] = (seed / 65536) % MOD;
            seed = (seed * 1103515245 + 12345) % 2147483648;
        }

        F.resize(1<<18);
        ll ans = 0;
        REP(x, MOD) {
            fill(ALL(F), 0);
            int bal = N;
            REP(i, N) {
                fenwick_add(bal, 1);
                if (As[i] == x) {
                    ++bal;
                } else {
                    --bal;
                }
                ans += fenwick_sum(bal - 1);
            }
        }
        return ans;
    }

    long long getCount(int n_, int seed_, int m_) {
        ll n = n_;
        ll seed = seed_;
        ll MOD = m_;

        return solve(n, seed, MOD);
    }
};

// CUT begin
ifstream data2("MajoritySubarray.sample");

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

bool do_test(int n, int seed, int m, long long __expected) {
    time_t startClock = clock();
    MajoritySubarray *instance = new MajoritySubarray();
    long long __result = instance->getCount(n, seed, m);
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
        int seed;
        from_stream(seed);
        int m;
        from_stream(m);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, seed, m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1530012384;
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
        cout << "MajoritySubarray (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
