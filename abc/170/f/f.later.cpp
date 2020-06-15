// chokudaiさんの https://atcoder.jp/contests/abc170/submissions/14358430
// 参考に修正
//
// breakとcontinueの両方を使い分ける必要がある

#include <algorithm>
#include <array>
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
typedef long long ll;
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())
#define pb push_back
#define mp make_pair
#define mt make_tuple

using P = pair<int, int>;

int solve(int H, int W, int K, P start, P goal, vector<string> cells) {
    vector<vector<int>> steps(H, vector<int>(W, 1e9));

    queue<P> q;
    q.push(start);
    steps[start.second][start.first] = 0;

    int dx[] = { 0, 0, 1, -1 };
    int dy[] = { 1, -1, 0, 0 };

    int cnt = 0;
    while (!q.empty()) {

        //REP(h, H) {
        //    REP(w, W) {
        //        if (cells[h][w] == '@') {
        //            cout << "@ ";
        //        }
        //        else if (steps[h][w] == 1e9) {
        //            cout << "X ";
        //        }
        //        else {
        //            cout << steps[h][w] << " ";
        //        }
        //    }
        //    cout << endl;
        //}
        //cout << endl;

        P cur = q.front(); q.pop();
        int cur_x = cur.first;
        int cur_y = cur.second;

        int cur_step = steps[cur_y][cur_x];
        if (cur == goal) {
            return cur_step;
        }

        //if (cnt % 1000 == 0) {
        //    cout << "q size " << SIZE(q) << ", step - " << cur_step << ", cnt = " << cnt << endl;
        //}
        cnt++;

        REP(d, 4) {
            FOR(k, 1, K + 1) {
                int next_x = cur_x + dx[d] * k;
                int next_y = cur_y + dy[d] * k;
                if (next_x < 0 || next_x >= W || next_y < 0 || next_y >= H) {
                    break;
                }
                if (cells[next_y][next_x] == '@') break;

                int next_step = steps[next_y][next_x];

                // 改善の見込みがないなら終了
                if (next_step <= cur_step) break;

                // さらにその次のセルで改善する可能性がある
                if (next_step <= cur_step + 1) continue;

                //cout << "next_step: " << next_step << " -> " << cur_step + 1 << endl;

                steps[next_y][next_x] = cur_step + 1;
                q.push(mp(next_x, next_y));
            }
        }
    }

    return -1;

}
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    //while(1){
    //    int H = 1000;
    //    int W = 1000;
    //    int K = rand() % 1000 + 1;
    //    P start, goal;
    //    start.first = rand() % W;
    //    start.second = rand() % W;
    //    goal.first = rand() % W;
    //    goal.second = rand() % W;
    //    vector<string> cells(H);
    //    REP(h, H) {
    //        string s;
    //        REP(w, W) {
    //            s += (rand() % 3 == 1) ? "@" : ".";
    //        }
    //        cells[h] = s;
    //    }
    //    cout << solve(H, W, K, start, goal, cells) << endl;

    //}

    int H, W, K;
    cin >> H >> W >> K;
    P start, goal;
    cin >> start.second >> start.first >> goal.second >> goal.first;
    --start.first;
    --start.second;
    --goal.first;
    --goal.second;

    vector<string> cells(H);
    REP(h, H) cin >> cells[h];

    cout << solve(H, W, K, start, goal, cells) << endl;

    return 0;
}
