#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
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

int N;
void fill(vector<char>& fix, vector<int>& mx, vector<int>& Ts) {
    REP(n,N) {
        mx[n] = Ts[n];
        if (n == 0) {
            fix[n] = 1;
        } else {
            if (Ts[n] > Ts[n-1]) {
                fix[n] = 1;
            }
        }
    }
}

ll MOD = 1000000007;

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N;
    vector<int> Ts(N);
    vector<int> As(N);
    REP(n,N) cin >> Ts[n];
    REP(n,N) cin >> As[n];
    
    vector<char> fix_left(N);
    vector<int> mx_left(N);
    fill(fix_left, mx_left, Ts);

    reverse(ALL(As));
    vector<char> fix_right(N);
    vector<int> mx_right(N);
    fill(fix_right, mx_right, As);

    ll ans = 1;
    REP(n,N) {
        auto f1 = fix_left[n];
        auto m1 = mx_left[n];
        auto f2 = fix_right[N-1-n];
        auto m2 = mx_right[N-1-n];
        // printf("f1,m1,f2,m2 = %d,%d,%d,%d\n", f1, m1, f2, m2);

        if (f1 * f2 > 0) {
            if (m1 != m2) {
                ans = 0;
                break;
            }
        }
        else if ((f1 > 0) && (f2 == 0)) {
            if (m1 > m2) {
                ans = 0;
                break;
            }
        }
        else if (f1 == 0 && f2 > 0) {
            if (m2 > m1) {
                ans = 0;
                break;
            }
        }
        else {
            ans *= min(m1,m2);
            ans %= MOD;
        }
        // cout << "ans:" << ans << endl;
    }

    cout << ans << endl;
    return 0;
}
