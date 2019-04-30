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

// n以下の素数を得る　速い
// use Sieve of Eratosthenes
// warning: needs lots of memory
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

int count_prime_sums(vector<int>& As, set<int>& primes) {
    int local = 0;
    int sum = 0;
    for(auto a: As) {
        sum += a;
        local += primes.count(sum);
    }
    return local;
}

vector<int> slow(int N, vector<int> As, set<int>& primes) {
    vector<int> best_A;
    int best = 0;
    sort(ALL(As));
    do {
        int local = count_prime_sums(As, primes);
        if (local > best) {
            best = local;
            best_A = As;
        }
    }while(next_permutation(ALL(As)));
    return best_A;
}

vector<int> fast(int N, vector<int>& As) {

    int one = 0;
    int two = 0;
    for(auto a: As) {
        if (a == 1) one++;
        else two++;
    }

    vector<int> ans;
    if (N == 1) {
        ans = As;
    }
    else {
        if (one == 0 || two == 0) {
            ans = As;
        } else {
            ans.pb(2);
            ans.pb(1);
            REP(n, two - 1) ans.pb(2);
            REP(n, one - 1) ans.pb(1);
        }
    }
    return ans;
}


int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> As(N);
    REP(n, N) {
        int a; cin >> a;
        As[n] = a;
    }

    // while(1){
    //     int N = 5;
    //     vector<int> As(N);
    //     REP(n, N) As[n] = (rand() % 2) + 1;

    //     auto primes_v = getPrimesFast(400000);
    //     set<int> primes(ALL(primes_v));
     
     
    //     vector<int> ans_f = fast(N, As);
    //     vector<int> ans_s = slow(N, As, primes);

    //     int nf = count_prime_sums(ans_f, primes);
    //     int ns = count_prime_sums(ans_s, primes);
    //     if (nf != ns) {
    //         cout << "error ! "  << endl;

    //         cout << "As: ";
    //         REP(n, N) cout << " " << As[n];
    //         cout << endl;

    //         cout << "fast: ";
    //         REP(n, N) cout << " " << ans_f[n];
    //         cout << endl;

    //         cout << "slow: ";
    //         REP(n, N) cout << " " << ans_s[n];
    //         cout << endl;

    //         cout << nf << "," << ns << endl;

    //     }
    // }

    vector<int> ans = fast(N, As);

    cout << ans[0];
    FOR(n, 1, N) cout << " " << ans[n];
    cout << endl;

    return 0;
}
