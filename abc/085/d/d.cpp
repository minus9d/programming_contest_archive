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
    int N, H;
    cin >> N >> H;

    using P = tuple<int, int>;

    priority_queue<P, vector<P>> q;
    vector<int> A(N);
    vector<int> B(N);
    REP(n, N) {
        cin >> A[n] >> B[n];
        q.push( mt(B[n], 1) );
        q.push( mt(A[n], 0) );
    }

    int ans = 0;
    while (H > 0) {
        auto p = q.top();
        auto damage = get<0>(p);
        if (get<1>(p) == 1) {
            q.pop();
            H -= damage;
            ans++;
        }
        else {
            ans += (H + (damage - 1)) / damage;
            break;
        }
    }

    cout << ans << endl;

    return 0;
}
