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

typedef pair<int,int> P;

int main(void)
{
    cin.sync_with_stdio(false);
    int H, W;
    cin >> H >> W;
    vector<vector<char>> cells(H, vector<char>(W));
    
    P start;
    P goal;
    REP(h,H) {
        REP(w,W){
            cin >> cells[h][w];
            if (cells[h][w] == 's') start = mp(w,h);
            if (cells[h][w] == 'g') goal = mp(w,h);
        }
    }

    set<P> seen;
    queue<P> q;
    q.push(start);

    while(!q.empty()) {
        P pop = q.front(); q.pop();
        seen.insert(pop);
        
        if (pop == goal) {
            cout << "Yes" << endl;
            return 0;
        }

        int dx[] = {0,0,1,-1};
        int dy[] = {1,-1,0,0};
        REP(d,4) {
            int x = pop.first + dx[d];
            int y = pop.second + dy[d];
            if (x < 0 || x > W-1 || y < 0 || y > H-1) continue;
            if (cells[y][x] == '#') continue;

            P nxt = mp(x,y);
            if (seen.count(nxt)) continue;
            q.push(nxt);
        }
    }
    
    cout << "No" << endl;
    return 0;
}


