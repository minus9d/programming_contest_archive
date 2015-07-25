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
#include <complex>

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


#define curr(P, i) P[(i) % P.size()]
#define next(P, i) P[(i+1) % P.size()]
#define prev(P, i) P[(i+P.size()-1) % P.size()]
#define diff(P, i) (next(P, i) - curr(P, i))

const double EPS = 1e-8;
const double INF = 1e12;

typedef complex<double> P;
struct L : public vector<P> {
    L(const P &a, const P &b) {
        push_back(a); push_back(b);
    }
};
typedef vector<P> Polygon;

namespace std {
    bool operator < (const P& a, const P& b) {
        return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
    }
}

// 内積
double dot(const P& a, const P& b) {
    return real(conj(a)*b);
}

// 各次元の値の2乗和
double norm(const P& a) {
    return real(conj(a)*a);
}

// 外積
double cross(const P& a, const P& b) {
    return imag(conj(a)*b);
}

// 点p2を、点p0, p1を通る直線に射影した点
P projection(const P& p0, const P& p1, const P& p2) {
    // 位置ベクトルに直す
    P vec1 = p1 - p0;
    P vec2 = p2 - p0;
    return p0 + vec1 * dot(vec1, vec2) / dot(vec1, vec1);
}

// projectionの別表現
// not verified
P projection(const L &l, const P &p) {
    double t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
    return l[0] + t*(l[0]-l[1]);
}

// 点p0, p1を通る直線を対称軸として、点p2と対称な点
P reflection(const P& p0, const P& p1, const P& p2) {
    P proj = projection(p0, p1, p2);
    return proj - (p2 - proj);
}

int ccw(P a, P b, P c) {
    b -= a; c -= a;
    if (cross(b, c) > 0)   return +1;       // counter clockwise
    if (cross(b, c) < 0)   return -1;       // clockwise
    if (dot(b, c) < 0)     return +2;       // c--a--b on line
    if (norm(b) < norm(c)) return -2;       // a--b--c on line
    return 0;                               // a--c--b on line
}

// 2直線が平行か否か
bool is_parallel(const L& l1, const L& l2) {
    P p1 = l1[1] - l1[0];
    P p2 = l2[1] - l2[0];
    auto res = ccw(p1, p2, P(0,0));
    return (res == 2 || res == -2 || res == 0);
}

// 2直線が垂直か否か
bool is_ortho(const L& l1, const L& l2) {
    P p1 = l1[1] - l1[0];
    P p2 = l2[1] - l2[0];
    return dot(p1, p2) == 0;
}

// l: line(直線)
// s: segment(線分)
// not verified
bool intersectLL(const L &l, const L &m) {
  return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
         abs(cross(l[1]-l[0], m[0]-l[0])) < EPS;   // same line
}

// not verified
bool intersectLS(const L &l, const L &s) {
    return cross(l[1]-l[0], s[0]-l[0])*       // s[0] is left of l
        cross(l[1]-l[0], s[1]-l[0]) < EPS; // s[1] is right of l
}

// not verified
bool intersectLP(const L &l, const P &p) {
    return abs(cross(l[1]-p, l[0]-p)) < EPS;
}

bool intersectSS(const L &s, const L &t) {
    return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
        ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}

// not verified
bool intersectSP(const L &s, const P &p) {
    return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // triangle inequality
}

// not verified
double distanceLP(const L &l, const P &p) {
    return abs(p - projection(l, p));
}

int main(void)
{
    cin.sync_with_stdio(false);
    int x, y;
    cin >> x >> y;
    int N;
    cin >> N;

    vector<int> xs(N), ys(N);
    REP(n,N) {
        cin >> xs[n] >> ys[n];
    }

    P p(x, y);
    double ret = 1e9;
    REP(n,N) {
        P p1(xs[n], ys[n]);
        P p2(xs[(n+1)%N], ys[(n+1)%N]);
        L line(p1, p2);
        auto d = distanceLP(line, p);
        ret = min(ret, d);
    }

    printf("%.12lf\n", ret);

    return 0;
}
