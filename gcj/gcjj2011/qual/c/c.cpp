#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

using namespace std;
typedef map<int, int> cards_t;


int retMax(int a, int b){
  return (a < b) ? b : a;
}
  
void solve(void)
{
  static int qNo = 1;
  long long int N;
  // cin >> N;
  scanf("%lld", &N);
  
  int bestOn = 0;
  int bestOff = 0;
  int ans = 0;

  bool kuriagariFlag = false;
  
  while(N) {
    int binary = N % 2;
    //    printf("%d\n", binary);

    if (N == 1) {
      ans = retMax(bestOn, bestOff + 1);
      break;
    }
    else {
      if (binary == 0) {
	if (kuriagariFlag) {
	  bestOn = retMax(bestOn + 1, bestOff + 2);
	}
	else {
	  bestOn = bestOff + 2;
	}
	kuriagariFlag = true;
      }
      else {
	if (kuriagariFlag) {
	  bestOn += 2;
	  bestOff = (bestOn, bestOff + 1);
	}
	else {
	  bestOff = bestOff + 1;
	}
      }
    }

    // printf("(on, off) = (%d, %d)\n", bestOn, bestOff);

    N = N / 2;
  }
  // printf("\n");

  printf("Case #%d: %d\n", qNo++, ans);
}

int main(void)
{
  int T;
  int t;
  scanf("%d", &T);
  
  for(t = 0; t < T; t++) {
    solve();
  }
}
