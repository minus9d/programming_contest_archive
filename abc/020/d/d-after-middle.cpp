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

// 最大公約数
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

ll lcm(ll a, ll b)
{
    ll temp = gcd(a, b);
    return temp ? (a / temp * b) : 0;
}

const int MOD = 1000000007;

int main(void)
{
    int N, K;
    cin >> N >> K;

    auto ret = 0LL;

    // LCM(a,b) = a*b/GCD(a,b) = a*b/GCD(a%b, b) という関係を使う
    // a%bが同じ項を集めると、
    //    LCM(a1,b) + LCM(a2,b) + ... = 1/GCD(a%b,b) * b*(a1+a2+...)
    // となる
    
    // k: NをKで割った余り
    REP(k, K){
        // 項数
        ll itemNum = (N-k)/K + 1;
        // 初項, 最後の項
        ll f = k;
        ll l = (itemNum - 1) * K + k;

        // 0を除く
        if (f == 0) {
            f += K;
            itemNum -= 1;
        }

        // cout << "mod: " << k << endl;
        // cout << "  item num: " << itemNum << endl;
        // cout << "  " << f << ", ..., " << l << endl;
        
        ll sum = (f + l) * itemNum / 2;
        sum *= K;
        sum /= gcd(k, K);
        sum %= MOD;

        ret += sum;
        ret %= MOD;
    }

    cout << ret << endl;

    return 0;
}
