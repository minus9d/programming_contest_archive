#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
// #include <unordered_set>
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

//unordered_set<pair<int,int>> blacks;
set<pair<int,int>> blacks;

int main(void)
{
    cin.sync_with_stdio(false);
    int H, W, N;
    cin >> H >> W >> N;

    REP(n,N) {
        int a,b;
        cin >> a >> b;
        --a; --b;
        blacks.insert(mp(a,b));
    }

    vector<ll> appear(10);
    vector<vector<char>> mini(5, vector<char>(5));
    for(auto&e: blacks) {
        auto cy = e.first;
        auto cx = e.second;

        REP(y1,5) {
            REP(x1,5) {
                auto y = cy + y1 - 2;
                auto x = cx + x1 - 2;
                if (0 <= y && y < H && 0 <= x && x < W) {
                    mini[y1][x1] = blacks.count(mp(y,x));
                }
                else {
                    mini[y1][x1] = -100;
                }
            }
        }

        // cout << endl;
        // cout << "mini:" << endl;
        // REP(y1,5) {
        //     REP(x1,5) {
        //         cout << (int)mini[y1][x1] << "\t";
        //     }
        //     cout << endl;
        // }

        REP(y1,3) {
            REP(x1,3) {
                int tmp = 0;
                REP(y,3) {
                    REP(x,3) {
                        tmp += mini[y1+y][x1+x];
                    }
                }
                if (tmp >= 0) {
                    ++appear[tmp];
                    // cout << "found " << tmp << endl;
                }
            }
        }
    }

    ll zero_cnt = (ll)(W-2) * (H-2);
    FOR(x,1,10) {
        zero_cnt -= appear[x] / x;
    }
    cout << zero_cnt << endl;
    FOR(x,1,10) {
        cout << appear[x] / x << endl;
    }

    return 0;
}
