#include <algorithm>
#include <array>
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
typedef long long ll;
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())
template<class T> inline bool chmin(T& a, T b) {
    if (a > b) {
        a = b; return true;
    }
    return false;
}
template<class T> inline bool chmax(T& a, T b) {
    if (a < b) {
        a = b; return true;
    }
    return false;
}
#define pb push_back
#define mp make_pair
#define mt make_tuple

void solve() {
    int W, H, L, U, R, D;
    cin >> W >> H >> L >> U >> R >> D;
    --L; --U; --R; --D;

    vector<vector<long double>> pred(H, vector<long double>(W));

    for(int h = H - 1; h >= 0; --h) {
        for(int w = W - 1; w >= 0; --w) {
            if (L <= w && w <= R && U <= h && h <= D) {
                pred[h][w] = 0.0;
            }
            else if (w == W - 1 && h == H - 1) {
                pred[h][w] = 1.0;
            }
            else if (w == W - 1) {
                pred[h][w] = pred[h + 1][w];
            }
            else if (h == H - 1) {
                pred[h][w] = pred[h][w + 1];
            }
            else {
                pred[h][w] = (pred[h + 1][w] + pred[h][w + 1]) / 2.0;
            }
        }
    }
    cout << fixed << setprecision(20) << pred[0][0];
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
