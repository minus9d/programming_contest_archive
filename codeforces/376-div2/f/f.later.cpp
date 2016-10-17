// 参考：http://kmjp.hatenablog.jp/entry/2016/10/16/1030

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

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> nums(N);
    vector<ll> S(400005); // パワーがi以下のビデオカードの枚数
    set<int> SS;
    REP(n,N) {
        cin >> nums[n];
        S[nums[n]]++;
        SS.insert(nums[n]);
    }
    REP(n,400005) {
        S[n+1] += S[n];
    }

    ll ma = 0;

    // setを使わないとTLEになることに注意
    // setを使った場合は、最悪計算回数が
    // 200000 / 1 + 200000 / 2 + ... + 20000 / 200000
    // となり、250万回以内の計算で収まる
    for(auto r: SS) {
        ll t = 0;

        // 例えばr = 5の場合：
        //  t = パワーが5~9であるビデオカードの枚数 * 5 
        //    + パワーが10~14であるビデオカードの枚数 * 5 * 2
        //    ...
        //  となる。
        //  S[9] - S[4]によりパワーが5~9であるビデオカードの枚数が求まる
        for(auto x = r; x <= 200000; x += r) {
            t += (S[x+r-1] - S[x-1]) * x;
        }
        ma = max(ma, t);
    }
    cout << ma << endl;
    return 0;
}
