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
    int N, M;
    cin >> N >> M;

	UnionFind uf;
	uf.Init(N);		
    REP(m,M) {
        int u, v;
        cin >> u >> v;
		--u; --v;
		uf.Unite(u, v);
    }
	
	map<int, int> group_num;
	REP(n,N) {
		auto group = uf.Find(n);
		++group_num[group];
	}
	
	int ans = N * N;
	int cnt = 0;
	for (auto kv: group_num) {
		int num = kv.second;
		cout << "num = " << num << endl;
		if (num != 1) {
			ans -= (num * num - 1);
			cnt += 1;
		}
	}
	
	ans -= 
	
	cout << ans << endl;

 
    return 0;
}