// 本番時WA、原因は★部分参照

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

bool canMake(vector<int>& vs, int goal) {
    if (vs.empty()) {
        return goal == 0;
    }
    set<int> tmp;
    if (vs[0] == goal) return true;
    tmp.insert(vs[0]);
    tmp.insert(0);
    FOR(i, 1, SIZE(vs)) {
        set<int> tmp2;
        for (auto t: tmp) {
            auto val = t + vs[i];
            if (val == goal) return true;
            if (val < goal) tmp2.insert(val);

            tmp2.insert(t); // ★★本番ではこの行を入れ忘れてWA
        }
        tmp = tmp2;
    }
    return tmp.count(goal);
}

bool can_move(deque<int>& vs, int goal, int ini_pos) {
    set<int> tmp;
    tmp.insert(ini_pos);
    for(auto v: vs) {
        set<int> tmp2;
        for (auto t: tmp) {
            tmp2.insert(t + v);
            tmp2.insert(t - v);
        }
        tmp = tmp2;
    }
    return tmp.count(goal);
}

// 本番中に出した答案。canMake()にバグがありWA
bool solve_fail(string s, int x, int y) {
    bool ini = true;
    bool xyFlag = true;
    vector<int> xs;
    vector<int> ys;
    int len = 0;
    for (auto ch : s) {
        if (ch == 'F') {
            if (ini) {
                --x;
            }
            else {
                ++len;
            }
        }
        else {
            if (ini) {
                ini = false;
            }
            else {
                if (len != 0) {
                    if (xyFlag) xs.pb(len);
                    else ys.pb(len);
                }
            }
            xyFlag = !xyFlag;
            len = 0;
        }
    }
    if (s.back() == 'F') {
        if (!ini) {
            if (xyFlag) xs.pb(len);
            else ys.pb(len);
        }
    }

    x = abs(x);
    y = abs(y);
    auto xSum = accumulate(ALL(xs), 0);
    auto ySum = accumulate(ALL(ys), 0);
    if ((xSum + x) % 2) return false;
    if ((ySum + y) % 2) return false;

    auto ans1 = canMake(xs, (xSum + x) / 2);
    auto ans2 = canMake(ys, (ySum + y) / 2);

    return ans1 && ans2;
}

// 終了後書いた答案。AC
bool solve_later(string s, int x, int y) {
    bool xyFlag = true;
    deque<int> xs;
    deque<int> ys;
    int len = 0;
    for (auto ch : s) {
        if (ch == 'F') {
            ++len;
        }
        else {
            if (len != 0) {
                if (xyFlag) xs.pb(len);
                else ys.pb(len);
            }
            xyFlag = !xyFlag;
            len = 0;
        }
    }
    if (s.back() == 'F') {
        if (xyFlag) xs.pb(len);
        else ys.pb(len);
    }

    int xPos = 0;
    if (SIZE(xs) > 0 && s[0] == 'F') {
        xPos = xs[0];
        xs.pop_front();
    }

    return can_move(xs, x, xPos) && can_move(ys, y, 0);
}


int main(void)
{
    cin.sync_with_stdio(false);
    string s;
    cin >> s;
    int x, y;
    cin >> x >> y;

    //assert(solve_later("FFFFF", 5, 0) == true);
    //assert(solve_later("F", 1, 0) == true);
    //assert(solve_later("F", 0, 0) == false);
    //assert(solve_later("T", 0, 0) == true);
    //assert(solve_later("TTTTTT", 0, 0) == true);
    //assert(solve_later("TTTTTT", 0, 1) == false);
    //assert(solve_later("TTTTTT", 1, 0) == false);
    //assert(solve_later("T", 1, 0) == false);
    //assert(solve_later("TFF", 0, 2) == true);
    //assert(solve_later("TFF", 0, -2) == true);
    //assert(solve_later("TFF", -1, -2) == false);
    //assert(solve_later("FTFFTFFFTFFF", 4, -5) == true);
    //assert(solve_later("FTFFTFFFTFFF", 4, -1) == true);
    //assert(solve_later("FTFFTFFFTFFF", 4, 1) == true);
    //assert(solve_later("FTFFTFFFTFFF", 4, 5) == true);
    //assert(solve_later("FTFFTFFFTFFF", -2, -5) == true);
    //assert(solve_later("FTFFTFFFTFFF", -2, -1) == true);
    //assert(solve_later("FTFFTFFFTFFF", -2, 1) == true);
    //assert(solve_later("FTFFTFFFTFFF", -2, 5) == true);
    //assert(solve_later("FTFFTFFFTFFF", 3, -5) == false);
    //assert(solve_later("FTFFTFFFTFFF", 3, -1) == false);
    //assert(solve_later("FTFFTFFFTFFF", 3, 1) == false);
    //assert(solve_later("FTFFTFFFTFFF", 3, 5) == false);
    //assert(solve_later("FTFFTFFFTFFF", -3, -5) == false);
    //assert(solve_later("FTFFTFFFTFFF", -3, -1) == false);
    //assert(solve_later("FTFFTFFFTFFF", -3, 1) == false);
    //assert(solve_later("FTFFTFFFTFFF", -3, 5) == false);

    //for (auto i : vector<int>{ -6, -2, 2, 6 }) {
    //    for (auto j : vector<int>{ -4, -2, 2, 4 }) {
    //        assert(solve_later("TFTFFTFFFTFFFF", i, j) == true);
    //        assert(solve_later("TFTFFTFFFTFFFFT", i, j) == true);
    //        assert(solve_later("TFTFFTFFFTFFFFTT", i, j) == true);
    //        assert(solve_later("TFTFFTFFFTTTFFFFTT", i, j) == true);
    //    }
    //}

    //assert(solve_later("FFTFF", 2, 2) == true);
    //assert(solve_later("FFTFF", 2, -2) == true);

    //assert(solve_later("TFTTFTTFFF", 0, -1) == true);
    //assert(solve_fail("TFTTFTTFFF", 0, -1) == true);

    //FOR(len, 2, 20) {
    //    REP(i, 1 << len) {
    //        string str = "";
    //        REP(j, len) {
    //            if ((1 << j) & i) {
    //                str += "T";
    //            }
    //            else {
    //                str += "F";
    //            }
    //        }
    //        FOR(y, -10, 11) {
    //            FOR(x, -10, 11) {
    //                auto ans1 = solve_later(str, x, y);
    //                auto ans2 = solve_fail(str, x, y);
    //                if (ans1 != ans2) {
    //                    cout << "str, x, y = " << str << ", " << x << ", " << y << endl;
    //                    exit(-1);
    //                }
    //                //assert(solve_later(str, x, y) == solve_fail(str, x, y));
    //            }
    //        }
    //    }
    //}

    assert(solve_later(s, x, y) == solve_fail(s, x, y));

    if (solve_later(s, x, y)) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}
