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
#define mt make_tuple

int find_longest_chain(int m, vector<vector<int>>& Revs, int ignore)
{
    if (SIZE(Revs[m]) == 0) {
        return 0;
    }
    else if (SIZE(Revs[m]) == 1 && ignore == Revs[m][0]) {
        return 0;
    }
    else {
        int mx = 0;
        for (auto& v : Revs[m]) {
            if (v == ignore) continue;
            auto tmp = find_longest_chain(v, Revs, -1);
            mx = max(tmp, mx);
        }
        return mx + 1;
    }
}


void solve(void)
{
    int N;
    cin >> N;
    vector<int> Fs(N);
    vector<vector<int>> Revs(N);
    REP(n,N) {
        int tmp;
        cin >> tmp;
        Fs[n] = tmp-1;
        Revs[tmp - 1].push_back(n);
    }

    // (i) circle composed of a single loop
    //     example of circle: a -> b -> ... -> c -> a
    int ans = -1;
    set<set<int>> couples;
    REP(kid, N) {
        set<int> seen;
        int cur = kid;
        while(1) {
            seen.insert(cur);
            int nxt = Fs[cur];
            if (seen.count(nxt)) {
                if (nxt == kid) {
                    ans = max(ans, SIZE(seen));
                }
                if (SIZE(seen) == 2) {
                    couples.insert(seen);
                }

                break;
            }
            cur = nxt;
        }
    }

    // (ii) circle composed of one or more lines containing a single couple [a, b] 
    //     example of single line: an -> ... -> a1 -> a <-> b <- b1 <- ... <- bn
    int second_ans = 0;
    for (auto& couple : couples) {
        second_ans += 2;
        vector<int> tmp(ALL(couple));
        int m1 = tmp[0];
        int m2 = tmp[1];

        second_ans += find_longest_chain(m1, Revs, m2);
        second_ans += find_longest_chain(m2, Revs, m1);
    }

    ans = max(ans, second_ans);

    cout << ans;
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
