#include <iostream>
#include <complex>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

typedef complex<double> P;

double dot(const P& a, const P& b) {
    return real(conj(a)*b);
}

// 点p2を、点p0, p1を通る直線に射影した点
P projection(const P& p0, const P& p1, const P& p2) {
    // 位置ベクトルに直す
    P vec1 = p1 - p0;
    P vec2 = p2 - p0;
    return p0 + vec1 * dot(vec1, vec2) / dot(vec1, vec1);
}

int main(){
    double x, y;

    // 直線の始点と終点
    cin >> x >> y;
    P p0(x, y);
    cin >> x >> y;
    P p1(x, y);

    int Q;
    cin >> Q;
    REP(q, Q) {
        cin >> x >> y;
        P p2(x, y);
        P ret = projection(p0, p1, p2);
        printf("%.10lf %.10lf\n", ret.real(), ret.imag());
    }
    
    return 0;
}
