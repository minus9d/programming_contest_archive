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

ll N;
vector<ll> As;
vector<ll> Bs;

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N;

    As.resize(N);
    Bs.resize(N);
    REP(n,N) cin >> As[n];
    REP(n,N) cin >> Bs[n];

    ll ret = Bs[0] * N;
    ll city = 0;
    ll day = 0;
    ll money = 0LL;
    ll best = Bs[0];

    // 街を順に移動
    while(city <= N && day < N) {
        // 街を一つ移動した後の持ち金
        ll expected = money + As[city];
        if (expected >= 0) {
            ++day;
            money = expected;
        }
        else {
            // 次の街に行けない
            if (best <= 0LL) break;

            ll stay = (abs(expected) + best - 1) / best;
            if (day + stay + 1 <= N) {
                money = expected + stay * best;
                day = day + stay + 1;
            } 
            else break;
        }

        ++city;

        // printf("day %d at city %d. money %d. best: %d\n", day, city, money, best);

        // 残り日はbestな街に滞在
        best = max(best, Bs[city]);
        ll tmp = money + (N - day) * best;

        // printf("tmp: %d\n", tmp);

        ret = max(tmp, ret);
    }

    cout << ret << endl;

    return 0;
}
