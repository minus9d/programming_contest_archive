// 参考：http://arc046.contest.atcoder.jp/submissions/593126
// http://kmjp.hatenablog.jp/entry/2015/12/14/1000

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

int main(void)
{
    cin.sync_with_stdio(false);
    int N,M;
    cin >> N >> M;
    vector<pair<int,int>> ABs(N);
    vector<pair<int,int>> DCs(M);

    REP(n,N) cin >> ABs[n].first >> ABs[n].second;
    REP(m,M) cin >> DCs[m].second >> DCs[m].first;

    sort(ALL(ABs), greater<pair<int,int>>()); // 男性を、自身の年収の高い順にソート
    sort(ALL(DCs), greater<pair<int,int>>()); // 女性を、希望年収の高い順にソート

    int ptr = 0;
    multiset<int> que; // 今注目している女性の希望年収を満たす男性の、女性に求める年収を管理
    int ret = 0;

    // 希望年収の高い順に女性を見ていく
    REP(i,M) {
        // 今注目している女性の希望年収よりも高い年収の男性を、queに入れる
        while(ptr < N && DCs[i].first <= ABs[ptr].first) {
            que.insert(ABs[ptr].second);
            ++ptr;
        }
        
        // queには、女性側の要求を満たす男性のみ入っている
        // この女性の年収でマッチングが可能な男性の上限を取得
        auto it = que.upper_bound(DCs[i].second);
        if (it == que.begin()) continue; // この女性の年収ではどの男性ともマッチングしない
        que.erase(--it);
        ++ret;
    }

    cout << ret << endl;

    return 0;
}
