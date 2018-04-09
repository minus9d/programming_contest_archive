// 本番ではSmallしか通らなかった
// Small: 代数的に解いた
// Large: 二分探索で解いたつもりがWA

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <complex>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

typedef complex<double> P;
typedef vector<P> Polygon;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define curr(P, i) P[(i) % P.size()]
#define next(P, i) P[(i+1) % P.size()]
#define prev(P, i) P[(i+P.size()-1) % P.size()]
#define diff(P, i) (next(P, i) - curr(P, i))

#define pb push_back
#define mp make_pair
#define mt make_tuple


const double PI = acos(-1);


namespace std {
    bool operator < (const P& a, const P& b) {
        return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
    }
}

double dot(const P& a, const P& b) {
    return real(conj(a)*b);
}
double norm(const P& a) {
    return real(conj(a)*a);
}
double cross(const P& a, const P& b) {
    return imag(conj(a)*b);
}
int ccw(P a, P b, P c) {
    b -= a; c -= a;
    if (cross(b, c) > 0)   return +1;       // counter clockwise
    if (cross(b, c) < 0)   return -1;       // clockwise
    if (dot(b, c) < 0)     return +2;       // c--a--b on line
    if (norm(b) < norm(c)) return -2;       // a--b--c on line
    return 0;                               // a--c--b on line
}
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
double convexArea(const Polygon& poly) {
    double area = 0.0;
    REP(i, SIZE(poly))
        area += cross(curr(poly, i), next(poly, i));
    return abs(area) * 0.5;
}

tuple<double,double> rotate(double x, double y, double rad) {
    double new_x = x * cos(rad) - y * sin(rad);
    double new_y = x * sin(rad) + y * cos(rad);
    return mt(new_x, new_y);
}

void print_tuple(const tuple<double, double, double>& t) {
    cout << fixed << setprecision(20)
         << get<0>(t) << " "
         << get<1>(t) << " "
         << get<2>(t) << endl;
}

tuple<double, double, double> between(tuple<double, double, double>& t1,
                                      tuple<double, double, double>& t2) {
    return mt((get<0>(t1) + get<0>(t2)) / 2.0,
              (get<1>(t1) + get<1>(t2)) / 2.0,
              (get<2>(t1) + get<2>(t2)) / 2.0);
}

double find_rad(double A, double lo, double hi, vector<tuple<double, double, double>> Vs) {
    double mid = (lo + hi) / 2.0;
    REP(rep, 30000) {
        Polygon polygon;
        for(auto V: Vs) {
            double x, y, z;
            tie(x, y, z) = V;
            double new_z, new_y;
            tie(new_z, new_y) = rotate(z, y, mid);
            polygon.pb(P{x, new_z});
        }

        auto hull = convexHull(polygon);
        auto S = convexArea(hull);

        // cerr << "===" << endl;
        // cerr << "rad, S = " << mid << ", " << S << endl;
    
        if (S > A) {
            hi = mid;
        } else {
            lo = mid;
        }
        mid = (lo + hi) / 2.0;
    }
    return mid;
}

void solve() {
    double A;
    cin >> A;

    vector<tuple<double, double, double>> rotatedVs;

    if (A <= sqrt(2)) {
        double rad = -PI / 4.0 + asin(A / sqrt(2));
        vector<tuple<double, double, double>> Vs {
            {-0.5, 0.5, -0.5},
            {-0.5, 0.5, 0.5},
            {0.5, 0.5, -0.5},
            {0.5, 0.5, 0.5},
            {-0.5, -0.5, -0.5},
            {-0.5, -0.5, 0.5},
            {0.5, -0.5, -0.5},
            {0.5, -0.5, 0.5}
        };
        for(auto V: Vs) {
            double new_x, new_y;
            tie(new_x, new_y) = rotate(get<0>(V), get<1>(V), rad);
            rotatedVs.pb(mt(new_x, new_y, get<2>(V)));
        }
    }
    else {
        double v = 1.0 / sqrt(2);
        vector<tuple<double, double, double>> Vs {
            {-v, 0, -0.5},
            {-v, 0, 0.5},
            {0, v, -0.5},
            {0, v, 0.5},
            {0, -v, -0.5},
            {0, -v, 0.5},
            {v, 0, -0.5},
            {v, 0, 0.5}};
        double rad = find_rad(A, 0, PI / 4.0, Vs);
        for(auto V: Vs) {
            double x, y, z;
            tie(x, y, z) = V;
            double new_z, new_y;
            tie(new_z, new_y) = rotate(z, y, rad);
            rotatedVs.pb(mt(x, new_y, new_z));
        }
    }
    print_tuple(between(rotatedVs[2], rotatedVs[7]));
    print_tuple(between(rotatedVs[0], rotatedVs[3]));
    print_tuple(between(rotatedVs[1], rotatedVs[7]));
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ":" << endl;
        solve();
    }
    return 0;
}
