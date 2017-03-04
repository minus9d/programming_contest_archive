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
    int H, W, K;
    cin >> H >> W >> K;
    vector<vector<int>> cells(H, vector<int>(W));
    REP(h,H) {
        string s;
        cin >> s;
        REP(w,W) {
            cells[h][w] = s[w] - '0';
        }
    }
    vector<vector<char>> used(H, vector<char>(W));


    vector<vector<pair<int,int>>> answers;

    // 3x3で区切っていく
    int width = 3;
    int height = 3;
    int tl_w = 0;
    int tl_h = 0;
    while(tl_h + height <= H) {
        if (tl_w + width >= W) {
            tl_h += 3;
            tl_w = 0;
            continue;
        }

        int nonzero = 0;
        vector<pair<int, pair<int, int>>> nums;
        FOR(h, tl_h, tl_h + height) {
            FOR(w, tl_w, tl_w + width) {
                if (cells[h][w] != 0) {
                    nums.push_back(mp(cells[h][w], mp(h, w)));
                    ++nonzero;
                }
            }
        }
        if (nonzero < 8) {
            tl_w += 1;
            continue;
        }
        else {
            tl_w += 3;

            // append
            sort(nums.rbegin(), nums.rend());
            vector<pair<int, int>> ans;
            REP(i, 8) {
                ans.pb(nums[i].second);
            }
            answers.pb(ans);
        }

    }
    
    cout << SIZE(answers) << endl;
    for(auto& ans: answers) {
        for(auto& pos: ans) {
            printf("%d %d\n", pos.first+1, pos.second+1);
        }
    }

    return 0;
}
