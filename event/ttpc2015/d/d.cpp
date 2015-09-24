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
#include <climits>

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

ll repl(string s, vector<char>& chars)
{
    map<char, char> table;
    int idx = 0;
    for (auto& ch : s) {
        if (table.count(ch)) {
            // do nothing
        }
        else {
            table[ch] = chars[idx];
            ++idx;
        }
        ch = table[ch];
    }

    return atoll(s.c_str());
}    

bool isPrime(long long n, vector<ll>& primes){
    if (n <= 1){
        return false;
    }
    for(const auto& p : primes) {
        if (p >= n) break;
        if (n % p == 0){
            return false;
        }
    }
    return true;
}

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
    string S;
    cin >> S;

    set<char> chars(ALL(S));
    
    if (SIZE(chars) > 5) {
        cout << -1 << endl;
    }
    else {
        auto primes = getPrimesFast(sqrt(1e10 + 5));

        vector<char> chars{'1', '3', '5', '7', '9'};
        do {
            auto cand = repl(S, chars);
            if (isPrime(cand, primes)) {
                cout << cand << endl;
                return 0;
            }
        } while(next_permutation(ALL(chars)));
        cout << -1 << endl;
    }

    return 0;
}
