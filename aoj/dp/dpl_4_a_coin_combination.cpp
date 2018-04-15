// 問題: 4つの袋からコインを1枚ずつ取り出してちょうどV円になる組み合わせを求める
// 解法: 2つの袋から作れる金額の組み合わせを総当たりで作成し、組み合わせる

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

map<ll, ll> make_map(vector<ll>& As) {
    map<ll, ll> ret;
    for(auto a: As) ++ret[a];
    return ret;
}

map<ll, ll> make_combination(map<ll, ll>& As, map<ll, ll>& Bs) {
    map<ll, ll> ret;
    for(auto a: As) {
        for(auto b: Bs) {
            auto val = a.first + b.first;
            auto cnt = a.second * b.second;
            ret[val] += cnt;
        }
    }
    return ret;
}

ll coin_combination(ll N, ll V,
                    vector<ll>& As, vector<ll>& Bs,
                    vector<ll>& Cs, vector<ll>& Ds) {
    auto Amap = make_map(As);
    auto Bmap = make_map(Bs);
    auto Cmap = make_map(Cs);
    auto Dmap = make_map(Ds);
    auto ABmap = make_combination(Amap, Bmap);
    auto CDmap = make_combination(Cmap, Dmap);

    ll ret = 0;
    for (auto ab: ABmap) {
        auto val = ab.first;
        auto cnt = ab.second;
        // cout << "val, cnt = " << val << "," << cnt << endl;
        if (CDmap.count(V - val)) {
            ret += cnt * CDmap[V - val];
        }
    }

    return ret;
}

int main() {
    ll N, V;
    cin >> N >> V;
    vector<ll> As(N);
    vector<ll> Bs(N);
    vector<ll> Cs(N);
    vector<ll> Ds(N);
    REP(n, N) cin >> As[n];
    REP(n, N) cin >> Bs[n];
    REP(n, N) cin >> Cs[n];
    REP(n, N) cin >> Ds[n];
    cout << coin_combination(N, V, As, Bs, Cs, Ds) << endl;

    return 0;
}
