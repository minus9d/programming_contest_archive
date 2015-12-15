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
#define mt make_tuple

// can't use y1!!
int X1,Y1,X2,Y2;
int vmax, T;
int vx, vy, wx, wy;

bool Check(double t)
{
    double x = X1;
    double y = Y1;

    x += (double)(min((double)T, t) * vx);
    y += (double)(min((double)T, t) * vy);
    if (t > T) {
        x += (double)(t - T) * wx;
        y += (double)(t - T) * wy;
    }

    double dist = hypot( X2 - x, Y2 - y );
    // cout << "(x,y) = " << x << "," << y << endl;
    // cout << "dist = " << dist << endl;
    // cout << "possible move = " << vmax * t << endl;
    return (dist <= vmax * t);
}

int main(void)
{
    cin >> X1 >> Y1 >> X2 >> Y2;
    cin >> vmax >> T;
    cin >> vx >> vy >> wx >> wy;
    
    double lo = 0.0;
    double hi = 1e12;
    
    REP(repeat, 1e6)  {
        double k = (lo + hi) / 2.0;
        // cout << "lo,hi,k: " << lo << ", " << hi << ", " << k << endl;
        if (Check(k))
            hi = k;
        else
            lo = k;
    }
    
    printf("%.16lf\n", (lo + hi) / 2.0);

    return 0;
}
