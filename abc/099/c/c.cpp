#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>


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
    int N;
    cin >> N;

    vector<int> ans(100001);

    set<int> base{1};
    int t = 6;
    while(t <= 100000) {
        base.insert(t); t *= 6;
    }
    t = 9;
    while(t <= 100000) {
        base.insert(t); t *= 9;
    }

    auto que = base;
    int rep = 1;
    while(!que.empty()) {

        for (auto e : que) {
            ans[e] = rep;
        }

        set<int> nxt;
        for(auto e: que) {
            for(auto b: base) {
                if (e + b <= 100000 && ans[e + b] == 0)
                {
                    nxt.insert(e + b);
                }
            }
        }
        cout << endl;
        ++rep;
        que = nxt;
    }
    cout << ans[N] << endl;

    return 0;
}
