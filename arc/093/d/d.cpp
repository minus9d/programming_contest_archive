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

int main(void)
{
    cin.sync_with_stdio(false);
    int A, B;
    cin >> A >> B;

    vector<vector<char>> ans(100, vector<char>(100, '#'));
    REP(h, 50) {
        REP(w, 100) {
            ans[h][w] = '.';
        }
    }

    --A; --B;
    // black
    int h = 1;
    int w = 1;
    REP(b, B) {
        ans[h][w] = '#';
        w += 2;
        if (w >= 99) {
            w = 1;
            h += 2;
        }
    }

    // white
    h = 51;
    w = 1;
    REP(a, A) {
        ans[h][w] = '.';
        w += 2;
        if (w >= 99) {
            w = 1;
            h += 2;
        }
    }

    cout << "100 100" << endl;
    REP(h, 100) {
        REP(w, 100) {
            cout << ans[h][w];
        }
        cout << endl;
    }

    return 0;
}
