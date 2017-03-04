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
    int H, W, K, sr, sc;
    cin >> H >> W >> K >> sr >> sc;
    --sr; --sc;

    vector<string> cells(H);
    REP(h,H) cin >> cells[h];
    int N;
    cin >> N;
    REP(n, N) {
        int r, c, f, d;
        cin >> r >> c >> f >> d;
    }

    string marks = "UDLR-";
    REP(k, K) {
        cout << marks[rand()%5];
    }
    cout << endl;

    return 0;
}
