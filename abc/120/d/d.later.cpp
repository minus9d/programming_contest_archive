// 本番中はintのオーバーフローにより2WA

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
        member_num_.resize(num_entries_, 1);
        REP(i, num_entries_) {
            par_[i] = i;
        }
    }
    int find(int x) {
        if (par_[x] == x) return x;
        else return par_[x] = find(par_[x]);
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (rank_[x] < rank_[y]) {
            par_[x] = y;
            member_num_[y] += member_num_[x];
            member_num_[x] = 0;
        } else {
            par_[y] = x;
            member_num_[x] += member_num_[y];
            member_num_[y] = 0;
            if (rank_[x] == rank_[y]) rank_[x]++;
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) {
        return member_num_[this->find(x)];
    }
private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
    std::vector<int> member_num_;
};

vector<ll> solve(ll N, ll M, vector<pair<ll, ll>> ABs) {
    REP(m, M) cin >> ABs[m].first >> ABs[m].second;
    reverse(ALL(ABs));
    UnionFind uf;
    uf.init(N);

    vector<ll> ans;
    ans.pb(N * (N - 1) / 2);

    for(auto ab: ABs) {
        auto a = ab.first - 1;
        auto b = ab.second - 1;
        ll decrease = 0;
        if (uf.find(a) != uf.find(b)) {
            ll n1 = uf.size(a);
            ll n2 = uf.size(b);
            decrease = n1 * n2;
        }
        ans.pb(ans.back() - decrease);
        uf.unite(a, b);
    }
    ans.pop_back();
    reverse(ALL(ans));
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, M;
    cin >> N >> M;
    vector<pair<ll,ll>> ABs(M);
    auto ans = solve(N, M, ABs);
    for(auto a: ans) cout << a << endl;
    return 0;
}
