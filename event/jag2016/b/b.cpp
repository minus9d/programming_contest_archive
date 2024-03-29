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

int main(void)
{
    cin.sync_with_stdio(false);
    int N,M,T;
    cin >> N >> M >> T;
    
    vector<int> time(T);
    REP(n,N) {
        int a;
        cin >> a;
        FOR(i, max(0,a-M), min(a+M,T)) {
            time[i]++;
        }
    }

    int ans = 0;
    REP(t,T) {
        ans += (time[t] == 0);
    }

    cout << ans << endl;

    return 0;
}
