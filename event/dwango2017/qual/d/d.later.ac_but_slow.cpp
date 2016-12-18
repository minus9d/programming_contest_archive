#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <climits>
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
    int N,M;
    cin >> N >> M;
 
    vector<int> X(N);
    vector<int> Y(N);
    REP(n,N) {
        cin >> X[n] >> Y[n];
    }
 
    if (M >= N) {
        ll ans = accumulate(ALL(X), 0LL);
        cout << ans << endl;
        return 0;
    }
 
    // take initial M
    vector<pair<int,int>> bonus;
    REP(m,M-1){
        bonus.pb(mp(Y[m]-X[m], m));
    }
    sort(ALL(bonus));
 
    ll curr_sum = 0;
    REP(m,M-1){
        curr_sum += X[m];
    }
 
    ll ans = curr_sum + X[M-1];
    FOR(m, M-1, N-1) {
        auto element = mp(Y[m]-X[m], m);
        auto it = lower_bound(ALL(bonus), element);
        auto idx = it - bonus.begin();
        if (idx < M - 1) {
            int del_idx = bonus[M-2].second;
            curr_sum -= X[del_idx];
            curr_sum += Y[del_idx];
            curr_sum += X[m];
        }
        else {
            curr_sum += Y[m];
        }
        bonus.insert(it, element);
        ans = max(ans, curr_sum + X[m+1]);
        bonus.pop_back();
 
        // cout << "ans:" << ans << endl;
    }
    cout << ans << endl;
 
    return 0;
}
