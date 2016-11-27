// 解説に従い実装

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

ll N, A;

bool check(ll time) {
    if (time >= N) return true;

    FOR(cookie_eat_num, 1, 41) {
        ll remain_time = time - A * cookie_eat_num;

        // 例えばクッキーを2回食べる場合
        // クッキーが増えるのを待っている時間をt1, t2, t3とする。
        // ここでt1 + t2 + t3 == remain_time
        // t経過後に生成されるクッキーの量はt1*t2*t3である
        // クッキーの量を最大になるためには、
        // t1, t2, t3がなるべく等しい整数になるように分割する
        ll division_num = cookie_eat_num + 1;
        if (division_num > remain_time) break;

        ll base = remain_time / division_num;
        ll add_one = remain_time - base * division_num;
        ll cookie_num = 1;
        REP(d, division_num) {
            cookie_num *= (base + (add_one > 0));
            --add_one;
            if (cookie_num >= N) return true;
        }
    }
    return false;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> A;

    ll lo = 0;
    ll hi = N;
    while (lo < hi) {
        ll k = (lo + hi) / 2;
        if (check(k)) hi = k;
        else lo = k + 1;
    }
    cout << lo << endl;
    return 0;
}
