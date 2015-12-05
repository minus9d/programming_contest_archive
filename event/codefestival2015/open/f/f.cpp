#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <numeric>
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
    int N;
    cin >> N;

    vector<vector<int>> edges(N);
    int edge_to_v0;

    REP(n,N-1) {
        int s, t;
        cin >> s >> t;
        --s; --t;
        edges[s].pb(t);
        edges[t].pb(s);
    }


    //printf("size:%d\n",SIZE(edges[0]));
    //for(auto e: edges[0]) {
    //    cout << "  " << e << endl;
    //}

    char ans;
    if (SIZE(edges[0]) == 1) {
        ans = 'A';
    }
    else {
        ans = ((N % 2) ? 'B' : 'A');
    }

    cout << ans << endl;

    return 0;
}
