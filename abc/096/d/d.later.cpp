// 自力で解答
//
// 5n + 2のタイプの素数ばかり集めると、
// どの素数を5個集めてもその和は必ず5で割り切れる

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

vector<ll> getPrimesFast(ll n){
    vector<ll> primes;
    if (n < 10000){
        primes.clear();
        if (n < 2){
            return primes;
        }
        primes.push_back(2);
        if (n == 2){
            return primes;
        }
        primes.push_back(3);
        if (n == 3){
            return primes;
        }
        for(ll i = 5; i <= n; i += 2){
            bool isPrime = true;
            for(int p = 0; p < (int)primes.size(); ++p){
                if (i % primes[p] == 0){
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                primes.push_back(i);
            }
        }
        return primes;
    }
    else{
        vector<ll> sieve = getPrimesFast(sqrt(n));

        vector<short> isPrime(n+1, 1);
        for(int i = 0; i < (int)sieve.size(); ++i){
            for(int j = sieve[i] * 2; j <= n; j += sieve[i]){
                isPrime[j] = 0;
            }
        }

        for(int i = 2; i <= n; ++i){
            if (isPrime[i]){
                primes.push_back(i);
            }
        }
        return primes;
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    auto primes = getPrimesFast(55555);
    vector<int> ans;
    for(auto p: primes) {
        if (p % 5 == 2) {
            ans.pb(p);
            if (SIZE(ans) == N) break;
        }
    }
    cout << ans[0];
    FOR(n, 1, N) {
        cout << " " << ans[n];
    }
    cout << endl;

    return 0;
}
