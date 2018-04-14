// 提出間に合わず

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


void add_range(vector<pair<double, double>>& can_range, pair<double, double> range) {
    auto it = lower_bound(ALL(can_range), range);
    if (it == can_range.end()) {
        auto b = it - 1;
        if (b->second >= range.first) {
            b->second = range.second;
        }
    }
    else if (*it == range) {
        // pass
    }
    else {
        auto b = it - 1;
        auto a = it;
        // need to insert
        if (b->second < range.first && range.second < a->first) {
            can_range.insert(it, range);
            return;
        }

        // extend
        if (range.second >= a->first) {
            a->first = range.first;
        }
        else {
            can_range.insert(it, range);
        }


        if (b->second >= range.first) {
            b->second = range.second;
            can_range.erase(it);
        }
        else {
            // pass
        }
    }

}

void solve() {
    ll N, P;
    cin >> N >> P;

    vector<ll> Ws(N);
    vector<ll> Hs(N);

    vector<pair<double, double>> ranges(N);
    set<pair<double, double>> seen;
    ll sum_peli = 0;
    REP(n, N) {
        cin >> Ws[n] >> Hs[n];
        sum_peli += (Ws[n] + Hs[n]) * 2;

        double mn = min(Ws[n], Hs[n]) * 2;
        double mx = hypot(Ws[n], Hs[n]) * 2;
        ranges[n] = mp(mn, mx);
        seen.insert(mp(mn, mx));
    }

    // only small
    vector<pair<double, double>> can_ranges;
    for (auto range : ranges) {
        if (can_ranges.empty()) {
            can_ranges.pb(range);
        }
        else {
            vector<pair<double, double>> after = can_ranges;

            add_range(after, range);

            for (auto r : can_ranges) {
                auto new_start = r.first + range.first;
                auto new_end = r.second + range.second;
                add_range(after, mp(new_start, new_end));
            }

            can_ranges = after;
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
