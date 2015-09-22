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

// <h,w>
typedef pair<int,int> Coord;
// <cost, Coord>
typedef pair<int,Coord> P;

const int INF = 1e9;
map<Coord, int> shortest;


int calc_need(int h, int w, vector<string>& cells, int i, int dh, int dw) {
    // スミを吐かない場合の、iマス先まで移動するのに必要なコストを計算
    int ret = 0;
    FOR(j,1,i+1) {
        auto c = cells[h + i * dh][w + i * dw];
        if (c == 'o') {
            ret += 1;
        }
        else if (c == '.' || c == 'S' || c == 'G') {
            ret += 2;
        }
        else if (c == 'x') {
            ret += 10000;
        }
    }

    // スミを吐いた場合のコストと良い方の値を採用
    if (i == 1) ret = min(3, ret);
    else if (i == 2) ret = min(4, ret);
    else if (i == 3) ret = min(5, ret);

    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int H,W;
    cin >> H >> W;

    REP(h,H) REP(w,W) shortest[ mp(h,w) ] = INF;
    
    vector<string> cells(H);
    REP(h,H) cin >> cells[h];

    Coord start;
    Coord goal;
    REP(h,H) REP(w,W) {
        if (cells[h][w] == 'S') start = Coord(h,w);
        if (cells[h][w] == 'G') goal = Coord(h,w);
    }

    priority_queue<P, vector<P>, greater<P>> q;
    q.push( P(0,start) );
    shortest[start] = 0;

    int dh[] = {0,0,1,-1};
    int dw[] = {1,-1,0,0};

    while(!q.empty()) {
        auto p = q.top();
        q.pop();

        auto cost = p.first;
        auto coord = p.second;
        auto h = coord.first;
        auto w = coord.second;

        if (shortest[coord] < cost) continue;

        // 4方向について
        REP(d,4) {
            // 同方向に1, 2, 3進む場合のコストを計算
            FOR(i,1,4) {
                auto h2 = h + dh[d] * i;
                auto w2 = w + dw[d] * i;

                // 枠外に出たり壁にぶつかったりする場合を除去
                if (h2 < 0 || w2 < 0 || h2 >= H || w2 >= W) break;
                if (cells[h + i * dh[d]][w + i * dw[d]] == '#') break;

                // 移動に必要なコスト
                auto need = calc_need(h, w, cells, i, dh[d], dw[d]);

                // 更新
                if (shortest[Coord(h2,w2)] > shortest[coord] + need) {
                    shortest[Coord(h2,w2)] = shortest[coord] + need;
                    q.push( P(shortest[Coord(h2,w2)], Coord(h2,w2)) );
                }
            }
        }
    }

    cout << shortest[goal] << endl;
        
    return 0;
}
