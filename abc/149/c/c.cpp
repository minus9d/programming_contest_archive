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

bool isPrime(ll n){
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

int main(void)
{
    cin.sync_with_stdio(false);
    int X;
    cin >> X;

    while(1) {
        if (isPrime(X)) {
            cout << X << endl;
            return 0;
        }
        X++;
    }

    return 0;
}

