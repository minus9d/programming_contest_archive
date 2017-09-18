#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

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

void make_set(set<int>& water, int A, int B, int F, int mul) {
    int a = 0;
    while(1) {
        int aA = a * A;
        if (mul * aA > F) break;

        int b = 0;
        while(1) {
            int bB = b * B;
            if (mul * (aA + bB) > F) break;
            water.insert(aA + bB);
            b += 1;
        }

        a += 1;
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    int A, B, C, D, E, F;
    cin >> A >> B >> C >> D >> E >> F;

    set<int> water;
    set<int> sugar;
    make_set(water, A, B, F, 100);
    make_set(sugar, C, D, F, 1);

    double mx = -1.0;
    int ans_ws = 0;
    int ans_s = 0;
    for (auto w : water) {
        for (auto s : sugar) {
            if (E * w - s >= 0
                && w != 0
                && 100 * w + s <= F
                ) {
                double val = (double)s / w;
                if (val > mx) {
                    ans_ws = 100 * w + s;
                    ans_s = s;
                    mx = val;
                }
            }
        }
    }
    cout << ans_ws << " " << ans_s << endl;

    return 0;
}
