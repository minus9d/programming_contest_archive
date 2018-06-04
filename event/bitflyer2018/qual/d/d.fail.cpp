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


vector<vector<char>> make_table(ll N, ll M, vector<vector<char>>& stamp_tmp,
                                bool hor_flip, bool ver_flip) {
    auto stamp = stamp_tmp;
    if (hor_flip) {
        for(auto& l: stamp) {
            reverse(ALL(l));
        }
    }
    if (ver_flip) reverse(ALL(stamp));

    vector<vector<char>> up(N, vector<char>(M));
    REP(n, N) {
        REP(m, M) {
            if (m == 0) up[n][m] = stamp[n][m];
            else up[n][m] = up[n][m-1] | stamp[n][m];

            if (n != 0) {
                up[n][m] |= up[n-1][m];
            }
        }
    }
    return up;
}


ll solve1(ll H, ll W, ll N, ll M, vector<vector<char>>& stamp) {
    assert(H == N);
    //REP(h, H) {
    //    vector<vector<char>> stamp_line;
    //    stamp_line.push_back(stamp[h]);
    //    auto table = make_table(N, M, stamp_line, false, false);
    //    REP(m, M-1)

    //}
    return 777;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll H, W;
    cin >> H >> W;
    ll N, M;
    cin >> N >> M;
    vector<vector<char>> stamp(N, vector<char>(M));
    REP(n, N) {
        string tmp;
        cin >> tmp;
        REP(m, M) {
            auto ch = tmp[m];
            stamp[n][m] = (ch == '#') ? 1 : 0;
        }
    }

    if (H == N && W == M) {
        ll ans = 0;
        REP(n, N) REP(m, M) ans += stamp[n][m];
        cout << ans << endl;
    }
    else if (H == N && W != M) {
        cout << solve1(H, W, N, M, stamp) << endl;
    }
    else if (H != N && W == M) {
        vector<vector<char>> stamp_rotate(M, vector<char>(N));
        REP(n, N) REP(m, M) stamp_rotate[m][n] = stamp[n][m];
        cout << solve1(W, H, M, N, stamp_rotate) << endl;
    }
    else {
        auto tbl1 = make_table(N, M, stamp, false, false);
        auto tbl2 = make_table(N, M, stamp, true, false);
        auto tbl3 = make_table(N, M, stamp, false, true);
        auto tbl4 = make_table(N, M, stamp, true, true);

        // corner


        ll ans = 0;
        REP(n, min(N - 1, H / 2)) {
            //if (W - (2 * M - 2) >= 0) {
            //    ans += tbl1[]
            //}

            //REP(m, min(M - 1, W / 2)) {
            //    if
            //}
        }
    }


    

    return 0;
}
