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

vector<string> cells(3);
int N, K;

map<pair<int,int>,bool> cache;

vector<string> makeCells(int heroX)
{
    int m = heroX * 2;
    vector<string> ret;
    auto len = SIZE(cells[0]);
    REP(i,3) {
        string s;
        REP(x,len) {
            int x2 = x + m;
            if (x2 >= len || cells[i][x2] == '.') s += '.';
            else s += cells[i][x2];
        }
        ret.pb(s);
    }
    return ret;
}

bool dfs(int heroX, int heroY) {
    if (cache.count( mp(heroX, heroY) )) return cache[mp(heroX, heroY)];
    
    auto currCells = makeCells(heroX);

    // debug
    //cout << "x,y = " << heroX << "," << heroY << endl;
    //REP(i,3) cout << currCells[i] << endl;
    //cout << endl;
    

    if (currCells[heroY][heroX] != '.') return false;

    if (heroX >= (N + 1) / 2) return true;

    if (currCells[heroY][heroX+1] != '.') return false;

    auto res = false;
    if (heroY != 0 && currCells[heroY-1][heroX+1] == '.') {
        auto tmp = dfs(heroX+1, heroY-1);
        res |= tmp;
    }
	if (heroY != 2 && currCells[heroY + 1][heroX + 1] == '.') {
        auto tmp = dfs(heroX+1, heroY+1);
        res |= tmp;
    }
    auto tmp = dfs(heroX+1, heroY);
    res |= tmp;

    cache[mp(heroX, heroY)] = res;

    return res;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;

    REP(t,T) {
        cache.clear();

        cin >> N >> K;
        REP(i,3) cin >> cells[i];

        // find s and delete it
        int initY = -1;
        REP(i,3) {
            if (cells[i][0] == 's') {
                initY = i;
                cells[i][0] = '.';
            }
        }

        auto res = dfs(0, initY);
        if (res) cout << "YES";
        else cout << "NO";
        cout << endl;
    }

    return 0;
}
