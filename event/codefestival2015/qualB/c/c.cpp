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
    int N,M;
    cin >> N >> M;

    vector<int> As(N);
    vector<int> Bs(M);
    REP(n,N) cin >> As[n];
    REP(m,M) cin >> Bs[m];

    sort(ALL(As));
    sort(ALL(Bs));

    int a = 0;
    bool fail = false;
    for(auto b : Bs) {
        while(1) {
            if (a == N) {
                fail = true;
                break;
            }

            int room = As[a];
            if (room >= b) {
                ++a;
                break;
            }
            else {
                ++a;
            }
        }
    }
    
    cout << ((fail)?"NO":"YES") << endl; 

    return 0;
}
