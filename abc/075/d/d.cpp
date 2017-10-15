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
    int N, K;
    cin >> N >> K;

    map<int, int> XtoY;
    set<int> X;
    // map<int, int> Y;
    REP(n, N) {
        int x, y;
        cin >> x >> y;
        X.insert(x);
        // Y[x] += 1;
        XtoY[x] = y;
    }
    vector<int> Xvec(ALL(X));
    int XSize = SIZE(Xvec);

    ll ans = 5 * 1e18;
    REP(xidx1, XSize) {
        int pointNumMax = 0;
        set<int> Y;
        FOR(xidx2, xidx1, XSize) {
            auto x1 = Xvec[xidx1];
            auto x2 = Xvec[xidx2];

            pointNumMax++;
            auto y = XtoY[x2];
            Y.insert(y);

            // [xidx1, xidx2]の間の領域に少なくともK個点がある
            if (pointNumMax >= K) {
                vector<int> Yvec(ALL(Y));
                int yidx1 = 0;
                int yidx2 = K - 1;
                while(yidx2 < pointNumMax) {
                    auto y1 = Yvec[yidx1];
                    auto y2 = Yvec[yidx2];
                    ans = min(ans, ll(x2 - x1) * ll(y2 - y1));

                    // printf("(x1,x2,y1,y2) = (%d,%d,%d,%d)\n",
                    //        x1, x2, y1, y2);
                    
                    ++yidx1;
                    ++yidx2;
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}
