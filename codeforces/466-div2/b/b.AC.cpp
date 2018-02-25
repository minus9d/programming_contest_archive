#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, K, A, B;
    cin >> N >> K >> A >> B;
    
    if (K == 1) {
        cout << ((N - 1) * A) << endl;
    }
    else {
        ll ans = 0;
        ll x = N;
        while (x > 1) {
            if (x < K) {
                ans += (x - 1) * A;
                break;
            }
            else if (x % K != 0) {
                ll new_x = (x / K) * K;
                ans += (x - new_x) * A;
                x = new_x;
            }
            else {
                ll new_x = x / K;
                ll cost1 = B;
                ll cost2 = (x - new_x) * A;
                ans += min(cost1, cost2);
                x = new_x;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
