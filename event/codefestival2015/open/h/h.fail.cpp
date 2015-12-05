#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <numeric>
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

vector<vector<int>> itg_sum;
vector<vector<vector<int>>> itg_num;

int area(int h1, int w1) {
    if (h1 < 0 || w1 < 0) return 0;
    return itg_sum[h1][w1];
}


int get_rect_area(int h1, int h2, int w1, int w2) {
    return area(h2, w2) - area(h2, w1-1) - area(h1-1, w2) + area(h1-1, w1-1);
}

int number(int h1, int w1, int n) {
    if (h1 < 0 || w1 < 0) return 0;
    return itg_num[n][h1][w1];

}

int get_num_count(int h1, int h2, int w1, int w2, int n) {
    if (h1 > h2 || w1 > w2) return 0;
    return number(h2, w2, n) - number(h2, w1-1, n) - number(h1-1, w2, n) + number(h1-1, w1-1, n);
}


int main(void)
{
    cin.sync_with_stdio(false);
    int H, W, K;
    cin >> H >> W >> K;

    // vector<string> cells_ch(H);

    vector<vector<int>> cells(H, vector<int>(W));
    REP(h,H) {
        string tmp;
        cin >> tmp;
        REP(w,W) cells[h][w] = tmp[w] - '0';
    }
    
    // integral sum
    itg_sum.resize(H, vector<int>(W));
    REP(h,H) {
        itg_sum[h][0] = cells[h][0];
        FOR(w,1,W) {
            itg_sum[h][w] = cells[h][w] + itg_sum[h][w-1];
        }

        if (h != 0) {
            REP(w,W) {
                itg_sum[h][w] += itg_sum[h-1][w];
            }
        }
    }

    // integral num
    itg_num.resize(11);
    FOR(n, 1, 10) {
        itg_num[n].resize(H, vector<int>(W));
    }
    REP(h,H) {
        FOR(n, 1, 10) {
            itg_num[n][h][0] = (cells[h][0] == n);

            FOR(w,1,W) {
                itg_num[n][h][w] = (cells[h][w] == n) + itg_num[n][h][w-1];
            }
            if (h != 0) {
                REP(w,W) {
                    itg_num[n][h][w] += itg_num[n][h-1][w];
                }
            }
        }
    }

 // cout << "itg:" << endl;
 // REP(h,H) {
 //     REP(w,W) {
 //         cout << itg_sum[h][w] << " ";
 //     }
 //     cout << endl;
 // }
    
    int ret = 0;
    REP(h1,H) {
        FOR(h2,h1+2,H) {
            REP(w1,W) {
                FOR(w2,w1+2,W) {
                    auto sum = get_rect_area(h1,h2,w1,w2);

                    // cout << "sum: " << sum << endl;

                    auto desire = sum - K;
                    if (desire < 1 || desire > 9) continue;
                    auto possible = get_num_count(h1 + 1, h2 - 1, w1 + 1, w2 - 1, desire);
                    
                    ret += possible;
                }
            }
        }
    }
        
    cout << ret << endl;

    return 0;
}
