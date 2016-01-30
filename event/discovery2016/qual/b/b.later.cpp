// 参考：http://discovery2016-qual.contest.atcoder.jp/submissions/625599

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

int main(void)
{
    int N;
    cin >> N;

	map<int, vector<int>> rooms;
    REP(n,N) {
        int t;
        cin >> t;
        rooms[t].pb(n);
    }

	int ans = 1;
    int cur = -1;
	for (auto e : rooms) {
        auto& locs = e.second;

        // x: 前の数字を処理し終えた後にいる部屋
        // o: 今回処理する数字がある部屋

        // . . x . . o . . の場合
        // 最後のoに移動
        if (locs[0] > cur)
            cur = locs.back();
        // . . o . . x . . o . . の場合
        // xより前にあるoのうち最後のoに移動
        else {
            ++ans;
            int nxt = -1;
            for(auto loc: locs) {
                if (loc < cur) nxt = loc;
                else break;
            }
            cur = nxt;
        }
    }

    // corner case
    if (cur == 0) --ans;

	cout << ans << endl;

    return 0;
}
