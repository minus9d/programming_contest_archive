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

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, M, K;
    cin >> N >> M >> K;

    vector<int> friends(N);
    vector<int> blocks(N);
    vector<pair<ll, ll>> ABs(M);
    REP(m, M) {
        ll a, b;
        cin >> a >> b;
        --a; --b;
        ABs[m] = mp(a, b);
        friends[a]++;
        friends[b]++;
    }
    vector<pair<ll, ll>> CDs(K);
    REP(k, K) {
        ll c, d;
        cin >> c >> d;
        --c; --d;
        CDs[k] = mp(c, d);
        blocks[c]++;
        blocks[d]++;
    }

    UnionFind uf;
    uf.init(N);

    for (auto& ab: ABs) {
        ll a = ab.first;
        ll b = ab.second;
        uf.unite(a, b);
    }

    // つながっているがblockの数を数える
    vector<int> connect_but_blocks(N);
    for (auto& cd: CDs) {
        ll c = cd.first;
        ll d = cd.second;
        if (uf.same(c, d)) {
            connect_but_blocks[c]++;
            connect_but_blocks[d]++;
        }
    }
    


    // REP(i, N) {
    //     auto s = uf.size(i);
    //     cout << "size:" << s << endl;
    // }

    REP(i, N) {
        auto s = uf.size(i);
        if (i != 0) cout << " ";
        cout << (s - friends[i] - connect_but_blocks[i] - 1);
    }
    cout << endl;
    

    return 0;
}
