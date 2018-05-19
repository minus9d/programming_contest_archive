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
    int N, M;
    cin >> N >> M;

    vector<int> Ps(N);
    REP(n, N) {
        int p;
        cin >> p;
        Ps[n] = p-1;
    }

    UnionFind uf;
    uf.init(N);

    REP(m, M) {
        int x, y; cin >> x >> y;
        --x; --y;
        uf.unite(x, y);
    }

    vector<int> used(N);
    vector<set<int>> groups(N);
    REP(n, N) {
        auto id = uf.find(n);
        groups[id].insert(n);
    }
    int ans = 0;
    REP(n, N) {
        if (!used[n]) {
            auto id = uf.find(n);
            auto members = groups[id];
            for(auto m: members) {
                auto val = Ps[m];
                if (members.count(val)) {
                    ++ans;
                }
                used[m] = 1;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
