#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
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
    int N, K;
    cin >> N >> K;
    vector<vector<int>> cell(N, vector<int>(N));

    REP(n1, N) {
        REP(n2, N) {
            cin >> cell[n1][n2];
        } 
    }

    ll ans = 0;
    for(int group_num = N; group_num >= 1; --group_num) {

        // // for debug
        // cout << "cell:" << endl;
        // REP(n1, N) {
        //     REP(n2, N){
        //         cout << cell[n1][n2] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;

        ll score = group_num * K;
        REP(n1, N-1) {
            FOR(n2, n1+1, N) {
                score -= cell[n1][n2];
            } 
        }
        ans = max(ans, score);

        if (group_num == 1) break;

        int u, v;
        int mx = 0;
        REP(n1, N-1) {
            FOR(n2, n1+1, N) {
                if (cell[n1][n2] > mx) {
                    mx = cell[n1][n2];
                    u = n1;
                    v = n2;
                }
            } 
        }

        // merge u and v
        int M = N - 1;
        vector<vector<int>> new_cell(N, vector<int>(N));
        map<int, int> table;
        int to = 0;
        REP(n, N) {
            if (n == u || n == v) {
                table[n] = N - 2;
            }
            else {
                table[n] = to;
                ++to;
            }
        }

        REP(n1, N) {
            if (n1 == u || n1 == v) {
                continue;
            }
            REP(n2, N) {
                if (n2 == u || n2 == v) {
                    continue;
                }
                new_cell[table[n1]][table[n2]] = cell[n1][n2];
            }
        }

        REP(n, N) {
            if (n == u || n == v) {
                continue;
            }
            int val = cell[n][u] + cell[n][v];
            new_cell[table[n]][N-2] = new_cell[N-2][table[n]] = val;
        }
        
        cell = new_cell;
        N = M;
    }

    cout << ans << endl;

    return 0;
}
