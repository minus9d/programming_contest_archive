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
    int N, C;
    cin >> N >> C;
    vector<vector<int>> Ds(C, vector<int>(C));
    REP(c1, C) REP(c2, C) cin >> Ds[c1][c2];
    vector<vector<int>> Cs(N, vector<int>(N));
    REP(n1, N) REP(n2, N) {
        int c;
        cin >> c; --c;
        Cs[n1][n2] = c;
    }
    vector<vector<int>> colors(3, vector<int>(C));
    REP(h, N) {
        REP(w, N) {
            auto c = Cs[h][w];
            auto m = (h + w) % 3;
            ++colors[m][c];
        }
    }

    int ans = 1e9;
    REP(c1, C) {
        REP(c2, C) {
            REP(c3, C) {
                if (c1 == c2 || c2 == c3 || c1 == c3) continue;
                auto score = 0;

                REP(c, C) {
                    auto p1 = Ds[c][c1];
                    auto p2 = Ds[c][c2];
                    auto p3 = Ds[c][c3];
                    score += p1 * colors[0][c];
                    score += p2 * colors[1][c];
                    score += p3 * colors[2][c];
                }
                //cout << score << endl;
                ans = min(ans, score);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
