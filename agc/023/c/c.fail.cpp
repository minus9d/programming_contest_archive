#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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


ll faster(ll N) {
    vector<int> shff(N - 1);
    REP(i, N - 1) shff[i] = i;
    ll ans = 0;
    ll MOD = 1000000007;
    map<int, map<vector<int>, int>> table;
    do {
        vector<int> cells(N);
        int cnt = 0;
        int colored = 0;
        for (auto s : shff) {
            if (cells[s] == 0) {
                ++colored;
                cells[s] = 1;
            }
            if (cells[s+1] == 0) {
                ++colored;
                cells[s+1] = 1;
            }
            ++cnt;
            if (colored == N) break;
        }
        vector<int> tmp;
        REP(n, cnt) {
            tmp.push_back(shff[n]);
        }
        ++table[cnt][tmp];
        cout << endl;
        ans += cnt;
        ans %= MOD;
    } while (next_permutation(ALL(shff)));

    for (auto kv : table) {
        cout << "score " << kv.first << ": " << endl;
        for (auto kv2 : kv.second) {
            cout << "  x" << kv2.second << ": ";
            for (auto e : kv2.first) cout << e + 1 << " ";
            cout << endl;
        }
    }

    return ans;
}


int main(void) {
    ll N;
    cin >> N;
    auto ans = faster(N);
    cout << ans << endl;

    return 0;
}
