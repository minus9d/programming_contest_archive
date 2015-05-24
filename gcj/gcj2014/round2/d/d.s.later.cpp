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

map<vector<string>,ll> cache;

ll calc_nodes_for_one_server(const vector<string>& words)
{
    if (cache.count(words)) return cache[words];

    set<string> prefixes;

    for(auto w : words) {
        string tmp = "";
        prefixes.insert(tmp);
        REP(i,SIZE(w)) {
            tmp += w[i];
            prefixes.insert(tmp);
        }
    }
    
    cache[words] = prefixes.size();
    return prefixes.size();
}

vector<string> words;
vector<int> comb;

ll mx = -1;
ll way = 0;

void dfs(int idx, int M, int N) {
    if (idx == M) {
        // serverに単語を割り振る
        vector<vector<string>> servers(N);
        REP(i,M){
            servers[comb[i]].push_back(words[i]);
        }

        // 枝刈り
        // 単語が割り当てられないサーバがあるときはノード数最大にならない
        for(auto &s: servers) {
            if (SIZE(s) == 0) return;
        }

        // serverごとにprefixの数を数えて和を取る
        ll n = 0;
        for(auto &s: servers) {
            n += calc_nodes_for_one_server(s);
        }

        if (n > mx) {
            way = 1;
            mx = n;
        }
        else if (n == mx) {
            ++way;
        }
    }
    else {
        REP(n,N) {
            comb[idx] = n;
            dfs(idx + 1, M, N);
        }
    }
}

void solve(void)
{
    int M, N;
    cin >> M >> N;

    words.resize(M);
    REP(m,M) cin >> words[m];

    // reset
    cache.clear();
    comb.resize(M);
    mx = -1;
    way = 0;

    // 各wordについて、サーバ1, 2, ..., Nへ割り振られる場合をすべて試す
    dfs(0, M, N);

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
