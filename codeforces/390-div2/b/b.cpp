#include <iostream>
#include <sstream>
#include <string>
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

vector<string> cells(4);

char check2(int i, int j){
    if (i < 0 || i >= 4 || j < 0 || j >= 4) return 'z';
    return cells[j][i];
}

bool check(int i, int j, int dx, int dy) {
    return
        (check2(i,j) == 'x'
         && check2(i+dx,j+dy) == 'x'
         && check2(i+dx*2,j+dy*2) == '.')
        ||
        (check2(i,j) == '.'
         && check2(i+dx,j+dy) == 'x'
         &&  check2(i+dx*2,j+dy*2) == 'x')
        ||
        (check2(i,j) == 'x'
         && check2(i+dx,j+dy) == '.'
         &&  check2(i+dx*2,j+dy*2) == 'x')
        ;
}

int main(void)
{
    cin.sync_with_stdio(false);
    REP(n,4) cin >> cells[n];
    
    bool ans = false;
    REP(i,4){
        REP(j,4) {
            if (check(i,j,1,0) || check(i,j,0,1) ||
                check(i,j,1,1) || check(i,j,-1,1)) {
                ans = true;
                break;
            }
        }
    }
    cout << (ans ? "YES" : "NO") << endl;

    return 0;
}
