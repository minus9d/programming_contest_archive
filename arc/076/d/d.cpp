#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
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

class UnionFind
{
public:
	UnionFind() {};
	~UnionFind() {};

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


struct edge { int u, v, cost; };

class Kruskal {

private:

	// costが小さい順にソート
	static bool comp(const edge& e1, const edge& e2) {
		return e1.cost < e2.cost;
	}

public:

	// クラスカル法で最小全域木を求める
	static int kruskal(vector<edge>& edges, int V)
	{
		sort(ALL(edges), comp);
		UnionFind uf;
		uf.Init(V);

		int res = 0;
		int E = edges.size();
		REP(i, E) {
			edge e = edges[i];
			if (!uf.Same(e.u, e.v)) {
				uf.Unite(e.u, e.v);
				res += e.cost;
			}
		}
		return res;
	}

};


void make_edges(const vector<int>& ex_to_ecid, vector<edge>& edges, int cid_size, map<int, int>& x_decode)
{
	vector<int> lasts(cid_size, -1);
	FOR(i, 1, SIZE(ex_to_ecid)) {
		auto ecid1 = ex_to_ecid[i - 1];
		auto ecid2 = ex_to_ecid[i];
		auto dist = x_decode[i] - x_decode[i - 1];
		edges.pb(edge{ ecid1, ecid2, abs(dist) });
	}
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    set<int> x_set;
    set<int> y_set;

    vector<pair<int,int> > xys(N);

    REP(n,N) {
        int x, y;
        cin >> x >> y;
        xys[n] = mp(x,y);
        x_set.insert(x);
        y_set.insert(y);
    }
    map<int, int> x_encode;
    map<int, int> x_decode;
    map<int, int> y_encode;
    map<int, int> y_decode;
    int idx = 0;
    for(auto x: x_set) {
        x_encode[x] = idx;
        x_decode[idx] = x;
        ++idx;
    }
	idx = 0;
	for (auto y : y_set) {
		y_encode[y] = idx;
		y_decode[idx] = y;
		++idx;
	}

	auto x_size = SIZE(x_set);
	auto y_size = SIZE(y_set);
	UnionFind uf;
	uf.Init(N);
	vector<pair<int, int> > exys; // e = encoded
	vector<vector<int>> ex_members(x_size);
	vector<vector<int>> ey_members(y_size);
	REP(i, N) {
		auto xy = xys[i];
		auto ex = x_encode[xy.first];
		auto ey = y_encode[xy.second];
		exys.push_back(mp(ex, ey));
		ex_members[ex].pb(i);
		ey_members[ey].pb(i);
	}
	for (auto members : ex_members) {
		FOR(i, 1, SIZE(members)) {
			uf.Unite(members[0], members[i]);
		}
	}
	for (auto members : ey_members) {
		FOR(i, 1, SIZE(members)) {
			uf.Unite(members[0], members[i]);
		}
	}

	set<int> cid_set;
	REP(i, N) {
		auto cid = uf.Find(i);
		cid_set.insert(cid);
	}
	map<int, int> cid_encode;
	idx = 0;
	for (auto cid : cid_set) {
		cid_encode[cid] = idx;
		++idx;
	}


	vector<int> ex_to_ecid(x_size);
	vector<int> ey_to_ecid(y_size);
	REP(i, N) {
		auto cid = uf.Find(i);
		auto ecid = cid_encode[cid];
		auto ex = exys[i].first;
		auto ey = exys[i].second;
		ex_to_ecid[ex] = ecid;
		ey_to_ecid[ey] = ecid;
	}

	auto cid_size = SIZE(cid_set);
	const int INF = 1e9;
	
	vector<edge> edges;
	make_edges(ex_to_ecid, edges, cid_size, x_decode);
	make_edges(ey_to_ecid, edges, cid_size, y_decode);

	auto ret = Kruskal::kruskal(edges, cid_size);
	cout << ret << endl;

	// union_find_
	//map<int, int>

	return 0;
}
