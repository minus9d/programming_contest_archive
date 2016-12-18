// 御飯を残す寿司はM個。最後に御飯を残す寿司の位置(mとする)を固定して考える。
// 位置0からm-1の寿司のうち、御飯を残す価値のある寿司M-1個を選ぶ。
// それ以外の寿司は御飯ごと食べる。

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
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

int main(void)
{
    cin.sync_with_stdio(false);
    int N,M;
    cin >> N >> M;

    vector<int> X(N);
    vector<int> Y(N);
    REP(n,N) {
        cin >> X[n] >> Y[n];
    }

    // ネタだけ食べる価値の高い寿司上位M-1個をbonusに保持
    // ただのsetだと、同じbonusを持つ寿司が複数あるとき正しく処理できない
    multiset<int> bonus;
    ll ans = 0;
    ll cur_ans = 0;
    REP(n,N) {
        if (SIZE(bonus) > M-1) {
            auto top = *bonus.begin();
            cur_ans -= top;
            bonus.erase(bonus.begin());
        }
        bonus.insert(X[n]-Y[n]);
        cur_ans += X[n];
        // cout << "cur_ans:" << cur_ans << endl;
        ans = max(ans, cur_ans);
    }
    cout << ans << endl;

    return 0;
}
