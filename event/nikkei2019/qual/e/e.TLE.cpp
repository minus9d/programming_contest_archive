// 本番中に提出してWA
//
// 部分木をUnion Findで構成 →
// 条件を満たしていない辺を取り除く を繰り返してTLE

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

class UnionFind
{
public:
    UnionFind(){};
    ~UnionFind(){};
    void init(int num_entries) {
        num_entries_ = num_entries;
        par_.resize(num_entries_);
        rank_.resize(num_entries_, 0);
        REP(i, num_entries_) par_[i] = i;
    }
    int find(int x) {
        if (par_[x] == x) return x;
        else return par_[x] = find(par_[x]);
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (rank_[x] < rank_[y]) par_[x] = y;
        else {
            par_[y] = x;
            if (rank_[x] == rank_[y]) rank_[x]++;
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
};

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, M;
    cin >> N >> M;
    vector<ll> Xs(N);
    ll sum_of_x = 0;
    REP(n, N) {
        cin >> Xs[n];
        sum_of_x += Xs[n];
    }
    int ans = 0;
    vector<pair<int,int>> edges(M);
    vector<ll> Ys(M);
    vector<char> deleted_edge(M);
    UnionFind uf;
    uf.init(N);
    REP(m, M) {
        int a, b; ll y;
        cin >> a >> b >> y;
        --a; --b;
        edges[m] = mp(a, b);
        Ys[m] = y;
        uf.unite(a, b);
    }

    // 各グループごとの頂点の和を計算
    vector<ll> group_sum(N);
    REP(n, N) {
        auto id = uf.find(n);
        group_sum[id] += Xs[n];
    }

    while(true) {
        bool ok = true;

        // 全辺についてチェック
        REP(m, M) {
            if (deleted_edge[m]) continue;

            int a, b; ll y;
            tie(a, b) = edges[m];
            y = Ys[m];

            auto id = uf.find(a);
            auto score = group_sum[id];
            if (y > score) {
                ok = false;
                // エッジを消す
                deleted_edge[m] = 1;
                ++ans;
            }
        }
        if (ok) break;

        // ufやりなおし
        uf.init(N);
        REP(m, M) {
            if (deleted_edge[m]) continue;
            int a, b; ll y;
            tie(a, b) = edges[m];
            y = Ys[m];
            uf.unite(a, b);
        }
        // sumやりなおし
        group_sum = vector<ll>(N);
        REP(n, N) {
            auto id = uf.find(n);
            group_sum[id] += Xs[n];
        }
    }
    cout << ans << endl;
    return 0;
}
