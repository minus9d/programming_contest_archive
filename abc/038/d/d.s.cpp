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

vector<int> Ws;
vector<int> Hs;
vector<set<int>> bigger;


bool v1_is_bigger_than_v2(int w1, int h1, int w2, int h2) {
    return w1 > w2 && h1 > h2;
}


vector<int> cache;

// 最小の箱がnとする
int dfs(int n) {
    if (cache[n] != 0) return cache[n];

    auto ret = 0;
    auto b = bigger[n];
    if (SIZE(b) == 0) {
        ret = 1;
    }
    else {
        int mx = -1;
        for (auto& e : b) {
            mx = max(mx, dfs(e));
        }
        ret = mx + 1;
    }

    cache[n] = ret;
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    Ws.resize(N);
    Hs.resize(N);
    bigger.resize(N);
    cache.resize(N);

    REP(n,N) {
        int t1, t2;
        cin >> t1 >> t2;
        Ws[n] = t1-1;
        Hs[n] = t2-1;
    }
    
    REP(n1,N) {
        REP(n2,N) {
            if (v1_is_bigger_than_v2(Ws[n1], Hs[n1], Ws[n2], Hs[n2])) {
                bigger[n2].insert(n1);
            }
            else if (v1_is_bigger_than_v2(Ws[n2], Hs[n2], Ws[n1], Hs[n1])) {
                bigger[n1].insert(n2);
            }
        }
    }

    // REP(n,N) {
    //     auto& b = bigger[n];
    //     cout << "n: ";
    //     for(auto e: b) {
    //         cout << e << ",";
    //     }
    //     cout << endl;
    // }

    int ans = 0;
    REP(n,N) {
        ans = max(ans, dfs(n));
    }

    cout << ans << endl;

    return 0;
}
