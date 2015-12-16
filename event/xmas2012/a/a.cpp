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

int ok[6][6][6];

int main(void)
{
  int N;
  cin >> N;

  int pattern[6][5] = {{2,3,5,4}, {1,4,6,3}, {2,6,5,1},
		       {1,5,6,2}, {1,3,6,4}, {2,4,5,3}};
  for(int i = 0; i < 6; ++i){
    for(int j = 0; j < 4; ++j){
      ok[i+1][pattern[i][j]][pattern[i][(j+1)%4]] = 1;
    }
  }
  
  for(int n = 0; n < N; ++n){
    int a[6];
    for(int i = 0; i < 6; ++i){
      cin >> a[i];
    }
    if (a[0] + a[3] != 7 || a[1] + a[4] != 7 || a[2] + a[5] != 7){
      cout << "NO" << endl;
    }
    else{
      if (ok[a[2]][a[0]][a[1]]){
	cout << "YES" << endl;
      }
      else{
	cout << "NO" << endl;
      }
    }
  }
  
  return 0;
}
