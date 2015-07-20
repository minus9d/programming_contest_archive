#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <deque>
#include <queue>
#include <map>
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
 
ll gcd(ll a, ll b)
{
    while(1)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}
 
ll lcm(ll a, ll b) {
    ll temp = gcd(a, b);
    return temp ? (a / temp * b) : 0;
}
 
int main(void)
{
    ll N;
    cin >> N;
    ll ret = 1;
    REP(n,N) {
        ll a;
        cin >> a;
        ret = lcm(ret, a);
    }
    cout << ret << endl;
     
    return 0;
}
