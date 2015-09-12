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
#include <climits>

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

int dp[1000][1000][2];

int main(void)
{
    cin.sync_with_stdio(false);
    int W,H,Q;
    cin >> W >> H >> Q;
    
    if (W > 100 || H > 100) return 0;

    vector<tuple<int,int,int>> data(Q);

    int tMax = -1;
    REP(q,Q) {
        int T,D,X;
        cin >> T >> D >> X;
        data[q] = make_tuple(T,D,X);
        tMax = max(tMax, T);
    }
    sort(ALL(data));
    
    int idx = 0;
    FOR(t,1,tMax+1) {
        // beamで盤面を埋める
        vector<vector<char>> cells(H,vector<char>(W));
        while(idx < (int)data.size()) { 
            int& ti = get<0>(data[idx]);
            int& di = get<1>(data[idx]);
            int& xi = get<2>(data[idx]);
			if (ti != t) {
				break;
			}
            if (di == 0) {
                REP(h,H) cells[h][xi-1] = 1;
            }
            else {
                REP(w,W) cells[xi-1][w] = 1;
            }
            ++idx;
        }

        // dp
        REP(h,H) {
            REP(w,W) {
                dp[h][w][t%2] = INT_MAX;
                if (cells[h][w]) {
                    // do nothing
                }
                else {
                    REP(h2,H) {
                        REP(w2,W) {
                            if (dp[h2][w2][(t+1)%2] == INT_MAX) continue;
                            auto diff = abs(h2-h)+abs(w2-w);
                            dp[h][w][t%2] = min(dp[h][w][t%2],dp[h2][w2][(t+1)%2]+diff);
                        }
                    }
                }
            }
        }
    }

    int ret = INT_MAX;
    REP(h,H) {
        REP(w,W) {
            ret = min(ret, dp[h][w][tMax%2]);
        }
    }
    cout << ((ret == INT_MAX) ? -1 : ret) << endl;
        
    return 0;
}
