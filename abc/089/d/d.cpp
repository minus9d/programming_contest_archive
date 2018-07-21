#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
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

vector<pair<int,int>> hws(90001);

int dist(int a, int b) {
    int h1, w1, h2, w2;
    tie(h1, w1) = hws[a];
    tie(h2, w2) = hws[b];
    // printf("dist of %d and %d is %d\n", a, b, abs(h1 - h2) + abs(w1 - w2));
    return abs(h1 - h2) + abs(w1 - w2);
    
}

int main(void)
{
    cin.sync_with_stdio(false);
    int H, W, D;
    cin  >> H >> W >> D;

    REP(h, H) {
        REP(w, W) {
            int a;
            cin >> a;
            hws[a] = mp(h, w);
        }
    }
    
    map<int, map<int, int>> table;

    FOR(start, 1, 1 + D) {
        table[start][start] = 0;
        int to = start + D;
        while (to <= 300*300+1) {
            table[start][to]
                = table[start][to - D]
                + dist(to, to - D);
            // printf("table[%d][%d] = %d\n", start, to, table[start][to]);
            to += D;
        }
    }

    int Q;
    cin >> Q;
    REP(q, Q) {
        int l, r;
        cin >> l >> r;
        auto base = l % D;
        if (base == 0) base += D;
        cout << (table[base][r] - table[base][l]) << endl;
    }

    return 0;
}
