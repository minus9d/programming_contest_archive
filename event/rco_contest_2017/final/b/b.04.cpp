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
#include <tuple>
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

typedef pair<int, int> P;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

struct State {
    // (h, w)
    vector<pair<int,int>> locs;
    vector<pair<int,int>> goals;
    vector<vector<char>> cells;
};
State s;
int H, W, K, T;
vector<int> shff;


bool is_out_of_range(int h2, int w2) {
    return (h2 < 1 || h2 > H ||  w2 < 1 || w2 > W);
}

P move_result(P& before, P& diff) {
    P after;
    after.first = before.first + diff.first;
    after.second = before.second + diff.second;
    return after;
}

void update_cells() {
    // 1-based
    s.cells.resize(H+1, vector<char>(W+1));
    for(auto p: s.locs) {
        auto h = p.first;
        auto w = p.second;
        s.cells[h][w] = 1;
    }
}

char move_to_char(const pair<int,int>& p) {
    if (p == mp(0, 0)) return '-';
    else if (p == mp(1, 0)) return 'D';
    else if (p == mp(-1, 0)) return 'U';
    else if (p == mp(0, 1)) return 'R';
    else if (p == mp(0, -1)) return 'L';
    return '?';
}
int count_move_num(string s) {
    int num = 0;
    for(auto ch: s) num += ch != '-';
    return num;
}

P can_get_goal(int idx) {
    auto loc = s.locs[idx];
    auto goal = s.goals[idx];
    
    set<pair<int,int>> seen;
    int dh[] = {0, 0, 1, -1};
    int dw[] = {1, -1, 0, 0};

    priority_queue<P, vector<P>, greater<P> > que;
    que.push(goal);
    seen.insert(goal);
    while(!que.empty()){
       P p = que.top();
       // cout << "p:" << p.first << "," << p.second << endl;
       que.pop();
       REP(d, 4) {
           int h2 = p.first + dh[d];
           int w2 = p.second + dw[d];
           if (seen.count(mp(h2,w2))) continue;
           if (is_out_of_range(h2, w2)) continue;
           if (s.cells[h2][w2]) continue;
           if (mp(h2,w2) == loc) {
               auto h_diff = p.first - loc.first;
               auto w_diff = p.second - loc.second;
               return mp(h_diff, w_diff);
           }
           que.push(mp(h2,w2));
           seen.insert(mp(h2,w2));
       }
    }
    return mp(-1,-1);
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> H >> W >> K >> T;

    s.locs.resize(K);
    s.goals.resize(K);
    shff.resize(K);
    REP(k,K) shff[k] = k;

    vector<tuple<int,int,int,int>> ABCDs(K);
    REP(k, K) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        ABCDs[k] = mt(a, b, c, d);
        s.locs[k] = mp(a, b);
        s.goals[k] = mp(c, d);
    }

    vector<string> anses;

//    REP(t, T) {
    int t = 0;
    bool last_flag = false;
    int last_time = 5;
    int MAX = 7000;
    for(; t < MAX; ++t) {
    // for(; t < 500; ++t) {
//    for(; t < 1000; ++t) {
        set<pair<int,int>> occupied;
        REP(k, K) {
            occupied.insert(s.locs[k]);
        }
        string ans(K, '-');
        random_shuffle(ALL(shff));
        for(auto k: shff) {
            vector<pair<int,int>> poss_move;

            // float random_poss = 0.5 - 0.2 * t / 5000;
            float random_poss = 0.45 - 0.0 * t / 5000;
            if (last_flag) {
                random_poss = 0.0;
            }

            if (rand() % 100 < (random_poss * 100)) {
                int rand_res = rand() % 4;
                if (rand_res == 0) poss_move.pb(mp(1,0));
                else if (rand_res == 1) poss_move.pb(mp(-1,0));
                else if (rand_res == 2) poss_move.pb(mp(0,1));
                else if (rand_res == 3) poss_move.pb(mp(0,-1));
            }
            else {
                if (s.locs[k] == s.goals[k]) {
                    poss_move.pb(mp(0,0));
                }
                else {
                    if (s.locs[k].first < s.goals[k].first) poss_move.pb(mp(1,0));
                    if (s.locs[k].first > s.goals[k].first) poss_move.pb(mp(-1,0));
                    if (s.locs[k].second < s.goals[k].second) poss_move.pb(mp(0,1));
                    if (s.locs[k].second > s.goals[k].second) poss_move.pb(mp(0,-1));
                }
            }

            random_shuffle(ALL(poss_move));
            bool found = false;
            for (auto m : poss_move) {
                auto new_loc = move_result(s.locs[k], m);
                if (is_out_of_range(new_loc.first, new_loc.second)) {
                    continue;
                }

                if (!occupied.count(new_loc)) {
                    occupied.insert(new_loc);
                    ans[k] = move_to_char(m);
                    found = true;
                    s.locs[k] = new_loc;
                    break;
                }
            }
            if (!found) ans[k] = '-';
        }

        if (last_flag) {
            --last_time;
            if (last_time == 0) break;
        }

        auto move_num = count_move_num(ans);
        if (move_num < 10 || t == MAX - last_time) {
            last_flag = true;
        }
        anses.pb(ans);
    }

    // int cur_t = t;
    // for(; t < cur_t + 20; ++t) {
    //     // cout << "---t:"  << t << "---" << endl;
    //     update_cells();
    //     string ans(K, '-');
    //     random_shuffle(ALL(shff));
    //     int cnt = 0;
    //     for(auto k: shff) {
    //         P move = can_get_goal(k);
    //         if (move != mp(-1,-1)) {
    //             cout << endl;
    //             cout << "cell:" << endl;
    //             REP(h,H) {
    //                 REP(w,W) cout << (int)s.cells[h][w];
    //                 cout << endl;
    //             }
    //             cout << k << "'s pos:" << s.locs[k].first << "," << s.locs[k].second << endl;
    //             cout << k << "'s goal:" << s.goals[k].first << "," << s.goals[k].second << endl;
    //             cout << "suggested move:" << move.first << "," << move.second << endl;


    //             ans[k] = move_to_char(move);
    //             auto new_loc = move_result(s.locs[k], move);
    //             s.cells[new_loc.first][new_loc.second] = 1;
    //             s.locs[k] = new_loc;
    //             ++cnt;
    //         }
    //         if (cnt == 20) break;
    //     }
    //     anses.pb(ans);
    // }

    // print ans
    cout << SIZE(anses) << endl;
    for(auto ans: anses) {
        cout << ans << endl;
    }

    return 0;
}

