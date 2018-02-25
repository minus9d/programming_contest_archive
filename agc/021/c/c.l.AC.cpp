#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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

int H, W, A, B;

// 右端を上から縦に埋める
void fillRightCol(vector<vector<char>>& ans, int &B, int ver) {
    int x = W-1; int y = 0;
    while(ver > 0 && B > 0) {
        ans[y][x] = '^';
        ans[y+1][x] = 'v';
        y += 2;
        ver--;
        B--;
    }
}

// 下端を左から横に埋める
void fillBottomRow(vector<vector<char>>& ans, int &A, int hor) {
    if (hor > 0) {
        int x = 0; int y = H-1;
        while(hor > 0 && A > 0) {
            ans[y][x] = '<';
            ans[y][x+1] = '>';
            x += 2;
            hor--;
            A--;
        }
    }
}

void fill3x3(vector<vector<char>>& ans, int &A, int &B) {
    ans[H-3][W-3] = '<';
    ans[H-3][W-2] = '>';
    ans[H-3][W-1] = '^';
    ans[H-2][W-3] = '^';
    ans[H-2][W-2] = '.';
    ans[H-2][W-1] = 'v';
    ans[H-1][W-3] = 'v';
    ans[H-1][W-2] = '<';
    ans[H-1][W-1] = '>';
    A -= 2;
    B -= 2;
}


// 2x2のマスをラスタスキャン順に埋める
void fill2x2Tile(vector<vector<char>>& ans, int &A, int &B) {
    int x = 0;
    int y = 0;

    while (A > 0) {
        ans[y][x] = '<';
        ans[y][x+1] = '>';
        if (y % 2 == 0) {
            ++y;
        }
        else {
            --y;
            x += 2;
            if (x + 1 >= W) {
                x = 0;
                y += 2;
            }
        }
        A--;
    }

    if (y % 2 == 1) {
        --y;
        x += 2;
        if (x + 1 >= W) {
            x = 0;
            y += 2;
        }
    }

    while (B > 0) {
        ans[y][x] = '^';
        ans[y+1][x] = 'v';
        if (x % 2 == 0) {
            ++x;
        }
        else {
            ++x;
            if (x + 1 >= W) {
                x = 0;
                y += 2;
            }
        }
        B--;
    }
}

pair<bool, vector<vector<char>>> solve(int H, int W, int A, int B) {

    vector<vector<char>> ans(H, vector<char>(W, '.'));

    // 本番中に気づかなかったコーナーケース
    // 右下の3x3が四畳半になる場合を救う。
    // ver は | の数 / 2
    // hor は - の数 / 2
    // tilenum は *の数/4
    //   ****|
    //   ****|
    //   **xxx
    //   **xxx
    //   --xxx
    if ((W % 2) && (H % 2) && 2 * (A + B) + 1 == H * W) {
        auto ver = (W % 2) * (H / 2) - 1;
        auto hor = (H % 2) * (W / 2) - 1;
        auto tilenum = (W / 2) * (H / 2) - 1;
        auto needtile
            = (max(0, A - hor - 2) + 1) / 2
            + (max(0, B - ver - 2) + 1) / 2;
        if (needtile <= tilenum) {
            fillRightCol(ans, B, ver);
            fillBottomRow(ans, A, hor);
            fill3x3(ans, A, B);
            fill2x2Tile(ans, A, B);
            return mp(true, ans);
        }
    }

    // コーナーケース以外
    auto ver = (W % 2) * (H / 2);
    auto hor = (H % 2) * (W / 2);
    auto tilenum = (W / 2) * (H / 2);
    auto needtile
        = (max(0, A - hor) + 1) / 2
        + (max(0, B - ver) + 1) / 2;
    if (needtile > tilenum) {
        return mp(false, ans);
    }

    fillRightCol(ans, B, ver);
    fillBottomRow(ans, A, hor);
    fill2x2Tile(ans, A, B);
    return mp(true, ans);
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> H >> W >> A >> B;
    auto ret = solve(H, W, A, B);

    if (ret.first) {
        cout << "YES" << endl;
        REP(h, H) {
            REP(w, W) {
                cout << ret.second[h][w];
            }
            cout << endl;
        }
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}
