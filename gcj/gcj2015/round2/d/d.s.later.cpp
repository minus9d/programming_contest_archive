#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>
#include <complex>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

void solve(void)
{
    int R, C;
    cin >> R >> C;
    
    // C = 3
    //   3*  (221)*
    //   3*  (221)*
    // C = 4, 5
    //   C = 3の1つ目
    // C = 6
    //   3*  (221)*  122221
    //   3*  (221)*  221122
    if (R == 2) {
        vector<int> ans{0,0,0,2,1,1,3};
        cout << ans[C];
    }

    // C = 3, 4, 5, 6
    //   2*  3*
    //   3*  2*
    //   3*  2*
    else if (R == 3) {
        vector<int> ans{0,0,0,2,3,2,2};
        cout << ans[C];
    }

    // C = 3
    //   2*  221  333
    //   3*  221  333
    //   3*  333  221
    //   2*  333  221
    // C = 4, 5
    //   C = 3の1つ目
    // C = 6
    //   2*  (221)*  (333)*  122221  333333
    //   3*  (221)*  (333)*  221122  333333
    //   3*  (333)*  (221)*  333333  122221
    //   2*  (333)*  (221)*  333333  221122
    else if (R == 4) {
        vector<int> ans{0,0,0,3,1,1,5};
        cout << ans[C];
    }

    // C = 3
    //   3*  222  221
    //   3*  333  221
    //   2*  333  333
    //   3*  221  333
    //   3*  221  222
    // C = 4
    //   3*  3333  2212
    //   3*  3333  1212
    //   2*  2212  1222
    //   3*  1212  3333
    //   3*  1222  3333
    // C = 5
    //   C = 3の1つ目
    // C = 6 (本番で失敗)
    //   3*  (222)*  (221)*  222222  122221
    //   3*  (333)*  (221)*  333333  221122
    //   2*  (333)*  (333)*  333333  333333
    //   3*  (221)*  (333)*  122221  333333
    //   3*  (221)*  (222)*  221122  222222
    else if (R == 5) {
        vector<int> ans{0,0,0,3,3,1,5};
        cout << ans[C];
    }

    // C = 3(本番で失敗)
    //   3*  2*  221  221  221  333
    //   3*  3*  221  221  221  333
    //   2*  3*  333  333  333  221
    //   3*  2*  333  333  333  221
    //   3*  3*  221  212  122  333
    //   2*  3*  221  212  122  333
    // C = 4
    //   3*  2*  2212  2222
    //   3*  3*  1212  3333
    //   2*  3*  1222  3333
    //   3*  2*  3333  2212
    //   3*  3*  3333  1212
    //   2*  3*  2222  1222
    // C = 5
    //   C = 3の最初2つ
    // C = 6(本番で失敗)
    //     (a)    (b) (c)    (d)
    //     122221 3*  (221)* 2*
    //     221122 3*  (221)*
    //   と置くと、以下の19通り
    //     a a b b b c c d
    //     b b a c d b b b
    //     a c b b b a c d
    //             d     b
    //     ---------------
    //     6 3 1 1 1 3 3 1  (パターンの回転を考慮した場合の数)
    else if (R == 6) {
        vector<int> ans{0,0,0,6,4,2,19};
        cout << ans[C];
    }
}

int bruteforce(int R, int C) {
    vector<vector<int>> cell(R, vector<int>(C));
    REP(i, (1 << (R*C))) {
        REP(j, (R*C)) {
            if (i & (1 << j)) {
            }
        }
    }
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": ";
        solve();
        cout << endl;
    }

    return 0;
}
