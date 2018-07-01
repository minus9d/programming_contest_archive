// 本番中に解けた
// まず前処理として、変数bだけを考えればよいように数列Aの各要素からiを引いて数列A2をつくる
// bを、数列のA2の各要素の値それぞれに設定
// 単純にやると計算量が大きくなるので工夫が必要
//
// 解説によると中央値のみで試せばよかったらしい

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
#define mt make_tuple

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];
    vector<ll> A2s(N);
    REP(i, N) {
        A2s[i] = As[i] - (i + 1);
    }
    sort(ALL(A2s));
    // for(auto a: A2s) cout << a << ","; cout << endl;

    map<ll, int> keys;
    for(auto a2: A2s) {
        ++keys[a2];
    }
    ll ans = 1e18;
    ll b = -1;
    int used = 0;
    bool first = true;
    ll tmp_ans = 0;
    for(auto kv: keys) {
        ll key = kv.first;
        ll value = kv.second;
        if (first) {
            b = key;
            for(auto a2: A2s) tmp_ans += abs(a2 - b);
            first = false;
        }
        else {
            ll next_b = key;
            tmp_ans
                = tmp_ans + (next_b - b) * used
                - (next_b - b) * (N - used);
            b = next_b;
        }
        used += value;
        // cout << "tmp_ans:" << tmp_ans << endl;
        ans = min(ans, tmp_ans);
    }
    cout << ans << endl;
    return 0;
}
