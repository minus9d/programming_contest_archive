#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

bool ok(string T, char ch) {
    for(auto c : T) {
        if (c != ch) return false; 
    }
    return true;
}


int main(void)
{
    cin.sync_with_stdio(false);
    string S;
    cin >> S;

    int ans = 1e9;
    REP(i, 26) {
        char target = 'a' + i;
        string T = S;
        while(1) {
            if (ok(T, target)) break;
            string T2;
            REP(j, SIZE(T)-1) {
                if (T[j] == target || T[j+1] == target) {
                    T2 += target;
                }
                else {
                    T2 += T[j];
                }
            }
            T = T2;
        }
        ans = min(ans, SIZE(S) - SIZE(T));
    }
    cout << ans << endl;

    return 0;
}
