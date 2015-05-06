#include <complex>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>

using namespace std;

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
// not verified
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

// not verified
double distanceLL(const L &l, const L &m) {
    return intersectLL(l, m) ? 0 : distanceLP(l, m[0]);
}

// not verified
double distanceLS(const L &l, const L &s) {
    if (intersectLS(l, s)) return 0;
    return min(distanceLP(l, s[0]), distanceLP(l, s[1]));
}

double distanceSP(const L &s, const P &p) {
    const P r = projection(s, p);
    if (intersectSP(s, r)) return abs(r - p);
    return min(abs(s[0] - p), abs(s[1] - p));
}

double distanceSS(const L &s, const L &t) {
    if (intersectSS(s, t)) return 0;
    return min(min(distanceSP(s, t[0]), distanceSP(s, t[1])),
               min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}

// 2直線の交点
P crosspoint(const L &l, const L &m) {
    double A = cross(l[1] - l[0], m[1] - m[0]);
    double B = cross(l[1] - l[0], l[1] - m[0]);
    if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
    if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
    return m[0] + B / A * (m[1] - m[0]);
}

// 多角形の面積を求める
// Pは凸包とは限らない
double area(const Polygon& poly) {
    double area = 0.0;
    REP(i, SIZE(poly))
        area += cross(curr(poly, i), next(poly, i));
    return abs(area) * 0.5;
}

// 凸包を求める
// 頂点は反時計回りで返される
Polygon convexHull(const Polygon& poly) {
    Polygon ps = poly;

    int n = ps.size(), k = 0;
    sort(ALL(ps));
    Polygon ch(2*n);
    for (int i = 0; i < n; ch[k++] = ps[i++]) // lower-hull
        while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
    for (int i = n-2, t = k+1; i >= 0; ch[k++] = ps[i--]) // upper-hull
        while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
    ch.resize(k-1);
    return ch;
}

// 凸性判定
// polyには反時計周りで頂点が格納されていることを期待する
// 頂点が直線上に並ぶのは許容
bool isConvex(const Polygon &poly) {
    REP(i, SIZE(poly)) {
        if (ccw(prev(poly, i), curr(poly, i), next(poly, i)) == -1)
            return false;
    }
    return true;
}

// polyは凸であることを期待
// 0: OUT
// 1: ON
// 2: IN
// not verified
enum { OUT, ON, IN };
int convexContains(const Polygon &poly, const P &p) {
  const int n = poly.size();
  P g = (poly[0] + poly[n/3] + poly[2*n/3]) / 3.0; // inner-P
  int a = 0, b = n;
  while (a+1 < b) { // invariant: c is in fan g-poly[a]-poly[b]
    int c = (a + b) / 2;
    if (cross(poly[a]-g, poly[c]-g) > 0) { // angle < 180 deg
      if (cross(poly[a]-g, p-g) > 0 && cross(poly[c]-g, p-g) < 0) b = c;
      else                                                  a = c;
    } else {
      if (cross(poly[a]-g, p-g) < 0 && cross(poly[c]-g, p-g) > 0) a = c;
      else                                                  b = c;
    }
  }
  b %= n;
  if (cross(poly[a] - p, poly[b] - p) < 0) return OUT;
  if (cross(poly[a] - p, poly[b] - p) > 0) return IN;
  return ON;
}

// polyは凸でなくてよい
// 0: OUT
// 1: ON
// 2: IN
int contains(const Polygon& poly, const P& p) {
    bool in = false;
    REP(i, SIZE(poly)) {
        P a = curr(poly,i) - p, b = next(poly,i) - p;
        if (imag(a) > imag(b)) swap(a, b);
        if (imag(a) <= 0 && 0 < imag(b))
            if (cross(a, b) < 0) in = !in;
        if (cross(a, b) == 0 && dot(a, b) <= 0) return ON;
    }
    return in ? IN : OUT;
}


int main(){
    int N;
    cin >> N;
    Polygon poly;
    REP(n, N) {
        double x, y;
        cin >> x >> y;
        poly.pb( P(x,y) );
    }

    int Q;
    cin >> Q;
    REP(q, Q) {
        double x, y;
        cin >> x >> y;
        cout << contains(poly, P(x,y)) << endl;
    }

    return 0;
}
