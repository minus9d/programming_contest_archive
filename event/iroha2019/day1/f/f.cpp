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

vector<ll> getFactorsVector(ll n){
    vector<ll> ret;
    while(!(n % 2)){
        n /= 2;
        ret.push_back(2);
    }
    for(int i = 3; i*i <= n; i += 2){
        while(!(n % i)){
            n /= i;
            ret.push_back(i);
        }
    }
    if (n > 1) ret.push_back(n);
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, K;
    cin >> N >> K;
    auto primes = getFactorsVector(N);

    if(SIZE(primes) < K) {
        cout << -1 << endl;
    }else{
        vector<ll> ans;
        REP(k, K) ans.pb(primes[k]);
        FOR(k, K, SIZE(primes)) ans.back() *= primes[k];
        for(auto a: ans) cout << a << " ";
        cout << endl;

    }

    return 0;
}
