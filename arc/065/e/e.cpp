// まず座標をs=x+y, t=x-yととり回転させる
// すると、ある点からmanhattan距離Dの点は、その点の周囲の正方形の上にくるようになる
// 最初の点から、距離Dの点をdfsで辿っていき、距離Dである辺の数を数えていく
// その際、ある点から距離Dの点の数はlower_bound()を使って4つの辺のそれぞれを数える。
//   角に来る点の二重数えに注意。
//   数え上げにiterateを使うと遅い
// ある点から距離Dの点を辿り、dfs()の次の引数とする
//   この際、すでにdfs()の引数になった点・これからなる点を除く

#include <iostream>
#include <sstream>
#include <string>
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

ll N, a, b;
vector<pair<ll,ll>> points_xy;
vector<pair<ll, ll>> points_st;
ll dist;

// ある点から距離Dの点の数を調べるときに使う
map<ll, vector<pair<ll,int>>> S;
map<ll, vector<pair<ll,int>>> T;
// dfsで次の点をたどるときに使う
map<ll, set<pair<ll, ll>>> S_set;
map<ll, set<pair<ll, ll>>> T_set;


// 点nから距離distにある点のsetを返す
// ただし、すでにdfsの引数になった点・これからなる点は除く
set<ll> find_neighbors(ll n) {
    set<ll> ans;

    auto& p = points_st[n];
    auto it = S_set[p.first + dist].lower_bound(mp(p.second - dist, 0));
    while(it != S_set[p.first + dist].end() && it->first <= p.second + dist) {
        ans.insert(it->second);
        ++it;
    }

    it = S_set[p.first - dist].lower_bound(mp(p.second - dist, 0));
    while(it != S_set[p.first - dist].end() && it->first <= p.second + dist) {
        ans.insert(it->second);
        ++it;
    }
    
    it = T_set[p.second + dist].lower_bound(mp(p.first - dist, 0));
    while(it != T_set[p.second + dist].end() && it->first <= p.first + dist) {
        ans.insert(it->second);
        ++it;
    }

    it = T_set[p.second - dist].lower_bound(mp(p.first - dist, 0));
    while(it != T_set[p.second - dist].end() && it->first <= p.first + dist) {
        ans.insert(it->second);
        ++it;
    }

    return ans;
}

// 点nから距離distにある点の数を返す
ll count_pairs(ll n) {
    ll ret = 0;
    auto& p = points_st[n];
    auto s = p.first;
    auto t = p.second;
    ret += lower_bound(ALL(S[s + dist]), mp(t + dist + 1, 0)) - lower_bound(ALL(S[s + dist]), mp(t - dist, 0)); // 端点両方含む 
    ret += lower_bound(ALL(S[s - dist]), mp(t + dist + 1, 0)) - lower_bound(ALL(S[s - dist]), mp(t - dist, 0)); // 端点両方含む 
    ret += lower_bound(ALL(T[t + dist]), mp(s + dist, 0)) - lower_bound(ALL(T[t + dist]), mp(s - dist + 1, 0)); // 端点両方含まない
    ret += lower_bound(ALL(T[t - dist]), mp(s + dist, 0)) - lower_bound(ALL(T[t - dist]), mp(s - dist + 1, 0)); // 端点両方含まない
    return ret;
}

void delete_n(ll n) {
    auto p = points_st[n];
    S_set[p.first].erase(mp(p.second, n));
    T_set[p.second].erase(mp(p.first, n));
}

set<ll> seen;
ll dfs(ll n) {
    ll ans = 0;
    seen.insert(n);
    //cout << "n:" << n << endl;

    // すでに見た点は消さないとループに時間がかかる
    delete_n(n);

    ans += count_pairs(n);

    auto neighbors = find_neighbors(n);
    for (auto& nei: neighbors) {
        delete_n(nei);
    }
    
    for (auto& nei: neighbors) {
        if (n == nei) continue;
        if (!seen.count(nei)) {
            ans += dfs(nei);
        }
    }
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> a >> b;
    --a; --b;
    points_xy.resize(N);
    points_st.resize(N);
    
    REP(n,N) {
        ll x, y;
        cin >> x >> y;
        points_xy[n] = mp(x,y);
        ll s = x + y;
        ll t = x - y;
        points_st[n] = mp(s,t);
        S[s].pb(mp(t,n));
        T[t].pb(mp(s,n));
        S_set[s].insert(mp(t, n));
        T_set[t].insert(mp(s, n));
    }
    for(auto& kv: S) sort(ALL(kv.second));
    for(auto& kv: T) sort(ALL(kv.second));

    auto p1 = points_xy[a];
    auto p2 = points_xy[b];
    dist = (ll)abs(p1.first - p2.first) + (ll)abs(p1.second - p2.second);

    ll ans = dfs(a);
    cout << ans / 2 << endl;

    return 0;
}
