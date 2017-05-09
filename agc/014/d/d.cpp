// 解説
// 先手は、葉の隣にある頂点を優先的に選んで塗る
// すると、後手は、葉を塗らざるをえない
// この戦略で先手が負ける場合、先手は他の戦略をとっても負ける

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

vector<set<int>> edges;
vector<int> degrees;        // 各頂点の次数
vector<int> degree_ones;    // 次数1の頂点のリスト
vector<int> deleted;        // 削除した頂点に1を立てる

void delete_v(int v, vector<int>& new_degree_ones) {
    for (auto v_nei: edges[v]) {
        edges[v_nei].erase(v);
        degrees[v_nei] -= 1;
        if (degrees[v_nei] == 1) {
            new_degree_ones.pb(v_nei);
        }
    }
    edges[v].clear();
    degrees[v] = 0;
    deleted[v] = 1;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    edges.resize(N);
    degrees.resize(N);
    deleted.resize(N);

    REP(n,N-1) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        edges[a].insert(b);
        edges[b].insert(a);
        ++degrees[a];
        ++degrees[b];
    }

    REP(i, N) {
        if (degrees[i] == 1) {
            degree_ones.pb(i);
        }
    }
    
    while(SIZE(degree_ones) > 0) {
        vector<int> new_degree_ones;
        vector<int> dummy;

        // 次数1の頂点でループ
        for(auto i: degree_ones) {

            // このループを回して頂点を消す過程で、次数が1でなくなっているかもしれないので
            // 改めてチェックする
            if (degrees[i] != 1) continue;

            auto j = *edges[i].begin();

            delete_v(i, dummy);

            // cout << "-----------" << endl;
            // cout << i << " is deleted." << endl;
            // REP(i, N) {
            //     cout << "degrees of " << i << ": " << degrees[i] << endl;
            // }

            // 頂点iと繋がっている頂点jを削除
            // この際、頂点jを削除することによって生じた次数1の点をnew_degree_onesに記録
            delete_v(j, new_degree_ones);

            // cout << "-----------" << endl;
            // cout << j << " (pair of i) is deleted." << endl;
            // REP(i, N) {
            //     cout << "degrees of " << i << ": " << degrees[i] << endl;
            // }

            // cout << "now new_degree_ones size:" << SIZE(new_degree_ones) << endl;
            // for(auto v : new_degree_ones) cout << v << ",";
            // cout << endl;
        }

        degree_ones = new_degree_ones;
    }

    REP(i, N) {
        // 孤立した点がある場合はdeleted[i]は0のまま
        if (deleted[i] == 0) {
            cout << "First" << endl;
            return 0;
        }
    }
    cout << "Second" << endl;
    return 0;
}
