#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>


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

const ll MOD = 1e9 + 7;

ll fact(int n) {
    ll ans = 1;
    REP(i, n) {
        ans *= (i + 1);
        ans %= MOD;
    }
    return ans;
}

ll solve(int N, string S) {
    ll n = 0;
    ll ans = 1;
    ll local_ans = 0;
    for (auto ch :S) {
        if (n == 0) {
            if (ch == 'W')
                return 0;
            else {
                n += 1;
                local_ans = 1;
            }
        }
        else if (n % 2 == 1){
            if (ch == 'W') {
                n += 1;
            } else {
                local_ans *= n;
                local_ans %= MOD;
                n -= 1;
            }
        } else {
            if (ch == 'W') {
                local_ans *= n;
                local_ans %= MOD;
                n -= 1;
            } else {
                n += 1;
            }
        }
        if (n == 0) {
            ans *= local_ans;
            ans %= MOD;
        }
    }
    
    if (n != 0) {
        return 0;
    }

    return (ans * fact(N)) % MOD;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    string S;
    
    cin >> N;
    cin >> S;

    cout << solve(N, S) << endl;

    return 0;
}
