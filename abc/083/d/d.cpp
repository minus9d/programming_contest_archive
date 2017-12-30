#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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


// vector<ll> getPrimes(ll n) {
//     vector<long long> primes;
//     primes.clear();
//     if (n < 2){
//         return primes;
//     }
//     primes.push_back(2);
//     if (n == 2){
//         return primes;
//     }
//     primes.push_back(3);
//     if (n == 3){
//         return primes;
//     }
//     for(ll i = 5; i <= n; i += 2){
//         bool isPrime = true;
//         for(int p = 0; p < (int)primes.size(); ++p){
//             if (i % primes[p] == 0){
//                 isPrime = false;
//                 break;
//             }
//         }
//         if (isPrime) {
//             primes.push_back(i);
//         }
//     }
//     return primes;
// }


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
    int Q;
    cin >> Q;

    auto primes_vec = getPrimesFast(100000);
    set<ll> primes(ALL(primes_vec));

    vector<int> sum(100010);
    for(int i = 3; i < 100001; i += 2) {
        sum[i] = sum[i-2]
               + primes.count(i) * primes.count((i + 1) / 2);
        sum[i+1] = sum[i];
    }

    REP(q, Q) {
        int l, r;
      	cin >> l >> r;
      	cout << sum[r] - sum[l - 1] << endl;
    }

    return 0;
}
