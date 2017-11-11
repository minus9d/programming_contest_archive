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
    int N;
    cin >> N;
    vector<int> A(N);
    vector<int> B(N);
    vector<int> C(N);
    REP(n,N) cin >> A[n];
    REP(n,N) cin >> B[n];
    REP(n,N) cin >> C[n];
    sort(ALL(A));
    sort(ALL(B));
    sort(ALL(C));
    
    vector<int> Bans(N);
    REP(i, N){
      auto b = B[i];
      auto idx = upper_bound(ALL(C), b);
      auto lower = idx - C.begin();
      Bans[i] = N - lower;
      // printf("b, ans = %d, %d\n", b, Bans[i]);
    }
 
    vector<ll> acc(N);
    ll s = 0;
    for(int i = N-1; i >= 0; --i) {
      s += Bans[i];
      acc[i] = s;
    }
 
    ll ans = 0;
    REP(i, N){
      auto a = A[i];
      auto idx = upper_bound(ALL(B), a) - B.begin();
      if (idx <= N - 1) {
	ans += acc[idx];
      }
    }
    cout << ans << endl;
    return 0;
}
