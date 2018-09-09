//    →→→↓
//　　↓←←←
//　　→→→↓
//    終←←←
//
//  上記の順番で捜査し、コイン数が奇数のセルがあれば、上記のパスに沿って、
//  次にコイン数が奇数のセルが見つかるまで移動。
//
//  本番では、コインを見つけるパスは上記の通り行ったのだが、
//  コインを移動させるパスは最短路で行ってしまったためWAを多発。
//  なんとか自力で気づいてAC

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

int main(void)
{
    cin.sync_with_stdio(false);
    int H, W;
    cin >> H >> W;

    vector<vector<int>> cells(H, vector<int>(W));
    REP(h, H) {
        REP(w, W) {
            cin >> cells[h][w];
        }
    }

    vector<pair<int,int>> odd_xys;
    REP(h, H) {
        if (h % 2 == 0) {
            REP(w, W) {
                if (cells[h][w] % 2) odd_xys.pb({w, h});
            }
        }
        else {
            for(int w = W-1; w >= 0; --w) {
                if (cells[h][w] % 2) odd_xys.pb({w, h});
            }
        }
    }

    vector<pair<pair<int,int>,pair<int,int>>> commands;
    auto size = SIZE(odd_xys);
    REP(i, size) {
        if (i != size - 1) {
            // i番目のコインを、i+1(=j)番目に移動させる
            auto& coin_i = odd_xys[i];
            const auto coin_j = odd_xys[i+1];
            // ジグザグ状にコインを移動させることで、
            // かならず同じマスを二度と選択しないように保証できる
            while (coin_i != coin_j) {
                pair<int, int> coin_next;

                // まず横方向の移動を試みる
                int direction = (coin_i.second % 2 == 0) ? 1 : -1;
                int next_x = coin_i.first + direction;
                // 盤面からはみ出る場合は下に移動
                if (next_x == -1 || next_x == W) {
                    coin_next = mp(coin_i.first, coin_i.second + 1);
                }
                // はみ出ない場合は横に移動
                else {
                    coin_next = mp(coin_i.first + direction, coin_i.second);
                }
                commands.pb({ coin_i, coin_next });
                coin_i = coin_next;
            }
            ++i;
        }
    }

    cout << SIZE(commands) << endl;
    for(auto com: commands) {
        cout << (com.first.second + 1) << " "
             << (com.first.first + 1) << " "
             << (com.second.second + 1) << " "
             << (com.second.first + 1) << endl;
    }
    return 0;
}
