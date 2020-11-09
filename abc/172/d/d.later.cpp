// https://twitter.com/kyopro_friends/status/1276873988010995712
// の通り実装。
// 「N以下のうちKの倍数になるもの」を考える！

#include <iostream>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N;
    cin >> N;

    ll ans = 0;
    FOR(i, 1, N + 1) {
        FOR(j, 1, N + 1) {
            ll n = i * j;
            if (n <= N) ans += n;
            else break;
        }
    }
    cout << ans << endl;
    return 0;
}
