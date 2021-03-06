#include <iostream>
#include <complex>
#include <cstdio>
#include <map>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

typedef complex<double> P;

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

// // 原点と点Pとのユークリッド距離
// double norm(const P& a, const P& b) {
//     return dot(
//     return real(conj(a)*b);
// }

int main(){
    double x0, y0, x1, y1;
    int Q;

    cin >> x0 >> y0 >> x1 >> y1;
    
    P p0(x0, y0);
    P p1(x1, y1);

    cin >> Q;
    REP(q, Q) {
        double x2, y2;
        cin >> x2 >> y2;
        P p2(x2, y2);
        auto ret = ccw(p0, p1, p2);
        map<int, string> table{
            {+1, "COUNTER_CLOCKWISE"},
            {-1, "CLOCKWISE"},
            {+2, "ONLINE_BACK"},
            {-2, "ONLINE_FRONT"},
            {0, "ON_SEGMENT"}
        };
        cout << table[ret] << endl;
    }
}
