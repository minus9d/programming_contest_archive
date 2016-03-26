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
    int N, Q;
    cin >> N >> Q;
    vector<int> rev(N+1);
    REP(q,Q){
        int l, r;
        cin >> l >> r;
        rev[l-1]++;
        rev[r]++;
    }

    string ans = "";
    bool black = true;
    REP(n,N){
        if (rev[n] % 2) black = !black;
        if (black) ans += '0';
        else ans += '1';
    }
    cout << ans << endl;

    return 0;
}
