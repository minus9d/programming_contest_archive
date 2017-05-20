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

vector<ll> biggest_n(vector<ll>& As, int N) {

    vector<ll> sums(3*N);
    multiset<ll> kept;

    REP(n, 3*N) {
        auto a = As[n];
        if (n == 0) {
            sums[n] = a;
            kept.insert(a);
        }
        else if (n < N) {
            sums[n] = sums[n-1] + a;
            kept.insert(a);
        }
        else {
            if (*kept.begin() < a) {
                sums[n] = sums[n-1] - *kept.begin() + a;
                kept.erase(kept.begin());
                kept.insert(a);
            }
            else {
                sums[n] = sums[n-1];
            }
        }
    }

    // for(auto s:sums) cout << s << " ";
    // cout << endl;

    return sums;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<ll> As(3*N);
    REP(n, 3*N) {
        cin >> As[n];
    }

    auto left_largeN = biggest_n(As, N);
    vector<ll> Bs(3*N);
    REP(i, 3*N) {
        Bs[i] = -As[3*N-1-i];
    }
    auto right_smallN = biggest_n(Bs, N);

    ll ans = 0;
    FOR(i, N-1, 2*N) {
        auto val1 = left_largeN[i];
        auto idx = (3 * N - 1) - i - 1;
        auto val2 = -right_smallN[idx];
        // cout << "i, idx = " << i << "," << idx << endl;
        // cout << "val1, val2 = " << val1 << "," << val2 << endl;
        if (i == N-1) ans = val1 - val2;
        else ans = max(ans, val1 - val2);
    }
    cout << ans << endl;

    return 0;
}
