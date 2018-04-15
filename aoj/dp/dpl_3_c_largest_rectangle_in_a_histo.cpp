// 問題: ヒストグラムに含まれる長方形の面積の最大値を求める
// 解法: dpl_3_bのサブセット
//       http://algorithms.blog55.fc2.com/blog-entry-132.html

#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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

ll largest_square(const ll N, const vector<ll>& in_histo) {
    // 番兵として、右端に0を入れる
    auto histo = in_histo;
    histo.pb(0);

    ll ans = 0;
    // <ヒストグラムの高さ, index>
    stack<pair<ll, ll>> s;
    REP(n, N+1) {
        auto height = histo[n];
        if (s.empty()) s.push(mp(height, n));
        else if (s.top().first < height) s.push(mp(height, n));
        else if (s.top().first > height) {
            ll last_idx = n;
            while(!s.empty() && s.top().first > height) {
                auto area = (n - s.top().second) * s.top().first;
                ans = max(area, ans);
                last_idx = s.top().second;
                s.pop();
            }
            s.push(mp(height, last_idx));
        }
    }
    return ans;
}

int main() {
    ll N;
    cin >> N;
    vector<ll> histo(N);
    REP(n, N) cin >> histo[n];
    cout << largest_square(N, histo) << endl;

    return 0;
}
