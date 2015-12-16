#include <cstdio>

typedef long long ll;

long long count(int M){
  return 23;
}

ll pow2(ll n){
  return n*n;
}


ll count(int M, int X, ll remain){
  ll ret = 0;
  int x_init = X/M;
  for(int x = 0; ; ++x){
    bool toobig = true;
    ll sum = 0;

    for(int rev = 0; rev < 2; ++rev){
      int x2 = rev ? x_init+x : x_init-x;
      int tmp = pow2(M * x2 - X);
      if (remain == tmp){
	++ret;
      }
      else if (remain > tmp){
	toobig = false;
      }

      if (toobig){
	return ret;
      }
    }
  }

  return 0;
}

int main(){
  long long aa = count(1212, 222, 111);
  
  return 0;
}
  
