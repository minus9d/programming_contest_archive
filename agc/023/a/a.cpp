#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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

ll faster(int N, vector<ll>& As) {
  vector<ll> table(N+1);
  map<ll, ll> seen;
  seen[0] = 1;
  ll ans = 0;
  REP(n,N) {
    table[n+1] = table[n] + As[n];
    ans += seen[table[n+1]];
    seen[table[n+1]]++;
//    cout << "n, ans = " << n << "," << ans << endl;
  }
  return ans;
}


int main(void) {
  int N; cin >> N;
  vector<ll> As(N);
  REP(n,N) cin >> As[n];

  auto ans = faster(N, As);
  cout << ans << endl;

  return 0;
}
