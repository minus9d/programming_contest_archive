#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair


pair<int, int> need_num(int A, int N){
    int rep = 0;
    while(A <= N){
        //cout << "A, N = " << A << ", " << N << endl;
        A = A + A - 1;
        ++rep;
    }
    return mp(A, rep);
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        int A, N;
        cin >> A >> N;
        vector<int> motes(N);
        REP(i,N){
            cin >> motes[i];
        }

        if (A == 1){
            cout << "Case #" << (test+1) << ": " << N << endl;
            continue;
        }

        sort(ALL(motes));

        const int R = 1000;

        //vector< vector<ll>((ll)(1e6+1)) > dp;
        //int dp[int(1e6+1)][int(1e4+1)];
        vector< vector<int> > dp(100001, vector<int>(R+1));


        REP(i,N){
            //cout << "i: " << i << endl;
            if (i == 0){
                if (motes[i] < A){
                    dp[0][0] = A + motes[i];
                }
                else {
                    dp[0][1] = A;

                    pair<int, int> p = need_num(A, motes[i]);
                    dp[0][p.second] = max(dp[0][p.second], p.first + motes[i]);

                    //printf("a dp[0][1] = %d\n", dp[0][1]);
                    //printf("a dp[0][%d] = %d\n", p.second, dp[0][p.second]);
                }
            }
            else{
                REP(j, R){
                    if (dp[i-1][j]){
                        int prev = dp[i-1][j];
                        //cout << "prev = " << prev << endl;
                        if (motes[i] < prev){
                            dp[i][j] = dp[i-1][j] + motes[i];
                            //printf("1 dp[%d][%d] = %d\n", i, j, dp[i][j]);
                        }
                        else{
                            dp[i][j+1] = max(dp[i][j+1], dp[i-1][j]);
                            pair<int, int> p = need_num(prev, motes[i]);
                            dp[i][j + p.second] = max(dp[i][j + p.second], p.first + motes[i]);

                            //printf("2 dp[%d][%d] = %d\n", i, j+1, dp[i][j+1]);
                            //printf("2 dp[%d][%d] = %d\n", i, p.second, dp[i][p.second]);
                        }
                    }
                }
            }
        }

        int ans = 99999999;
        REP(j,R){
            if (dp[N-1][j] != 0){
                ans = min(ans, j);
            }
        }

        cout << "Case #" << (test+1) << ": " << ans << endl;
    }

    return 0;
}
