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
 
int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<set<int>> edges(N);
    REP(m,M) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        edges[a].insert(b);
        edges[b].insert(a);
    }
    vector<int> order(N-1);
    REP(n,N-1) order[n] = n+1;
    int ans = 0;
    do {
        int cur = 0;
        bool ok = true;
        for(auto e: order) {
            if (edges[cur].count(e)) {
                cur = e;
            }
            else {
                ok = false;
                break;
            }
        }
        ans += ok;
    } while(next_permutation(ALL(order)));
    cout << ans << endl;
    
    return 0;
}
