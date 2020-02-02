// コンテスト後に実装
//
// http://drken1215.hatenablog.com/entry/2020/01/26/234000 
// の方法(1) 区間加算に対応したデータ構造を使う


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

// https://github.com/drken1215/algorithm/blob/master/DataStructure/binary_indexed_tree.cpp
// 区間加算にも対応した BIT
// 参考: https://www.slideshare.net/hcpc_hokudai/binary-indexed-tree
template <class Abel> struct BIT {
    vector<Abel> dat[2];
    Abel UNITY_SUM = 0;                     // to be set
    
    /* [1, n] */
    BIT(int n) { init(n); }
    void init(int n) {
        REP(iter, 2) dat[iter].assign(n + 1, UNITY_SUM);
    }
    
    /* a, b are 1-indexed, [a, b) */
    inline void sub_add(int p, int a, Abel x) {
        for (int i = a; i < (int)dat[p].size(); i += i & -i)
            dat[p][i] = dat[p][i] + x;
    }
    inline void add(int a, int b, Abel x) {
        sub_add(0, a, x * -(a - 1)); sub_add(1, a, x); sub_add(0, b, x * (b - 1)); sub_add(1, b, x * (-1));
    }
    
    /* a is 1-indexed, [a, b) */
    inline Abel sub_sum(int p, int a) {
        Abel res = UNITY_SUM;
        for (int i = a; i > 0; i -= i & -i) res = res + dat[p][i];
        return res;
    }
    inline Abel sum(int a, int b) {
        return sub_sum(0, b - 1) + sub_sum(1, b - 1) * (b - 1) - sub_sum(0, a - 1) - sub_sum(1, a - 1) * (a - 1);
    }
    
    /* debug */
    void print() {
        for (int i = 1; i < (int)dat[0].size(); ++i) cout << sum(i, i + 1) << ",";
        cout << endl;
    }
};

int main(void)
{
    cin.sync_with_stdio(false);

    ll N, D, A;
    cin >> N >> D >> A;

    BIT<ll> bit(N);

    // 爆弾の終端と、モンスターの位置を両方扱うqueue
    // 爆弾より先にモンスターが取り出されるようにするため、
    // モンスターの値に-1をかけておく
    using P = pair<ll, ll>;
    priority_queue<P, vector<P>, greater<P>> q;

    ll ans = 0;
    FOR(n, 1, N + 1) {
        ll x, h;
        cin >> x >> h;

        ll damage = bit.sum(n, n + 1);
        h -= damage;
        if (h > 0) {
            ll bomb_num = (h + (A - 1)) / A;
            ans += bomb_num;
            // bomb_num回だけ爆弾を x + D に落とす
            
        }
        q.push({x, -h});
    }

    ll damage = 0;
    ll ans = 0;
    while(!q.empty()) {
        auto p = q.top(); q.pop();

        // 爆弾の終端
        if (p.second > 0) {
            damage -= p.second;
        }
        // モンスター
        else {
            ll hp = -p.second;
            hp -= damage;
            if (hp > 0) {
                ll need_num = (hp + A - 1) / A;
                damage += need_num * A;
                ans += need_num;
                q.push({p.first + 2 * D, need_num * A});
            }
        }
    }
    cout << ans << endl;

    return 0;
}
