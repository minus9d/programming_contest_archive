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


int simulate(vector<string>& cells, int H, int W) {
    int ans = 0;
    REP(h, H) {
        REP(w, W) {
            int min_dist = 1e9;
            REP(h2, H) {
                REP(w2, W) {
                    if (cells[h2][w2] == '1') {
                        auto dist = abs(h2 - h) + abs(w2 - w);
                        min_dist = min(min_dist, dist);
                    }
                }
            }
            ans = max(ans, min_dist);
        }
    }
    return ans;
}

vector<vector<int>> calc_dist_table(vector<string>& cells, int H, int W) {
    vector<pair<int, int>> center_xys;
    REP(h, H) {
        REP(w, W) {
            if (cells[h][w] == '1') {
                center_xys.pb({ w, h });
            }
        }
    }



    int covered = 0;
    vector<vector<int>> dist_table2(H, vector<int>(W, 1e9));

    if (SIZE(center_xys) == 0) {
        REP(h, H) {
            REP(w, W) {
                dist_table2[h][w] = 777;
            }
        }
    }
    else {
        int d = 0;
        while (covered < H * W) {
            for (auto center_xy : center_xys) {
                auto center_x = center_xy.first;
                auto center_y = center_xy.second;
                FOR(x, center_x - d, center_x + d + 1) {
                    auto d_remain = d - abs(x - center_x);
                    for (auto y : { center_y - d_remain, center_y + d_remain }) {
                        if (x < 0 || x >= W || y < 0 || y >= H) continue;
                        if (dist_table2[y][x] == 1e9) {
                            ++covered;
                            dist_table2[y][x] = d;
                        }
                    }
                }
            }
            ++d;
        }
    }


    return dist_table2;
}

int simulate_fast(vector<string>& cells, int H, int W) {
    auto dist_table = calc_dist_table(cells, H, W);

    int ans = 0;
    REP(h, H) {
        REP(w, W) {
            ans = max(ans, dist_table[h][w]);
        }
    }
    return ans;
}


int solve_slow(vector<string> cells, int H, int W) {
    int ans = 1e9;
    REP(h, H) {
        REP(w, W) {
            char old = cells[h][w];
            cells[h][w] = '1';
            ans = min(ans, simulate(cells, H, W));
            cells[h][w] = old;
        }
    }
    return ans;
}

int solve_fast(vector<string> cells, int H, int W) {

    auto dist_table2 = calc_dist_table(cells, H, W);
    //cout << "dist table2:" << endl;
    //REP(h, H) {
    //    REP(w, W) {
    //        cout << dist_table2[h][w] << " ";
    //    }
    //    cout << endl;
    //}

    // “K“–‚É^‚ñ’†‚Á‚Û‚¢‚Ì‚ð‘I‚Ô
    int max_dist = 0;
    REP(h, H) {
        REP(w, W) {
            max_dist = max(max_dist, dist_table2[h][w]);
        }
    }
    int min_h = 1e9;
    int max_h = -1;
    int min_w = 1e9;
    int max_w = -1;
    REP(h, H) {
        REP(w, W) {
            if (max_dist == dist_table2[h][w]) {
                min_h = min(min_h, h);
                max_h = max(max_h, h);
                min_w = min(min_w, w);
                max_w = max(max_w, w);
            }
        }
    }

    int ans = 1e9;
    FOR(h, min_h - 2, max_h + 3) {
        FOR(w, min_w - 2, max_w + 3) {
            if (w < 0 || w >= W || h < 0 || h >= H) continue;

            auto old = cells[h][w];
            cells[h][w] = '1';
            ans = min(ans, simulate_fast(cells, H, W));
            cells[h][w] = old;
        }
    }
    return ans;


    //int max_val = -1;
    //int max_h = -1;
    //int max_w = -1;
    //REP(h, H) {
    //    REP(w, W) {
    //        if (dist_table2[h][w] > max_val) {
    //            max_val = dist_table2[h][w];
    //            max_h = h;
    //            max_w = w;
    //        }
    //    }
    //}
    //cells[max_h][max_w] = '1';
    //return simulate(cells, H, W);
}


void solve() {

    //while(1) {
    //    cout << endl;
    //    int rate = rand() % 101;
    //    int H = 5;
    //    int W = 5;
    //    vector<string> cells(H, string(W, '0'));
    //    REP(h, H) {
    //        REP(w, W) {
    //            if (rand() % 100 < rate) {
    //                cells[h][w] = '1';
    //            }
    //            //if (h == 0 || h == H - 1 || w == 0 || w == W - 1) {
    //            //    cells[h][w] = '1';
    //            //}
    //        }
    //    }


    //    auto gt = solve_slow(cells, H, W);
    //    auto mine = solve_fast(cells, H, W);
    //    if (gt != mine) {
    //        cout << "error!" << endl;
    //        REP(h, H) cout << cells[h] << endl;
    //        cout << "gt = " << gt << endl;
    //        cout << "mine = " << mine << endl;
    //        cout << "continue..." << endl;
    //    }
    //}

    int H, W;
    cin >> H >> W;
    vector<string> cells(H);
    REP(h, H) cin >> cells[h];
    cout << solve_fast(cells, H, W);
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
