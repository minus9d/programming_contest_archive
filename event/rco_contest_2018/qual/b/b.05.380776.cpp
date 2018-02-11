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
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>
#include <cstring>


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


int H, W, D, K;

int sector_map[200][200];
//vector<pair<int, int>> sectors;
vector<pair<int, int>> locs;
vector<int> costs;


int dist2(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}


int dist(int i, int j) {
    auto loc1 = locs[i];
    auto loc2 = locs[j];
    return abs(loc1.first - loc2.first) + abs(loc1.second - loc2.second);
}

// 点Pを点(h, w)に移動させたときのスコア変動
int try_move(int p_idx, int h, int w) {
    int diff_score = 0;

    // 点Pの元スコア
    if (p_idx != 0) {
        diff_score -= dist(p_idx - 1, p_idx);  // 元スコア
        diff_score += dist2(locs[p_idx - 1].first, locs[p_idx - 1].second, h, w);
    }
    if (p_idx != D - 1) {
        diff_score -= dist(p_idx, p_idx + 1);
        diff_score += dist2(locs[p_idx + 1].first, locs[p_idx + 1].second, h, w);
    }
    return diff_score;

}

int try_swap(int p_idx, int h, int w) {
    int diff_score = try_move(p_idx, h, w);

    // 点Pの移動先に点Qがある場合
    if (sector_map[h][w] != -1) {
        auto q_idx = sector_map[h][w];
        diff_score += try_move(q_idx, locs[p_idx].first, locs[p_idx].second);

        // 点Pと点Qとで番号が連続する場合は要注意
        if (abs(p_idx - q_idx == 1)) {
            diff_score += dist(p_idx, q_idx);
        }
    }

    return diff_score;
}

void do_swap(int p_idx, pair<int, int> q_loc) {
    auto p_loc = locs[p_idx];

    locs[p_idx] = q_loc;

    int q_h = q_loc.first;
    int q_w = q_loc.second;
    if (sector_map[q_h][q_w] != -1) {
        auto q_idx = sector_map[q_h][q_w];
        locs[q_idx] = p_loc;
    }

    swap(sector_map[p_loc.first][p_loc.second], sector_map[q_loc.first][q_loc.second]);
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> H >> W >> D >> K;

    //sectors.resize(D);
    locs.resize(D);
    costs.resize(D);

    memset(sector_map, -1, sizeof(sector_map));

    REP(d, D) {
        int r, c;
        cin >> r >> c;
        auto loc = mp(r, c);
        //sectors[d] = loc;
        locs[d] = loc;
        sector_map[r][c] = d;
    }

    REP(d, D - 1) {
        auto cost = dist(d, d + 1);
        costs[d] += cost;
        costs[d + 1] += cost;
    }

    vector<int> used_d(D);
    REP(k, K) {

        // もっともコストの高い点を選ぶ
        REP(d, D - 1) {
            auto cost = dist(d, d + 1);
            costs[d] += cost;
            costs[d + 1] += cost;
        }
        int greatest_cost = -1;
        int greatest_d = -1;
        REP(d, D) {
            if (used_d[d]) continue;
            if (costs[d] > greatest_cost) {
                greatest_cost = costs[d];
                greatest_d = d;
            }
        }

        // 使い切ったときはランダム
        if (greatest_d == -1) {
            greatest_d = rand() % D;
        }

        auto p_idx = greatest_d;
        used_d[greatest_d] = 1;

        // 点Pを置きに行く先を best_swap とする
        int best_diff = 1e9;
        pair<int, int> best_swap;
        REP(h, H) {
            REP(w, W) {
                auto diff = try_swap(p_idx, h, w);
                //fprintf(stderr, "  move to (%d, %d): diff %d\n", h, w, diff);
                if (diff < best_diff) {
                    best_diff = diff;
                    best_swap = mp(h, w);
                }
            }
        }

        cout << locs[p_idx].first << " "
            << locs[p_idx].second << " "
            << best_swap.first << " "
            << best_swap.second << endl;

        do_swap(p_idx, best_swap);

        //// TODO
        //que.push(mp(-1, p_idx));


        //cerr << endl;
        //REP(h, H) {
        //    REP(w, W) {
        //        cerr << sector_map[h][w] << "\t";
        //     }
        //    cerr << endl;
        //}
    }

    return 0;
}

