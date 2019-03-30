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

ll solve(ll N, ll K) {
    if (K == 0) {
        return (N * N);
    }
    else {
        ll ans = 0;
        FOR(b, K + 1, N + 1) {
            auto start = K;
            auto len = b - K;
            auto vacant = b - len;

            while(start <= N) {
                auto end = start + len - 1;
                if (end <= N) {
                    ans += len;
                    start += len + vacant;
                }
                else {
                    ans += N - start + 1;
                    break;
                }
            }
        }
        return ans;
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, K;
    cin >> N >> K;
    cout << solve(N, K) << endl;

    return 0;
}
