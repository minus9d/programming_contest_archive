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

#define pb push_back
#define mp make_pair
#define mt make_tuple

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<map<int, int>> edge(N);

    REP(m, M) {
        int l, r, d;
        cin >> l >> r >> d;
        --l; --r;
        edge[l][r] = d;
        edge[r][l] = -d;
    }


    map<int, int> pos;
    // set<int> seen;
    set<int> done;

    bool ok = true;
    REP(n, N) {
        if (done.count(n)) continue;

        pos[n] = 0;
        done.insert(n);

        set<int> bag;
        bag.insert(n);

        while(!bag.empty()) {
            set<int> new_bag;

            for(auto p: bag) {
                // cerr << "p: " << p << endl;
                for(auto nei: edge[p]) {
                    // cerr << "  " << nei.first << endl;
                    auto nei_d = nei.second;
                    auto new_pos = pos[p] + nei_d;
                    if (pos.count(nei.first)) {
                        if (pos[nei.first] != new_pos) {
                            ok = false;
                        }
                    } else {
                        pos[nei.first] = new_pos;
                        // cerr << nei.first << "'s pos: " << new_pos << endl;
                    }
                    if (!done.count(nei.first)) {
                        new_bag.insert(nei.first);
                    }
                }
                done.insert(p);
            }
            bag = new_bag;
        }
    }

    cout << (ok ? "Yes" : "No") << endl;

    return 0;
}
