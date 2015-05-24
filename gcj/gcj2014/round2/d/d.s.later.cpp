#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>
#include <complex>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

const string WALL = "-";

ll calc_nodes_for_one_server(const vector<string>& words)
{
    set<string> prefixes;

    for(auto w : words) {
        string tmp = "";
        prefixes.insert(tmp);
        REP(i,SIZE(w)) {
            tmp += w[i];
            prefixes.insert(tmp);
        }
    }
    
    return prefixes.size();
}

vector<string> words;
vector<int> comb;

vector<ll> dfs(int idx, int M, int N) {
    if (idx == M) {
        vector<vector<string>> servers(N);
        REP(i,SIZE(comb)) {
            servers[comb[i]].push_back(words[i]);
        }

        ll ret = 0;
        for(auto &s: servers) {
            ret += calc_nodes_for_one_server(s);
        }
        return vector<ll>{ret};
    }

    vector<ll> res;
    REP(n,N) {
        comb[idx] = n;
        auto tmp = dfs(idx + 1, M, N);
        for(auto t : tmp) {
            res.pb(t);
        }
    }
    return res;
}

void solve(void)
{
    int M, N;
    cin >> M >> N;

    // cache.clear();

    words.resize(M);
    REP(m,M) cin >> words[m];

    comb.resize(M);

    // 各wordについて、サーバ1, 2, ..., Nへ割り振られる場合をすべて試す
    auto res = dfs(0, M, N);

    ll mx = -1;
    ll way = 0;
    for(auto r : res) {
        if (r > mx) {
            way = 1;
            mx = r;
        }
        else if (r == mx) {
            ++way;
        }
    }

    cout << mx << " " << way;
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": ";
        solve();
        cout << endl;
    }

    return 0;
}
