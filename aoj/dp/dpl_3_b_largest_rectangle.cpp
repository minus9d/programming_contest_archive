// 問題: H*Wのタイルが与えられる。タイルは綺麗か汚れているかのいずれか。
//       綺麗なタイルのみでできる最大の長方形の最大値を求める
// 解法: http://algorithms.blog55.fc2.com/blog-entry-133.html
//       http://algorithms.blog55.fc2.com/blog-entry-132.html
//       まず各要素について上に向かって 1 が何個連続しているかを示すテーブル T を作る
//       次に、T の各行をヒストグラムの入力と見なしヒストグラムの最大長方形の面積を求めるアルゴリズムを適用

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

int largest_square(const int H, const int W, const vector<vector<int>>& cells) {
    // 上に綺麗なタイルが連続する数
    // 番兵として、右端は汚れたタイルがあるものとする
    vector<vector<int>> table(H, vector<int>(W+1));
    REP(w, W) {
        REP(h, H) {
            auto val = cells[h][w];
            if (val == 1) table[h][w] = 0;
            else {
                if (h == 0) table[h][w] = 1;
                else table[h][w] = table[h-1][w] + 1;
            }
        }
    }

    // REP(h, H) {
    //     REP(w, W+1) {
    //         cerr << table[h][w] << " ";
    //     }
    //     cerr << endl;
    // }

    int ans = 0;
    // 各行ごとに、ヒストグラムの最大長方形の面積を求めるアルゴリズムを適用
    REP(h, H) {
        // <ヒストグラムの高さ, index>
        stack<pair<int, int>> s;
        REP(w, W+1) {
            auto height = table[h][w];
            if (s.empty()) s.push(mp(height, w));
            else if (s.top().first < height) s.push(mp(height, w));
            else if (s.top().first > height) {
                int last_idx = w;
                while(!s.empty() && s.top().first > height) {
                    auto area = (w - s.top().second) * s.top().first;
                    ans = max(area, ans);
                    last_idx = s.top().second;
                    s.pop();
                }
                s.push(mp(height, last_idx));
            }
        }
    }
    return ans;
}


int main() {
    int H, W;
    cin >> H >> W;

    vector<vector<int>> cells(H, vector<int>(W));
    REP(h, H) {
        REP(w, W) {
            cin >> cells[h][w];
        }
    }

    cout << largest_square(H, W, cells) << endl;

    return 0;
}
