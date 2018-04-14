// 解法
//   高さH、幅Wの長方形を切断するとき、増える周囲長は [min(H, W), hypot(H, W)]。
//   長方形がすべて同じサイズの場合、n個の長方形を切断するなら、
//   増える周囲長は [n*min(H, W), n*hypot(H, W)]。
//   あとは n = 0 .. Nと動かし、周囲長が目標に近付くような最良の切り方を求める

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
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

void solve() {
    ll N, P;
    cin >> N >> P;

    vector<ll> Ws(N);
    vector<ll> Hs(N);

    vector<pair<double, double>> ranges(N);

    ll sum_peli = 0;
    REP(n, N) {
        cin >> Ws[n] >> Hs[n];
        sum_peli += (Ws[n] + Hs[n]) * 2;

        double mn = min(Ws[n], Hs[n]) * 2;
        double mx = hypot(Ws[n], Hs[n]) * 2;
        ranges[n] = mp(mn, mx);
    }

    // only small
    vector<pair<double, double>> can_ranges;
    for (auto range: ranges) {
        if (can_ranges.empty()) {
            can_ranges.pb(range);
        }
        else {
            auto last = can_ranges.back();

            auto new_start = last.first + range.first;
            auto new_end = last.second + range.second;

            // if (last.second >= new_first) {
            //     can_ranges.back().second = range.second;
            // }
            // else {
                can_ranges.pb(mp(new_start, new_end));
            // }
        }
    }

    double shortage = P - sum_peli;
    double ans = sum_peli;
    for (auto range: can_ranges) {
        if (shortage < range.first) {
            // pass
        }
        if (range.first <= shortage && shortage <= range.second) {
            ans = P;
            break;
        }
        else if (range.second < shortage) {
            ans = sum_peli + range.second;
        }
    }
    cout << fixed << setprecision(30) << ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
        return 0;
}
