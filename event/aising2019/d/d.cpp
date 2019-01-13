// 本番中にAC
//
// [x - k, x + k]の範囲にある点の数(aoki)と、
// [x + k + 1, +inf]の範囲にある点の数(takahashi)を計算。takahashi - aokiの値が0か1になるようなkの値を二分探索。
// 
// ただし、例外として、ちょうどx - kとx + kとに点があり、かつaoki - takahashiが1になる場合がある。
// この場合、aokiはx - kを優先する。したがってx + kはtakahashiに取られる。
//
// kの値が定まったあと、[0, x - k - 1]の領域にある点は、二人が交互に取る。これは事前に求めておける。

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

ll slow_query(ll N, vector<ll>& As, ll x) {
    ll ans = 0;
    bool takahashi = true;
    
    ll max_pos = N - 1;
    vector<char> used(N);

    REP(n, N) {
        if (takahashi) {
            while(true) {
                if (!used[max_pos]) {
                    ans += As[max_pos];
                    used[max_pos] = 1;
                    max_pos--;
                    break;
                } else {
                    --max_pos;
                }
            }
        } else {
            int best_pos = -1;
            int best_dist = 1e9 + 100;
            REP(i, N) {
                if (used[i]) continue;
                auto dist = abs(x - As[i]);
                if (dist < best_dist) {
                    best_dist = dist;
                    best_pos = i;
                }
            }
            used[best_pos] = 1;
        }
        takahashi = !takahashi;
    }
    return ans;
}

vector<ll> slow(ll N, vector<ll>& As, vector<ll>& Xs){
    vector<ll> ans;
    for(auto x: Xs) {
        ans.pb(slow_query(N, As, x));
    }
    return ans;
}

ll cnt_elem_eq_or_less_than_n(vector<ll>& nums, ll n) {
    return std::upper_bound(nums.begin(), nums.end(), n) - nums.begin();
}

ll fast_query(ll N, vector<ll>& As, ll x, set<ll>& pt_locs, vector<ll>& cum_left, vector<ll>& cum_right){
    // 例外：この場合はすべての点が交互に取られる
    if (x >= As[N - 2]) return cum_left[N];

    ll lo = 0;
    ll hi = 1e9 + 100;


    // 位置x にある点の数
    ll pt_num = pt_locs.count(x);

    while (lo < hi) {
        ll k = (lo + hi) / 2;
        // [x+1, x+k]の範囲にある点の数
        ll pt_num_right
            = cnt_elem_eq_or_less_than_n(As, x + k)
            - cnt_elem_eq_or_less_than_n(As, x);
        // [x-k, x-1]の範囲にある点の数
        ll pt_num_left
            = cnt_elem_eq_or_less_than_n(As, x - 1)
            - cnt_elem_eq_or_less_than_n(As, x - k - 1);
        ll aoki = pt_num + pt_num_right + pt_num_left;

        // [x+k+1,]の範囲にある点の数
        ll takahashi = N - cnt_elem_eq_or_less_than_n(As, x + k);

        //cout << "k = " << k << ": aoki " << aoki << ", takahashi " << takahashi << endl;

        auto diff = takahashi - aoki;
        if (0 <= diff && diff <= 1) {
            //cout << "ok. k = " << k << ": aoki " << aoki << ", takahashi " << takahashi << endl;
            ll ans1 = cum_right[takahashi];
            ll ans2 = cum_left[N - aoki - takahashi];
            return ans1 + ans2;
        }

        if (aoki - takahashi == 1 && pt_locs.count(x - k) && pt_locs.count(x + k)) {
            //cout << "ok. k = " << k << ": aoki " << aoki << ", takahashi " << takahashi << endl;
            ll ans1 = cum_right[takahashi + 1];
            ll ans2 = cum_left[N - aoki - takahashi];
            return ans1 + ans2;
        }

        if (aoki > takahashi) {
            hi = k;
        } else {
            lo = k + 1;
        }
    }
    //cout << "ng. k = " << endl;
    return 777;
}

vector<ll> fast(ll N, vector<ll>& As, vector<ll>& Xs){
    vector<ll> ans;

    set<ll> pt_locs;
    for(auto a: As) pt_locs.insert(a);

    // 右側からn個とるときの累積
    vector<ll> cum_right(N+1);
    ll tmp = 0;
    REP(n, N) {
        tmp += As[N - n - 1];
        cum_right[n + 1] = tmp;
    }

    // 左側からn個とるときの累積
    vector<ll> cum_left(N+1);
    tmp = 0;
    REP(n, N) {
        if (N % 2 == 1) {
            if (n % 2 == 0) tmp += As[n];
        }
        else if (N % 2 == 0) {
            if (n % 2 == 1) tmp += As[n];
        }
        cum_left[n + 1] = tmp;
    }

    for(auto x: Xs) {
        //cout << "============" << endl;
        ans.pb(fast_query(N, As, x, pt_locs, cum_left, cum_right));
    }
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, Q;
    cin >> N >> Q;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];
    vector<ll> Xs(Q);
    REP(q, Q) cin >> Xs[q];

    // auto ans = slow(N, As, Xs);
    auto ans = fast(N, As, Xs);
    for(auto a: ans) cout << a << endl;

    return 0;
}
