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
#include <complex>

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
#define mt make_tuple

void solve(void)
{
    int N;
    cin >> N;
    vector<int> Fs(N);
    REP(n,N) {
        int tmp;
        cin >> tmp;
        Fs[n] = tmp-1;
    }

    vector<int> shff(N);
    REP(n,N) shff[n] = n;
    
    int ans = 1;
    do {
        int s = 0;
            FOR(len, 2, N+1) {
                if (len <= ans) continue;

                bool valid = true;
                
                // cout << "circle:" << endl;
                // REP(i, t+1) cout << shff[(s + i) % N] << ",";
                // cout << endl;

                REP(i, len) {
                    int idx = (s + i) % N;
                    int kid = shff[idx];
                    int nxt1 = shff[s + (idx + 1) % len];
                    int nxt2 = shff[s + (idx - 1 + len) % len];
                    // printf("kid,nxt1,nxt2=%d,%d,%d\n", kid,nxt1,nxt2);

                    if (Fs[kid] != nxt1 && Fs[kid] != nxt2) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    ans = max(ans, len);
                }
            }
    } while (next_permutation(ALL(shff)));

    cout << ans;
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": ";
        solve();
        cout << endl;
    }

    return 0;
}
