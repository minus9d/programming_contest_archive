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

int main(void)
{
    cin.sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;

    vector<vector<int>> cell(N,vector<int>(N));
    
    REP(q,Q) {
        int type;
        cin >> type;
        int a,b,c,d;
        if (type == 3) {
            cin >> a >> b >> c >> d;
        }
        else {
            cin >> a >> b >> c;
        }

        if (type == 1) {
            REP(x,N) {
                REP(y,N) {
                    int n = x + y;
                    if (a <= n && n <= b) cell[x][y] += c;
                }
            }
        }
        else if (type == 2) {
            REP(x,N) {
                REP(y,N) {
                    int n = x - y;
                    if (a <= n && n <= b) cell[x][y] += c;
                }
            }
        }
        else {
            int mx = -1e9;
            int num = 0;
            FOR(y,c,d+1) {
                FOR(x,a,b+1) {
                    auto e = cell[x][y];
                    if (e == mx) {
                        ++num;
                    }
                    else if (e > mx) {
                        num = 1;
                        mx = e;
                    }
                }
            }
            cout << mx << " " << num << endl;
        }
    }


    return 0;
}
