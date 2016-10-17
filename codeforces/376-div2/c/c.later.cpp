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

class UnionFind
{
public:
    UnionFind(){};
    ~UnionFind(){};

    void Init(int num_entries) {
        num_entries_ = num_entries;
        par_.resize(num_entries_);
        rank_.resize(num_entries_, 0);
        for (int i = 0; i < num_entries_; ++i)
        {
            par_[i] = i;
        }
    }
    int Find(int x) {
        if (par_[x] == x)
        {
            return x;
        }
        else
        {
            return par_[x] = Find(par_[x]);
        }
    }
    void Unite(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;

        if (rank_[x] < rank_[y])
        {
            par_[x] = y;
        }
        else
        {
            par_[y] = x;
            if (rank_[x] == rank_[y])
            {
                rank_[x]++;
            }
        }
    }
    bool Same(int x, int y) {
        return Find(x) == Find(y);
    }

private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
};

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> colors(N);
    REP(n,N) cin >> colors[n];

    // 本番ではMでなくNとしてしまってランタイムエラー
    vector<int> Ls(M);
    vector<int> Rs(M);
    REP(m,M) {
        int l, r;
        cin >> l >> r;
        Ls[m] = l - 1;
        Rs[m] = r - 1;
    }

    UnionFind uf;
    uf.Init(N);
    REP(m,M) {
        uf.Unite(Ls[m], Rs[m]);
    }
    
    // id, color, num
    map<int, map<int,int>> table;
    REP(n,N) {
        auto id = uf.Find(n);
        ++table[id][colors[n]];
    }

    int ans = 0;
    for (auto& kv: table) {
        auto& cntable = kv.second;
        int mx = -1;
        int member = 0;
        for (auto& kv2: cntable) {
            auto num = kv2.second;
            mx = max(mx, num);
            member += num;
        }
        ans += (member - mx);
    }

    cout << ans << endl;
    return 0;
}
