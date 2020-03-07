// 二分探索するところ、判定式で2円の交点を使うところまでは自力で気付けた
// 判定式で円の中心も使うコードを本番中はコメントアウトしてしまったためWA
// そのコードを復活させるとAC

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

struct Meat {
    int x, y, c;
};

// https://github.com/drken1215/algorithm/blob/master/Geometry/crosspoint_line_circle.cpp

////////////////////////////
// 基本要素 (点, 線分, 円)
////////////////////////////

using DD = double;
const DD INF = 1LL<<60;      // to be set appropriately
const DD EPS = 1e-10;        // to be set appropriately
const DD PI = acosl(-1.0);
DD torad(int deg) {return (DD)(deg) * PI / 180;}
DD todeg(DD ang) {return ang * 180 / PI;}

/* Point */
struct Point {
    DD x, y;
    Point(DD x = 0.0, DD y = 0.0) : x(x), y(y) {}
    friend ostream& operator << (ostream &s, const Point &p) {return s << '(' << p.x << ", " << p.y << ')';}
};
inline Point operator + (const Point &p, const Point &q) {return Point(p.x + q.x, p.y + q.y);}
inline Point operator - (const Point &p, const Point &q) {return Point(p.x - q.x, p.y - q.y);}
inline Point operator * (const Point &p, DD a) {return Point(p.x * a, p.y * a);}
inline Point operator * (DD a, const Point &p) {return Point(a * p.x, a * p.y);}
inline Point operator * (const Point &p, const Point &q) {return Point(p.x * q.x - p.y * q.y, p.x * q.y + p.y * q.x);}
inline Point operator / (const Point &p, DD a) {return Point(p.x / a, p.y / a);}
inline Point conj(const Point &p) {return Point(p.x, -p.y);}
inline Point rot(const Point &p, DD ang) {return Point(cos(ang) * p.x - sin(ang) * p.y, sin(ang) * p.x + cos(ang) * p.y);}
inline Point rot90(const Point &p) {return Point(-p.y, p.x);}
inline DD cross(const Point &p, const Point &q) {return p.x * q.y - p.y * q.x;}
inline DD dot(const Point &p, const Point &q) {return p.x * q.x + p.y * q.y;}
inline DD norm(const Point &p) {return dot(p, p);}
inline DD abs(const Point &p) {return sqrt(dot(p, p));}
inline DD amp(const Point &p) {DD res = atan2(p.y, p.x); if (res < 0) res += PI*2; return res;}
inline bool eq(const Point &p, const Point &q) {return abs(p - q) < EPS;}
inline bool operator < (const Point &p, const Point &q) {return (abs(p.x - q.x) > EPS ? p.x < q.x : p.y < q.y);}
inline bool operator > (const Point &p, const Point &q) {return (abs(p.x - q.x) > EPS ? p.x > q.x : p.y > q.y);}
inline Point operator / (const Point &p, const Point &q) {return p * conj(q) / norm(q);}

/* Line */
struct Line : vector<Point> {
    Line(Point a = Point(0.0, 0.0), Point b = Point(0.0, 0.0)) {
        this->push_back(a);
        this->push_back(b);
    }
    friend ostream& operator << (ostream &s, const Line &l) {return s << '{' << l[0] << ", " << l[1] << '}';}
};

/* Circle */
struct Circle : Point {
    DD r;
    Circle(Point p = Point(0.0, 0.0), DD r = 0.0) : Point(p), r(r) {}
    friend ostream& operator << (ostream &s, const Circle &c) {return s << '(' << c.x << ", " << c.y << ", " << c.r << ')';}
};


////////////////////////////
// 円や直線の交点
////////////////////////////

Point proj_for_crosspoint(const Point &p, const Line &l) {
    DD t = dot(p - l[0], l[1] - l[0]) / norm(l[1] - l[0]);
    return l[0] + (l[1] - l[0]) * t;
}
vector<Point> crosspoint(const Line &l, const Line &m) {
    vector<Point> res;
    DD d = cross(m[1] - m[0], l[1] - l[0]);
    if (abs(d) < EPS) return vector<Point>();
    res.push_back(l[0] + (l[1] - l[0]) * cross(m[1] - m[0], m[1] - l[0]) / d);
    return res;
}
vector<Point> crosspoint(const Circle &e, const Circle &f) {
    vector<Point> res;
    DD d = abs(e - f);
    if (d < EPS) return vector<Point>();
    if (d > e.r + f.r + EPS) return vector<Point>();
    if (d < abs(e.r - f.r) - EPS) return vector<Point>();
    DD rcos = (d * d + e.r * e.r - f.r * f.r) / (2.0 * d), rsin;
    if (e.r - abs(rcos) < EPS) rsin = 0;
    else rsin = sqrt(e.r * e.r - rcos * rcos);
    Point dir = (f - e) / d;
    Point p1 = e + dir * Point(rcos, rsin);
    Point p2 = e + dir * Point(rcos, -rsin);
    res.push_back(p1);
    if (!eq(p1, p2)) res.push_back(p2);
    return res;
}
vector<Point> crosspoint(const Circle &e, const Line &l) {
    vector<Point> res;
    Point p = proj_for_crosspoint(e, l);
    DD rcos = abs(e - p), rsin;
    if (rcos > e.r + EPS) return vector<Point>();
    else if (e.r - rcos < EPS) rsin = 0;
    else rsin = sqrt(e.r * e.r - rcos * rcos);
    Point dir = (l[1] - l[0]) / abs(l[1] - l[0]);
    Point p1 = p + dir * rsin;
    Point p2 = p - dir * rsin;
    res.push_back(p1);
    if (!eq(p1, p2)) res.push_back(p2);
    return res;
}



bool cmp(const Point &a, const Point &b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); }

// int main() {
//     Circle c; cin >> c.x >> c.y >> c.r;
//     int Q; cin >> Q;
//     for (int _ = 0; _ < Q; ++_) {
//         Point x, y;
//         cin >> x.x >> x.y >> y.x >> y.y;
//         Line l(x, y);
//         vector<Point> cp = crosspoint(c, l);
//         if (cp.size() == 1) cp.push_back(cp[0]);
//         sort(cp.begin(), cp.end(), cmp);
//         cout << fixed << setprecision(10)
//             << cp[0].x << " " << cp[0].y << " " << cp[1].x << " " << cp[1].y << endl;
//     }
// }


int main(void)
{
    cin.sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    vector<Meat> meat(N);
    REP(n, N) {
        cin >> meat[n].x >> meat[n].y >> meat[n].c;
    }

    double lo = 0.0;
    double hi = 1000000;

    // double lo = 2.4;
    // double hi = 2.4;

    REP(rep, 200) {

        double mid_time = (lo + hi) / 2;
        // cout << "mid_time = " << mid_time << endl;

        // 各円の半径を決定
        vector<Circle> meat2(N);
        REP(n, N) {
            double dist = mid_time / meat[n].c;
            meat2[n].x = meat[n].x;
            meat2[n].y = meat[n].y;
            meat2[n].r = dist;
        }

        // 円同士が交わる点のリスト
        vector<Point> points;

        // 本番中コメントアウトしていたが解説pdfを読んで復活
        for(auto& m: meat2) {
            Point p;
            p.x = m.x;
            p.y = m.y;
            points.pb(p);
        }

        REP(i, N - 1) {
            FOR(j, i + 1, N) {
                auto& c1 = meat2[i];
                auto& c2 = meat2[j];
                auto tmp = crosspoint(c1, c2);
                for(auto t: tmp) points.pb(t);
            }
        }

        bool result = false;
        for (auto& point: points) {
            int ok_meat_num = 0;
            for(auto& m: meat) {
                auto dist = hypot(m.x - point.x, m.y - point.y);
                auto time = dist * m.c;
                // cout << "    dist, time = " << dist << ", " << time << ","
                //      << (time <= mid_time) << endl;
                ok_meat_num += (time <= mid_time + 1e-9);
            }
            // cout << "  p = " << point.x << "," << point.y << ", meat num = "
            //      << ok_meat_num << endl;

            if (ok_meat_num >= K) {
                result = true;
                break;
            }
        }
        (result ? hi : lo) = mid_time;
    }
    printf("%.16f\n", lo);

    return 0;
}

