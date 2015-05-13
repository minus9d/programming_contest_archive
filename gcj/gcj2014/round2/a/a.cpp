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
#include <climits>

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
        int N, X;
        cin >> N >> X;
        vector<int> Ss(N);
        vector<char> seen(N);
        REP(n, N){
            cin >> Ss[n];
        }

        sort(ALL(Ss), greater<int>());

        // for(auto s : Ss){
        //     cout << s << endl;
        // }

        int ret = 0;
        REP(i, N){
            // printf("seen[%d] = %d\n", i, seen[i]);
            if (seen[i]) continue;
            seen[i] = 1;
            ++ret;
            int remain = X - Ss[i];
            FOR(j, i + 1, N) {
                if (!seen[j] && remain >= Ss[j]){
                    seen[j] = 1;
                    break;
                }
            }
        }

        // for(auto j : seen){
        //     cout << (int)j << ", ";
        // }
        // cout << endl;
        
        cout << "Case #" << (test+1) << ": " << ret << endl;
    }

    return 0;
}
