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

// 2数の最大公約数
ll getGcdSimple(ll a, ll b)
{
    if (b == 0) return a;
    return getGcdSimple(b, a % b);
}

// 2数の最小公倍数
ll getLcmSimple(ll a, ll b)
{
    return a / getGcdSimple(a, b) * b;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll A, B;
    cin >> A >> B;
    cout << getLcmSimple(A, B) << endl;
    

    return 0;
}
