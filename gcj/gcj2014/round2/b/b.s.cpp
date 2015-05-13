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

bool ok(vector<int>& shuf){
    int N = SIZE(shuf);
    int mx = -1;
    int mx_pos = -1;
    REP(i, N){
        if (shuf[i] > mx) {
            mx = shuf[i];
            mx_pos = i;
        }
    }

    REP(i, mx_pos-1){
        if (shuf[i] >= shuf[i+1]) return false;
    }
    FOR(i, mx_pos, N-1){
        if (shuf[i] <= shuf[i+1]) return false;
    }

    return true;
}

ll swap_pos(vector<int>& As, int num, int goal){
    int N = SIZE(As);
    ll swap_num = 0;
    int start = -1;
    for(int i = N-1; i >= 0; --i){
        if (As[i] == num) {
            start = i;
            break;
        }
    }

    // swap
    for(int i = start; i >= goal + 1; --i){
        swap(As[i], As[i-1]);
        ++swap_num;
    }

    return swap_num;
}

ll arrange(vector<int> shuf, vector<int> As){
    int N = SIZE(shuf);
    ll swap = 0;
    REP(i, N){
        if (shuf[i] == As[i]) continue;
        else {
            swap += swap_pos(As, shuf[i], i);
        }
    }
    return swap;
}



int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        int N;
        cin >> N;
        vector<int> As(N);
        REP(n,N) cin >> As[n];

        vector<int> shuf = As;
        sort(ALL(shuf));
        ll ret = 100000000;
        if (N <= 2) {
            ret = 0;
        }
        else {
            do {
                if (ok(shuf)){

                    // for(auto s : shuf) {
                    //     cout << s << ", ";
                    // }
                    // cout << endl;
                    // cout << "  score: " << arrange(shuf, As) << endl;
                    
                    ret = min(ret, arrange(shuf, As));
                }
            }while(next_permutation(ALL(shuf)));
        }
        
        cout << "Case #" << (test+1) << ": " << ret << endl;
    }

    return 0;
}
