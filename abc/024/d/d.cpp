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

#define MOD 1000000007

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    
    int SIZE = 100;

    vector<vector<int>> cell(SIZE, vector<int>(SIZE));

    // とりあえず100x100分出力してみる
    REP(j,SIZE) {
        REP(i,SIZE) {
            if (j == 0) {
                cell[j][i] = 1;
            }
            else if (i == 0) {
                cell[j][i] = 1;
            }
            else {
                cell[j][i] = (cell[j][i-1] + cell[j-1][i]) % MOD;
            }
        }
    }

    REP(j,SIZE) {
        REP(i,SIZE) {
            cout << cell[SIZE-1-j][i] << ",";
        }
        cout << endl;
    }


    int ret = 0;
    cout << ret << endl;

    return 0;
}

