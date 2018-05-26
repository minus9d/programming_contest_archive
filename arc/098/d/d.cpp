#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>


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
    int N;
    cin >> N;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];

    ll ans = 0;
    int start = 0;
    int end = 0;
    ll sum_res = 0;
    ll xor_res = 0;
    while(start < N && end < N) {
        sum_res += As[end];
        xor_res ^= As[end];
        if (sum_res == xor_res) {
            ++end;
        }
        else {
            auto len = end - start;
            ans += len;
            //cout << "from " << start << " to " << end << endl;
            sum_res -= As[start];
            xor_res ^= As[start];
            sum_res -= As[end];
            xor_res ^= As[end];
            ++start;
        }
    }
    // 最後?
    while (start < end) {
        ans += end - start;
        ++start;
    }
    ans += end - start;

    cout << ans << endl;

    return 0;
}
