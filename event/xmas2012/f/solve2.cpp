#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;
typedef long long ll;
const int MOD = 20121224;

ll pow2(ll n){
  return n*n;
}


ll count_validx(int M, int X, ll remain){
  ll ret = 0;
  int x_init = X/M;
  for(int x = 0; x <= 1000; ++x){

    bool toobig = true;

    for(int rev = 0; rev < 2; ++rev){

      if (x == 0 && rev == 1) continue;
      
      int x2 = rev ? x_init+x : x_init-x;
      ll tmp = pow2(M * x2 - X);

      if (remain == tmp){
	printf("  ok!  x = %d\n", x2);
	++ret;
	toobig = false;
      }
      else if (remain > tmp){
	toobig = false;
      }


      
      if (toobig){
	break;
      }
    }
  }
  return ret;
}



int main(void)
{
  int T;
  cin >> T;
  for(int t = 0; t < T; ++t){
    int M, X, Y, N;
    cin >> M >> X >> Y >> N;
    ll r2 = 1;
    for(int i = 0; i < N; ++i){
      int P, E;
      cin >> P >> E;
      for(int e = 0; e < E; ++e){
	r2 *= P;
      }
    }

    printf("(My - Y)^2 + (Mx - X)^2 = r2\n");
    printf("(%d * y - %d)^2 + (%d * x - %d)^2 = %lld\n", M, Y, M, X, r2);


    ll ret = 0;
    int y_init = Y/M;
    for(int y = 0; y <= 10; ++y){

      bool toobig = true;
      for(int rev = 0; rev < 2; ++rev){
	int y2 = rev ? y_init + y : y_init-y;

	if (y == 0 && rev == 1) continue;
	
	cout << "y = " << y2 << endl;
	
	ll sum = pow2(M * y2 - Y);
	if (sum <= r2){
	  ret += count_validx(M, X, (r2-sum));
	  toobig = false;
	}
      }

      if (toobig) break;
    }
    cout << ret << endl;
  }

  return 0;
}
