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

// 数列を前から順番に見ていく
// 例えばある瞬間, idx 3の場所に4が見つかったとする。
// *は4以外の数字、?はドントケアを表す
//   idx  0 1 2 3 4 5 6
//   val  4 * * 4 ? ? ?
// このとき、4を含む部分数列として以下のものを加える。
// idx 0から始まる部分数列は既に考慮済みなので考えない
//   (1,3), (1,4), (1,5), (1,6),
//   (2,3), (2,4), (2,5), (2,6),
//   (3,3), (3,4), (3,5), (3,6),
// この個数は
//   (N - 3) * (3 - 0)
// 一般化して
//   (N - idx) * (idx - (前に4が出たidx))
// と表せる

int main(void)
{
    int N, C;
    cin >> N >> C;

    vector<int> lastSeen(C+1, -1);
    vector<ll> ans(C+1);
    REP(n, N){
        int a;
        cin >> a;
        ans[a] += (ll)(N - n) * (n - lastSeen[a]);

        lastSeen[a] = n;
    }

    REP(c, C){
        printf("%lld\n", ans[c+1]);
    }
    
    return 0;
}
