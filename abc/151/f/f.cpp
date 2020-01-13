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

// http://atelier-peppe.jp/programTips/GEOMETRIC/KIKA_10.html

#define eps    0.00001
// 0.0か?
#define EQ0(x) ((-eps <= (x)) && ((x) <= eps))
// 同一か？
#define EQ(a, b) (EQ0((a) - (b)))

// 直線の垂直二等分線算出
void CalcPerpLineSeg(double sx, double sy, double ex, double ey, double& a, double& b)
{
    // 線の傾き
    double a1 = (sy - ey) / (sx - ex);

    // 垂直二等分線の傾き
    if(EQ0(a1)){
        a = 1.0;
    }
    else{
        a = -1.0 / a1;
    }
    // 線の中点
    double cx(sx + (ex - sx) / 2.0);
    double cy(sy + (ey - sy) / 2.0);
    // 求める切片
    if(EQ0(a1)){
        b = 0;
    }
    else{
        b = cy - a * cx;
    }
}

bool CircleBy3Point(double x1, double y1, double x2, double y2, double x3, double y3,
                    double& cx, double& cy, double& dRad)
{
    // もし3点の中で同じ点が存在すれば、エラーとして返す
    if( (EQ(x1, x2) && EQ(y1, y2))
    ||  (EQ(x2, x3) && EQ(y2, y3))
    ||  (EQ(x3, x1) && EQ(y3, y1))
    ){
        return false;
    }
    // == 中心を算出 == 
    // 与えられた二点の垂直二等分線を算出
    double a, b, c, d;
    CalcPerpLineSeg(x1, y1, x2, y2, a, b);
    CalcPerpLineSeg(x2, y2, x3, y3, c, d);

    // もし3点が直線上の点なら、円にはならない
    if(EQ0(a - c)){
        return false;
    }
    // 中心を算出
    cx = (d - b) / (a - c);
    cy = a * cx + b;
    // 半径を算出
    dRad = sqrt(pow(cx - x1, 2.0) + pow(cy - y1, 2.0));

    return true;
}


int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<pair<double, double>> xys(N);
    REP(n, N) {
        cin >> xys[n].first >> xys[n].second;
    }

    if (N == 2) {
        auto& xy1 = xys[0];
        auto& xy2 = xys[1];
        auto x1 = xy1.first;
        auto y1 = xy1.second;
        auto x2 = xy2.first;
        auto y2 = xy2.second;

        auto dist = hypot(x1 - x2, y1 - y2);
        printf("%.20f\n", dist / 2.0);
    }
    else {
        // 3点ver
        double ans = 1e19;
        REP(i, N - 2) {
            FOR(j, i + 1, N - 1) {
                FOR(k, j + 1, N) {
                    auto& xy1 = xys[i];
                    auto& xy2 = xys[j];
                    auto& xy3 = xys[k];
                
                    auto x1 = xy1.first;
                    auto y1 = xy1.second;
                    auto x2 = xy2.first;
                    auto y2 = xy2.second;
                    auto x3 = xy3.first;
                    auto y3 = xy3.second;

                    double cx, cy, dRad;
                    auto res = CircleBy3Point(
                        x1, y1, x2, y2, x3, y3, 
                        cx, cy, dRad);
                    if (!res) continue;

                    // 他の点がすべて円に入っているか？
                    bool ok = true;
                    REP(ii, N) {
                        auto& xy = xys[ii];
                        auto x = xy.first;
                        auto y = xy.second;
                        auto d = hypot(x - cx, y - cy);
                        if (d <= dRad + 1e-9) {
                            // do nothing
                        } else {
                            ok = false;
                        }
                    }
                    if (ok) {
                        ans = min(ans, dRad);
                    }
                }
            }
        }
        // 2点ver
        REP(i, N - 1) {
            FOR(j, i + 1, N) {
                auto& xy1 = xys[i];
                auto& xy2 = xys[j];
                auto x1 = xy1.first;
                auto y1 = xy1.second;
                auto x2 = xy2.first;
                auto y2 = xy2.second;

                double cx = (x1 + x2) / 2.0;
                double cy = (y1 + y2) / 2.0;
                double dRad = hypot(x1 - x2, y1 - y2) / 2.0;

                // 他の点がすべて円に入っているか？
                bool ok = true;
                REP(ii, N) {
                    auto& xy = xys[ii];
                    auto x = xy.first;
                    auto y = xy.second;
                    auto d = hypot(x - cx, y - cy);
                    if (d <= dRad + 1e-9) {
                        // do nothing
                    } else {
                        ok = false;
                    }
                }
                if (ok) {
                    ans = min(ans, dRad);
                }
            }
        }


        printf("%.20f\n", ans);
    }
    return 0;
}
