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

// cost, x, y, floor
typedef tuple<int,int,int,int> P;
// x, y, floor
set<tuple<int,int,int>> seen;

int main(void)
{
    cin.sync_with_stdio(false);
    int N, R, C;
    cin >> N >> R >> C;
    
    vector<vector<string>> cells(N, vector<string>(R));
    REP(n,N){
        REP(r,R){
            cin >> cells[n][r];
        }
    }

    priority_queue<P, vector<P>, greater<P> > que;
    que.push(P(0, 0, 0, 0));

    int dx[] = {0,1};
    int dy[] = {1,0};
    while(!que.empty()){
        int cost, x, y, floor;
        std::tie(cost,x,y,floor) = que.top();
        que.pop();

        seen.insert(make_tuple(x,y,floor));

        if (floor == N-1 && x == C-1 && y == R-1) {
            cout << cost << endl;
            return 0;
        }
        REP(d,2) {
            auto x2 = x + dx[d];
            auto y2 = y + dy[d];
            if (x2 < 0 || x2 >= C || y2 < 0 || y2 >= R) continue;
            if (cells[floor][y][x] == 'H') {
                ++floor;
            }
            if (floor >= N) continue;
            if (seen.count(make_tuple(x2,y2,floor))) continue;
            que.push(P(cost + cells[floor][y][x] - '0', x2, y2, floor));
        }
    }
    
    return 0;
}
