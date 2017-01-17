#include <iostream>
#include <sstream>
#include <string>
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

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, A, B;
    cin >> N >> A >> B;
    vector<ll> Xs(N);
    REP(n,N) {
        cin >> Xs[n];
    }

    ll pos = 0;
    ll ans = 0;
    REP(n,N) {
        if (n != 0) {
            ans += min((Xs[n] - pos) * A, B);
        }
        pos = Xs[n];
    }
    cout << ans << endl;
    return 0;
}
