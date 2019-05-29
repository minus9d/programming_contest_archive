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

vector<int> getPrimesFast(int n){
    vector<int> primes;
    if (n < 10000){
        primes.clear();
        if (n < 2){
            return primes;
        }
        primes.push_back(2);
        if (n == 2){
            return primes;
        }
        primes.push_back(3);
        if (n == 3){
            return primes;
        }
        for(int i = 5; i <= n; i += 2){
            bool isPrime = true;
            for(int p = 0; p < (int)primes.size(); ++p){
                if (i % primes[p] == 0){
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                primes.push_back(i);
            }
        }
        return primes;
    }
    else{
        vector<int> sieve = getPrimesFast(sqrt(n));

        vector<short> isPrime(n+1, 1);
        for(int i = 0; i < (int)sieve.size(); ++i){
            for(int j = sieve[i] * 2; j <= n; j += sieve[i]){
                isPrime[j] = 0;
            }
        }

        for(int i = 2; i <= n; ++i){
            if (isPrime[i]){
                primes.push_back(i);
            }
        }
        return primes;
    }
}

vector<int> to_vec(int val) {
    vector<int> ret;
    REP(i, 5) {
        ret.pb(val % 10);
        val /= 10;
    }
    return ret;
}

vector<int> func2(vector<int>& sums, vector<int>& vec1, vector<int> &vec2) {
    vector<int> empty;
    vector<int> ans(5);
    REP(i, 5) {
        auto remain = sums[i] - vec1[i] - vec2[i];
        if (remain < 0) return empty;
        if (remain >= 10) return empty;
        ans[i] = remain;
    }
    return ans;
}

int to_int(vector<int>& vec) {
    int digit = 1;
    int ans = 0;
    for(auto e: vec) {
        ans += e * digit;
        digit *= 10;
    }
    return ans;
}

class EllysThreePrimes {
    public:
    vector<int> getPrimes(vector<int> sums) {

        auto primes2 = getPrimesFast(99999);

        vector<int> primes;
        set<int> primes_set;
        map<int, set<vector<int>>> xx_to_prime;
        for(auto p: primes2) {
            if (p >= 10000) {
                primes.pb(p);
                primes_set.insert(p);
                auto xx = p % 100;
                xx_to_prime[xx].insert(to_vec(p));
            }
        }
        cout << SIZE(primes) << endl;

        vector<int> xx_list;
        REP(i, 10) {
            for(int j = 1; j < 10; j += 2) {
                xx_list.pb(i * 10 + j);
            }
        }

        auto xx_list_size = SIZE(xx_list);
        REP(i_, xx_list_size) {
            REP(j_, xx_list_size) {
                auto i = xx_list[i_];
                auto j = xx_list[j_];

                auto d1 = sums[0] - (i % 10) - (j % 10);
                auto d2 = sums[1] - (i / 10) - (j / 10);

                if (d1 < 0 || d2 < 0 || d1 >= 10 || d2 >= 10) continue;

                auto k = d2 * 10 + d1;
                if (SIZE(xx_to_prime[k]) == 0) continue;

                for(auto p1: xx_to_prime[i]) {
                    for(auto p2: xx_to_prime[j]) {
                        auto p3 = func2(sums, p1, p2);

                        if (p3.empty()) continue;
                        if (p1 == p3 || p1 == p2 || p2 == p3) continue;

                        // cout << "p1: "; for(auto e: p1) cout << e << " "; cout << endl;
                        // cout << "p2: "; for(auto e: p2) cout << e << " "; cout << endl;
                        // cout << "p3: "; for(auto e: p3) cout << e << " "; cout << endl;

                        if (xx_to_prime[k].count(p3)) {
                            return vector<int>{to_int(p1),
                                    to_int(p2),
                                    to_int(p3)};
                        }
                    }
                }
            }
        }

        return vector<int>();
    }
};

// CUT begin
ifstream data("EllysThreePrimes.sample");

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

bool do_test(vector<int> sums, vector<int> __expected) {
    time_t startClock = clock();
    EllysThreePrimes *instance = new EllysThreePrimes();
    vector<int> __result = instance->getPrimes(sums);
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
        vector<int> sums;
        from_stream(sums);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(sums, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1559127609;
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
        cout << "EllysThreePrimes (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
