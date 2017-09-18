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

vector<int> Ps;
vector<set<int>> Cs;
vector<int> Xs;

tuple<bool, int, int> dfs(int v) {
    // leaf
    if (Cs[v].empty()) {
        // cout << "v " << v << ": possible(leaf)" << endl;
        return mt(true, Xs[v], 0);
    }

    int sum_of_subtree = 0;
    set<int> possible{0};

    for(auto c: Cs[v]) {
        auto ret = dfs(c);
        auto ok_flag = get<0>(ret);
        auto col1 = get<1>(ret);
        auto col2 = get<2>(ret);
        sum_of_subtree += (col1 + col2);
        if (!ok_flag) return mt(false, 0, 0);

        set<int> possible2;
        for(auto p: possible) {
            if (p + col1 <= Xs[v]) possible2.insert(p + col1);
            if (p + col2 <= Xs[v]) possible2.insert(p + col2);
        }
        possible = possible2;
    }

    if (possible.empty()) return mt(false, 0, 0);

    // cout << "possible: ";
    // for(auto p: possible) cout << p << " ";
    // cout << endl;

    auto max_possible = *possible.rbegin();
    int add = Xs[v] - max_possible;

    // cout << "v " << v << ": possible:" << endl;
    // cout << "   " << Xs[v] << ", " << sum_of_subtree + add - Xs[v] << endl;

    return mt(true, Xs[v], sum_of_subtree + add - Xs[v]);
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    Ps.resize(N);
    Cs.resize(N);
    Xs.resize(N);

    REP(n, N-1) {
        int c = n+1;
        int p;
        cin >> p; --p;

        Ps[c] = p;
        Cs[p].insert(c);
    }
    Ps[0] = -1;

    REP(n,N) cin >> Xs[n];

    auto ret = dfs(0);
    if (get<0>(ret)) {
        cout << "POSSIBLE" << endl;
    }
    else {
        cout << "IMPOSSIBLE" << endl;
    }
    
    return 0;
}
