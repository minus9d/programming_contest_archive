#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>

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

map<long long, int> getFactorsMap(long long N){
    map<long long, int> ret;
    for (long long p=2; p*p <= N; p++) {
        while (N % p == 0) {
            N /= p;	
            ret[p]++;
        }
    }
    ret[N]++;
    return ret;
}

const int MOD = 1000000007;

ll getMul(map<long long, int> a)
{
    ll ret = 1LL;
    
}

ll myPow(int num, int count)
{
    ll ret = 1LL;
    REP(c, count){
        ret *= (ll)num;
        ret %= MOD;
    }
    return ret;
}

int main(void)
{
    int N, K;
    cin >> N >> K;
    
    auto factorsK = getFactorsMap(K);
    ll sum = 0LL;
    FOR(n, 1, N+1){
        // cout << "--" << n << "--" << endl;
        auto factorsN = getFactorsMap(n);
        ll mul = 1LL;
        
        for(auto& f_n : factorsN){
            int num = f_n.first;
            int count = f_n.second;
            // printf(" factor: %d ^ %d\n", num, count);
            
            if (factorsK[num] < count){
                mul *= myPow(num, count - factorsK[num]);
            }
        }
        // cout << "mul: " << mul << endl;
        
        sum += mul;
        sum %= MOD;
    }

    sum *= K;
    sum %= MOD;

    cout << sum << endl;

    return 0;
}
