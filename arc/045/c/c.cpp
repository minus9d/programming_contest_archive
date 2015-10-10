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

struct Pair{
    ull v;
    ull cost;
};

vector<vector<Pair>> edges;
vector<ull> xors;

void dfs(ull v, ull prevV, ull xor_)
{
    for (auto& to : edges[v]) {
        if (to.v == prevV) continue;
        xors[to.v] = xor_ ^ to.cost;
        dfs(to.v, v, xors[to.v]);
    }
}


int main(void)
{
    cin.sync_with_stdio(false);
	ull N, X;
	cin >> N >> X;

    edges.resize(N);
    xors.resize(N);
    REP(n,N-1) {
		ull x, y, c;
		cin >> x >> y >> c;
		--x;
		--y;
        edges[x].pb({y,c});
        edges[y].pb({x,c});
    }

    dfs(0, -1, 0);

	// 頂点0から他の頂点まで
	ull ret = 0;
	FOR(i, 1, SIZE(xors)) {
		ret += (xors[i]== X);
	}


	// xorsの値の数でmap作る
	map<ull, ull> table;
	FOR(i, 1, SIZE(xors)) {
		table[xors[i]]++;
	}

	// 頂点aから頂点bまで (a != 0 かつ b != 0)
	set<ull> seen;
	for (auto e : table) {
		auto x = e.first;
		auto num = e.second;

		if (seen.count(x)) continue;

		ull pair = x ^ X;

		if (table.count(pair)) {
			if (pair != x)
				ret += num * table[pair];
			// コーナーケース!!
			else
				ret += num * (num - 1) / 2;
		}

		seen.insert(pair);
	}

	//FOR(i, 1, SIZE(xors)) {
	//	auto x = xors[i];
	//	if (seen.count(x)) continue;
	//	auto pair = x ^ X;
	//	ret += table[pair];
	//	seen.insert(pair);
	//}


	cout << ret << endl;


    return 0;
}
