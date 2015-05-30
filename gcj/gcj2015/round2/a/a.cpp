#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>
#include <complex>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

const string imp = "IMPOSSIBLE";

bool isArrow(char ch) {
    return (ch == '^' || ch == 'v' || ch == '<' || ch == '>');
}


/// @retval 0:  no pair
/// @ratval 1:  has pair but need to change direction
/// @retval 2:  ok
int examinePair(vector<string>& cell, int r, int c)
{
	int dc = 0;
	int dr = 0;
	if (cell[r][c] == '^') dr = -1;
	else if (cell[r][c] == 'v') dr = +1;
	else if (cell[r][c] == '>') dc = +1;
	else if (cell[r][c] == '<') dc = -1;

	int R = cell.size();
	int C = cell[0].size();

	bool hasPair = false;
	bool alreadyOk = false;
	int r2 = r + dr;
	int c2 = c + dc;
	while (0 <= r2 && r2 <= R - 1 && 0 <= c2 && c2 <= C - 1)
	{
		if (isArrow(cell[r2][c2])) {
			return 2;
		}
		r2 += dr;
		c2 += dc;
	}

	int drs[] = { 1, -1, 0, 0 };
	int dcs[] = { 0, 0, 1, -1 };
	REP(d, 4) {
		int r2 = r + drs[d];
		int c2 = c + dcs[d];
		while (0 <= r2 && r2 <= R - 1 && 0 <= c2 && c2 <= C - 1)
		{
			if (isArrow(cell[r2][c2])) {
				return 1;
			}
			r2 += drs[d];
			c2 += dcs[d];
		}
	}

	return 0;
}

void solve(void)
{
    int R, C;
    cin >> R >> C;

    vector<string> cell(R);
    REP(r, R) cin >> cell[r];

	int ans = 0;
    REP(r, R) {
        REP(c, C) {
            if (isArrow(cell[r][c])) {
				auto ret = examinePair(cell, r, c);
				//cout << "ret: " << ret << endl;
				if (ret == 2) continue;
				else if (ret == 1) ++ans;
				else {
					cout << imp;
					return;
				}
            }
        }
    }
	cout << ans;
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": ";
        solve();
        cout << endl;
    }

    return 0;
}
