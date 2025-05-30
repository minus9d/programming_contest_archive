#include <iostream>
#include <complex>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

typedef complex<double> P;

struct L : public vector<P> {
  L(const P &a, const P &b) {
    push_back(a); push_back(b);
  }
};

// 内積
double dot(const P& a, const P& b) {
    return real(conj(a)*b);
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

// // 原点と点Pとのユークリッド距離
// double norm(const P& a, const P& b) {
//     return dot(
//     return real(conj(a)*b);
// }

int main(){
    int Q;
    cin >> Q;
    REP(q, Q) {
        double x0, y0, x1, y1, x2, y2, x3, y3;
        cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        P p0(x0, y0);
        P p1(x1, y1);
        P p2(x2, y2);
        P p3(x3, y3);
        L l0(p0, p1);
        L l1(p2, p3);
        if (is_parallel(l0, l1)) {
            cout << 2 << endl;
        }
        else if (is_ortho(l0, l1)) {
            cout << 1 << endl;
        }
        else {
            cout << 0 << endl;
        }
    }
    return 0;
}
