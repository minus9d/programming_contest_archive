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


pair<int, int> need_num(int A, int num){
    int rep = 0;
    while(A <= num){
        A = A + A - 1;
        ++rep;
    }
    return mp(A, rep);
}

int dfs(int i, int N, int A, vector<int> &motes){
    if (i == N){
        return 0;
    }
    else{
        if (A > motes[i]){
            A += motes[i];
            return dfs(i+1, N, A, motes);
        }
        else{
            pair<int, int> p = need_num(A, motes[i]);

            int num1 = dfs(i+1, N, A, motes) + 1;
            int num2 = dfs(i+1, N, p.first + motes[i], motes) + p.second;
            
            return min(num1, num2);
            
        }
    }
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

        int ans = dfs(0, N, A, motes);
        cout << "Case #" << (test+1) << ": " << ans << endl;
    }

    return 0;
}
