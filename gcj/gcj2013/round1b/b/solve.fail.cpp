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

int get_tri(int N){
    if (N == 1) return N;
    
    int n = 2;
    int sum = 1;
    int prev_sum = sum;
    while(1){
        sum += n;
        ++n;
        sum += n;
        ++n;
        
        if (sum > N){
            return prev_sum;
        }
        prev_sum = sum;
    }
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        int N, X, Y;
        cin >> N >> X >> Y;

        double ans = 0;

        int max_tri = get_tri(N);
        int remain = N - max_tri;

        
        

        REP(i, 100){
            
            cout << "i = " << i << ", " << max_tri << endl;
        }
        

        cout << "Case #" << (test+1) << ": " << endl;
    }

    return 0;
}
