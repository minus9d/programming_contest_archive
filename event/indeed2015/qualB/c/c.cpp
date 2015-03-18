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

int main(void)
{
    int N;
    cin >> N;

    vector<vector<int>> edge(N+1);
    REP(n, N-1){
        int a, b;
        cin >> a >> b;
        edge[a].pb(b);
        edge[b].pb(a);
    }

    priority_queue<int, vector<int>, greater<int>> que;
    vector<int> ans;
    set<int> seen;
    que.push(1);
    while(!que.empty()){
        auto p = que.top();
        que.pop();

        ans.pb(p);
        seen.insert(p);
        for (auto& e : edge[p])
        {
            if (!seen.count(e)){
                que.push(e);
            }
        }
    }

    for(int i = 0; i < ans.size(); ++i){
        printf("%d", ans[i]);
        if (i != ans.size() - 1) {
            printf(" ");
        }
        else{
            printf("\n");
        }
    }

    return 0;
}
