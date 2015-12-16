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


int H, W, P, Q, B;

// rabit*2, bugget*2
bool visit[12][12][12][12];

int dp[] = {0, 0, 1, -1};
int dq[] = {1, -1, 0, 0};


bool debug_print(int P, int Q, vector<string> &cell, int R, int S){
  printf("----\n");
  printf("() = rabbit, [] = buggage\n");
  for(int i = 0; i < H; ++i){
    for(int j = 0; j < W; ++j){
      if (i == P && j == Q){
	cout << "(" << cell[i][j] << ")";
      }
      else if (i == R && j == S){
	cout << "[" << cell[i][j] << "]";
      }
      else{
	cout << " " << cell[i][j] << " ";	
      }
    }
    cout << endl;
  }
  printf("----\n");
}

  
bool canReach(int P, int Q, vector<string> &cell, int R, int S){
//  printf("P, Q, R, S = %d, %d, %d, %d\n", P, Q, R, S);
//  debug_print(P, Q, cell, R, S);
  
  if (cell[R][S] == '!'){
    return true;
  }

  if (visit[P][Q][R][S])
    return false;
  
  visit[P][Q][R][S] = true;
  
  bool ans = false;
  for(int d = 0; d < 4; ++d){
    int P2 = P+dp[d];
    int Q2 = Q+dq[d];

    if (P2 >= H || P2 < 0 || Q2 >= W || Q2 < 0){
	continue;
    }
    if (P2 == R && Q2 == S){
      continue;
    }
    if (cell[P2][Q2] == '#'){
      continue;
    }
    if (!visit[P2][Q2][R][S]){
      ans = ans || canReach(P2, Q2, cell, R, S);
    }
  }

  for(int d = 0; d < 4; ++d){
    int P2 = P+dp[d];
    int Q2 = Q+dq[d];
    if (P2 == R && Q2 == S){
      for(int i = 0; i < H; ++i){
	for(int j = 0; j < W; ++j){

	  if (cell[i][j] == '#')
	    continue;
	  if (i == P && j == Q)
	    continue;
	  
	  ans = ans || canReach(P, Q, cell, i, j);
	}
      }
    }
  }
  
  return ans;
}


int main(void)
{
  int T;
  cin >> T;

  for(int t = 0; t < T; ++t){
    memset(visit, 0, sizeof(visit));

    cin >> H >> W >> P >> Q >> B;
    --P;
    --Q;

    vector<int> R(B);
    vector<int> S(B);
    for(int i = 0; i < B; ++i){
      cin >> R[i] >> S[i];
      --R[i];
      --S[i];
    }

    vector<string>cell(H);
    for(int i = 0; i < H; ++i){
      cin >> cell[i];
    }

    if (cell[R[0]][S[0]] == '!'){
      cout << "YES" << endl;
      continue;
    }

    // can the rabbit reach a bugget?
    if (canReach(P, Q, cell, R[0], S[0])){
      cout << "YES" << endl;
    }
    else{
      cout << "NO" << endl;
    }
  }

  return 0;
}
