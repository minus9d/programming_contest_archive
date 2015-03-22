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

struct P{
    int w;
    int h;
};

int main(void)
{
    int H, W, T;
    cin >> H >> W >> T;
    vector<string> cells(H);
    REP(h,H){
        cin >> cells[h];
    }

    P start;
    P goal;
    REP(h,H){
        REP(w,W){
            if (cells[h][w] == 'S'){
                start.h = h;
                start.w = w;
            }
            else if (cells[h][w] == 'G'){
                goal.h = h;
                goal.w = w;
            }
        }
    }

    for(int hOS = -10; hOS <= 10; ++hOS){
        
    }

    
    
    int ret = 0;
    cout << ret << endl;

    return 0;
}

Process flymake-proc segmentation fault (core dumped)
