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

bool grad(int i, int j, int k) {
    if (i < j && j < k) return true;
    if (i > j && j > k) return true;
    return false;
}


bool ok(vector<vector<int>> cell, vector<int>& unseen) {
    int idx = 0;
    REP(j,5) REP(i,5) if (cell[j][i] == 0) cell[j][i] = unseen[idx++];
    REP(j,5) REP(i,3) {
        if (grad(cell[j][i], cell[j][i+1], cell[j][i+2])) return false;
        if (grad(cell[i][j], cell[i+1][j], cell[i+2][j])) return false;
    }
    return true;
}


int main(void)
{
    cin.sync_with_stdio(false);
    vector<vector<int>> cell(5, vector<int>(5));
    REP(i,5) REP(j,5) cin >> cell[i][j];

    set<int> seen;
    REP(j,5) REP(i,5) if (cell[j][i] != 0) seen.insert(cell[j][i]);
    
    if (seen.size() < 17) return 0;
    
    vector<int> unseen;
    REP(i,25) if (!seen.count(i+1)) unseen.pb(i+1);

    int ret = 0;
    do {
        if (ok(cell, unseen)) ++ret;
    } while(next_permutation(ALL(unseen)));

    cout << ret << endl;

    return 0;
}
