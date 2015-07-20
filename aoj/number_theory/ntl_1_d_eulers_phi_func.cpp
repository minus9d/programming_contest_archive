#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
 
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
 
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

set<long long> getPrimeFactorsSet(long long n){
    set<long long> ret;
    while(!(n % 2)){
        n /= 2;
        ret.insert(2);
    }
    for(int i = 3; i <= n; i += 2){
        while(!(n % i)){
            n /= i;
            ret.insert(i);
        }
    }
    return ret;
}
 
int popcount(int n) {
    int ret = 0;
    while(n) {
        if (n % 2) ++ret;
        n /= 2;
    }
    return ret;
}

// 1からnまでの整数のうち、aの倍数であるものの個数を返す
ll multiples(int n, int a) {
    return n / a;
}

// 包除原理を使う
int main(void)
{
    ll N;
    cin >> N;

    auto factorsSet = getPrimeFactorsSet(N);
    vector<ll> factors(factorsSet.begin(), factorsSet.end());

    ll ret = 0;
    REP(i, 1 << SIZE(factors)) {
        int ones = popcount(i);
        if (ones == 0) continue;

        ll a = 1;
        REP(j, SIZE(factors)) {
            if ((1 << j) & i) a *= factors[j];
        }
        if (ones % 2) {
            ret += multiples(N, a);
        }
        else {
            ret -= multiples(N, a);
        }
    }

    ret = N - ret;
    cout << ret << endl;
     
    return 0;
}
