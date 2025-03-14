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
    int H, W, K;
    cin >> H >> W >> K;
    vector<vector<int>> cells(H, vector<int>(W));
    REP(h,H) {
        string s;
        cin >> s;
        REP(w,W) {
            cells[h][w] = s[w] - '0';
        }
    }

    cout << 300 << endl;
    REP(h,H) {
        REP(i,48) {
            printf("%d %d\n", h+1, i+1);
        }
    }

    return 0;
}

