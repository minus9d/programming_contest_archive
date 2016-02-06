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

struct P {
    int x;
    int y;
};

ll pow2(ll x) { return x*x; }

ll length(P& p1, P& p2) {
    return pow2((ll)p1.x - p2.x) + pow2((ll)p1.y - p2.y);
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> Xs(N);
    vector<int> Ys(N);
    REP(n,N) cin >> Xs[n] >> Ys[n];

    if (N > 100) return 0;

    int acute = 0;
    int obtuse = 0;
    int right = 0;
    
    REP(i,N-2) {
        P p1{Xs[i],Ys[i]};
        FOR(j,i+1,N-1) {
            P p2{Xs[j],Ys[j]};
            FOR(k,j+1,N) {
                P p3{Xs[k],Ys[k]};
                
                vector<ll> ls(3);
                ls[0] = length(p1,p2);
                ls[1] = length(p1,p3);
                ls[2] = length(p2,p3);
                sort(ALL(ls));
                
                if (ls[0] + ls[1] == ls[2]) {
                    ++right;
                }
                else if (ls[0] + ls[1] > ls[2]) {
                    ++acute;
                }
                else {
                    ++obtuse;
                }
            }
        }
    }

    printf("%d %d %d\n", acute, right,obtuse);

    return 0;
}
