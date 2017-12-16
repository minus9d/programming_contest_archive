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


vector<pair<ll, ll>> cache;
vector<int> Pof;
vector<vector<int>> Cof;

ll MOD = 1000000007;

ll pow2(ll n) {
    ll ret = 1;
    while (n > 0) {
        ret *= 2;
        ret %= MOD;
        --n;
    }
    return ret;
}

// 自分の下にあるメンバ数と、得点を返す
pair<ll, ll> solve(int v) {
    if (cache[v] != mp(0LL, 0LL)) return cache[v];

    auto childNum = SIZE(Cof[v]);

    // 葉の場合
    if (childNum == 0) {
        return mp(0, 0);
    }

    int gcNum = 0;
    ll scoreSum = 0;
    for (auto c: Cof[v]) {
        ll memberNum = 0;
        ll score = 0;
        tie(memberNum, score) = solve(c);

        scoreSum += score;
        scoreSum %= MOD;
        
        gcNum += memberNum;
        gcNum %= MOD;
    }

    ll ret = pow2(childNum);
    ret *= scoreSum;
    ret %= MOD;
    
    ll ret2 = pow2(gcNum);
    ret2 *= childNum;
    ret2 %= MOD;

    ret += ret2;
    ret %= MOD;

    auto ans = mp(childNum + gcNum, ret);
    cache[v] = ans;
    return ans;
}


int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    cache.resize(N+1);
    Pof.resize(N+1);
    Cof.resize(N+1);

    Pof[0] = -1;
    REP(n, N) {
        int p;
        cin >> p;
        Pof[n+1] = p;
        Cof[p].pb(n+1);
    }

    auto ans = solve(0);

    auto ans2 = 1 + pow2(N);
    auto ans3 = ans.second * ans2;
    ans3 %= MOD;

    cout << ans3 << endl;

    return 0;
}
