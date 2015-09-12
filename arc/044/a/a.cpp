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
#define mt make_tuple

bool isPrime(long long n){
    if (n <= 1){
        return false;
    }
    for(int i = 2; i*i <= n; ++i){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

int sum(ll n)
{
    int ret = 0;
    while(n > 0) {
        ret += n % 10;
        n /= 10;
    }
    return ret;
}

bool judge(ll n)
{
    if (n == 1) return false;
    if (isPrime(n)) return true;
    ll v1 = n % 10;
    if (v1 % 2 == 1 && v1 != 5 && sum(n) % 3 != 0) return true;
    return false;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N;
    cin >> N;

    cout << (judge(N) ? "Prime" : "Not Prime") << endl;

    return 0;
}
