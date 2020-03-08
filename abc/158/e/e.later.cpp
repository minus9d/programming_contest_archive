// 本番後にAC
//
// 本番中, P = 2 or 5の場合を特別扱いしないといけないことに気付けずWA
//
// P = 2 or 5の場合、部分数列の末尾だけを見ればよい
// Pがそれ以外の場合、
//   例えば S = 3543の場合について考える
//   35がPで割れる <=> 350も3500も35000もPで割れる に着目
//   [(3000 % P), (500 % P), (40 % P), (3 % P)] という配列を作る
//  この配列の部分配列のうち、総和 % Pが0になるものの数が求める答
//  これは、累積和をとり、同じ値になる要素の数を数えることで求められる
//
// http://kmjp.hatenablog.jp/entry/2020/03/08/0930
// に従うともう少し整理できそう


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

ll slow(ll N, ll P, string S) {
    ll ans = 0;
    REP(i, N) {
        FOR(j, i, N) {
            string sub = S.substr(i, j - i + 1);
            ll n = stoll(sub);
            if (n % P == 0) {
                // cerr << "gt: sub = " << sub << endl;
                ++ans;
            }
        }
    }
    return ans;
}

ll solve(ll N, ll P, string S) {
    reverse(ALL(S));

    // P = 2, P = 5は特別扱いする必要がある
    // 本番中は気づけなかった
    if (P == 2 || P == 5) {
        ll ans = 0;
        REP(i, N) {
            ll n = S[i] - '0';
            if (n % P == 0) {
                ans += N - i;
            }
        }
        return ans;
    }

    // 以下、Pと10は互いに素

    vector<ll> nums;
    ll base = 1;
    for(auto ch: S) {
        ll n = ch - '0';
        n *= base;
        n %= P;
        // cerr << n << " ";
        nums.pb(n);
        base *= 10;
        base %= P;
    }
    // cerr << endl;
    vector<ll> sums;
    REP(i, SIZE(nums)) {
        ll tmp = nums[i];
        if (i != 0) {
            tmp += sums.back();
        }
        tmp %= P;
        // cerr << tmp << " ";
        sums.pb(tmp);
    }
    // cerr << endl;

    map<ll, ll> counter;
    for(auto s: sums) {
        counter[s]++;
    }

    ll ans = 0;
    for(auto kv: counter) {
        auto n = kv.first;
        auto count = kv.second;
        // cout << "n, cout = " << n << "," << count << endl;
        if (n == 0) {
            ans += count * (count + 1) / 2;
        } else {
            ans += count * (count - 1) / 2;
        }
        // cout << "now ans = " << ans << endl;
    }
    return ans;
}

bool isPrime(const ll n){
    if (n <= 1){
        return false;
    }
    for(ll i = 2; i*i <= n; ++i){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, P;
    cin >> N >> P;
    string S;
    cin >> S;
    cout << solve(N, P, S) << endl;
    return 0;

    // バグを見つけるためのコード
    {
        string S = "111";
        ll N = SIZE(S);

        // FOR(P, 32, 98) {
        for(ll P = 2; P < 10003; P++) {
            if (!isPrime(P)) continue;
            auto gt = slow(N, P, S);
            auto ans = solve(N, P, S);
            if (gt != ans) {
                cout << "P: " << P << endl;
                cout << "gt = " << gt << endl;
                cout << "ans = " << ans << endl;
                break;
            }
        }
    }

    return 0;
}
