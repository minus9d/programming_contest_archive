#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

int main(void)
{
    const double eps = 1e-9;
    string str;
    double a, b, c, d, e, f;
    while(cin >> a >> b >> c >> d >> e >> f){
        double delta = a * e - b * d;
        double x = 1.0 / delta * (c * e - b * f) + eps;
        double y = 1.0 / delta * (-d * c + a * f) + eps;
        printf("%.3f %.3f\n", x, y);
    }
    
    return 0;
}
