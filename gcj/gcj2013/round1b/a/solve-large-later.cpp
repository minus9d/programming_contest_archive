// Q. https://code.google.com/codejam/contest/2434486/dashboard#s=p0&a=0

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

        int ans = 1e7;

        // i番目以降は常にremoveする、というルールでループ
        REP(i, N+1){
            int times = 0;
            int mote = A;
            // シミュレーションする
            REP(j, N){
                // i番目以降はremove
                if (j >= i){
                    ++times;
                }
                // 0からi-1番目はabsorb
                else{
                    if (motes[j] < mote) {
                        mote += motes[j];
                    }
                    else{
                        while(1){
                            if (mote <= motes[j]){
                                mote += mote - 1;
                                ++times;
                            }
                            else{
                                mote += motes[j];
                                break;
                            }
                        }
                    }
                }
            }
            ans = min(ans, times);
        }
        cout << "Case #" << (test+1) << ": " << ans << endl;
    }

    return 0;
}
