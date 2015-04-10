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

        int ans = 99999;
        for(uint i = 0; i < (1 << N); ++i){
            int A2 = A;

            int did = 0;

            for(int counter = 0; counter < N; ++counter){
                if (i & (1 << counter)){
                    int m = motes[counter];

                    //printf("A = %d, mote = %d\n", A2, m);

                    if (A2 > m){
                        A2 += m;
                    }
                    else{
                        pair<int, int> p = need_num(A2, m);
                        did += p.second;
                        A2 = p.first;
                        A2 += m;
                    }
                }
                else{
                    ++did;
                }
            }
//            printf("i, did = %d, %d\n", i, did);
//            cout << "---" << endl;
            ans = min(ans, did);

        }
        cout << "Case #" << (test+1) << ": " << ans << endl;
    }

    return 0;
}
