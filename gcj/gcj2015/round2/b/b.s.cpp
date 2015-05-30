#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>
#include <complex>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

const string imp = "IMPOSSIBLE";

void solve(void)
{
    int N;
    double V, X;
    cin >> N >> V >> X;

    vector<double> Rs(N);
    vector<double> Cs(N);

    REP(n, N) {
        cin >> Rs[n] >> Cs[n];
    }

    if (N == 1) {
        if (Cs[0] != X) {
            cout << imp;
            return;
        }

        double ans = V / Rs[0];
        printf("%.10lf", ans);
    }
    else if (N == 2) {
        // same temp
        if (Cs[0] == Cs[1]) {
            if (Cs[0] != X) {
                cout << imp;
                return;
            }

            double ans = V / (Rs[0] + Rs[1]);
            printf("%.10lf", ans);
        }
        else {
            double v0 = V * (Cs[1] - X) / (Cs[1] - Cs[0]);
            double v1 = V * (X - Cs[0]) / (Cs[1] - Cs[0]);
            if (v0 < 0 || v1 < 0) {
                cout << imp;
                return;
            }
            double ans = max(v0 / Rs[0], v1 / Rs[1]);
            printf("%.10lf", ans);
        }
    }
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": ";
        solve();
        cout << endl;
    }

    return 0;
}
