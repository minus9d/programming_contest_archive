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

double a, b, c;
const double pi = acos(-1);
double val(double t) {
    return a * t + b * sin(c * t * pi) - 100;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> a >> b >> c;

    double l = 1e-9;
    double u = 1e4;

    int cnt = 0;
    while (abs(val(l)) > 1e-10 && cnt < 1e7) {
        double mid = (l + u) / 2;
        // printf("l,u,mid = %lf,%lf,%lf\n",
        //        l,u,mid);
        // printf("val(l), val(u), val(mid) = %lf,%lf,%lf\n",
        //        val(l), val(u), val(mid));

        if (val(mid) >= 0)
            u = mid;
        else
            l = mid;
        ++cnt;
    }
    
    printf("%.10lf\n", l);

    // printf("val = %lf\n", val(l));
    
    return 0;
}
