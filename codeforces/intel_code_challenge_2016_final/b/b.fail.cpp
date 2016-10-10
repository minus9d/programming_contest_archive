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

int N, M;

bool ok1(vector<vector<int>>& cells)
{
    vector<int> gt(M);
    REP(m,M) gt[m] = m + 1;
    REP(n,N) {
        int err = 0;
        REP(m,M) err += (gt[m] != cells[n][m]);
        if (err != 0 && err != 2) return false;
    }
    return true;
}

void swapij(vector<vector<int>>& cells, int i, int j)
{
    REP(n,N) {
        swap(cells[n][i], cells[n][j]);
    }
}

bool ok2(vector<vector<int>>& cells, int i, int j)
{
    vector<int> gt(M);
    REP(m,M) gt[m] = m + 1;
    REP(n,N) {
        int err = 0;
        set<int> err_loc;
        REP(m,M) {
            if (gt[m] != cells[n][m]) {
                err_loc.insert(m);
                ++err;
            }
        }

        if (err == 0 || err == 2) {
            continue;
        }
        
        if (err == 3) {
            if (err_loc.count(i) && err_loc.count(j)) continue;
        }
        
        return false;
    }
    return true;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> M;

    vector<vector<int>> cells(N,vector<int>(M));

    REP(n,N) {
        REP(m,M) {
            cin >> cells[n][m];
        }
    }
    
    auto cells2 = cells;
    if (ok1(cells2)) {
        cout << "YES" << endl;
        return 0;
    }
    
    REP(i,M-1) {
        FOR(j,i+1,M) {
            auto cells3 = cells;
            swapij(cells3, i, j);
            if (ok2(cells3, i, j)) {
                cout << "YES" << endl;
                return 0;
            }
        }
    }

    cout << "NO" << endl;
    return 0;
}

