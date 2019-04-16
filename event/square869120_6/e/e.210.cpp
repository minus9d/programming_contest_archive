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


bool solve_bf(vector<string>& cells, int H, int W, int N,
                 vector<pair<int, int>>& id_to_xy) {
    vector<int> shff(N);
    REP(n, N) shff[n] = n;
    do {
        bool ok = true;
        REP(n, N - 1) {
            int id1 = shff[n];
            int id2 = shff[n + 1];
            auto xy1 = id_to_xy[id1];
            auto xy2 = id_to_xy[id2];
            if ((xy1.first != xy2.first) && (xy1.second != xy2.second)) {
                ok = false;
                break;
            }
            if (n >= 1) {
                auto xy0 = id_to_xy[shff[n - 1]];
                if (((xy0.first == xy1.first) && (xy1.first == xy2.first))
                    || ((xy0.second == xy1.second) && (xy1.second == xy2.second))) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) {
            return true;
        }
    }while(next_permutation(ALL(shff)));
    return false;
}

bool dfs(const vector<string>& cells, int H, int W, int N,
         const vector<pair<int, int>>& id_to_xy,
         int prev_id, int curr_id, vector<char>& used, int visit_num) {
    if (visit_num == N) return true;
    REP(next_id, N) {
        if (used[next_id]) continue;

        auto xy1 = id_to_xy[curr_id];
        auto xy2 = id_to_xy[next_id];
        if ((xy1.first != xy2.first) && (xy1.second != xy2.second)) {
            continue;
        }
        if (prev_id != -1) {
            auto xy0 = id_to_xy[prev_id];
            if (((xy0.first == xy1.first) && (xy1.first == xy2.first))
                || ((xy0.second == xy1.second) && (xy1.second == xy2.second))) {
                continue;
            }
        }
        
        used[next_id] = 1;
        visit_num++;
        bool res = dfs(cells, H, W, N, id_to_xy,
                       curr_id, next_id, used, visit_num);
        if (res) return true;
        
        used[next_id] = 0;
        visit_num--;
    }
    return false;
}

bool solve_dfs(vector<string>& cells, int H, int W, int N,
               vector<pair<int, int>>& id_to_xy) {
    REP(n, N) {
        vector<char> used(N);
        used[n] = 1;
        bool judge = dfs(cells, H, W, N, id_to_xy,
                         -1, n, used, 1);
        if (judge) return true;
    }
    return false;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int H, W;
    cin >> H >> W;
    vector<string> cells(H);
    REP(h ,H) {
        cin >> cells[h];
    }
    vector<pair<int, int>> id_to_xy;
    REP(h, H) {
        REP(w, W) {
            if (cells[h][w] == 'o') {
                id_to_xy.pb({w, h});
            }
        }
    }
    auto N = SIZE(id_to_xy);
    bool ret = false;
    if (N <= 8) {
        ret = solve_bf(cells, H, W, N, id_to_xy);
    }
    else {
        ret = solve_dfs(cells, H, W, N, id_to_xy);
    }
    if (ret) {
        cout << "Possible" << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
