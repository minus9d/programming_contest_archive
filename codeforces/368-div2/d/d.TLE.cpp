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

struct State {
    map<int,set<short>> s;
    vector<bool> rev;
    int sum;
};

int main(void)
{
    cin.sync_with_stdio(false);
    int N,M,Q;
    cin >> N >> M >> Q;


    vector<tuple<int,int,int>> queries;
    vector<int> keep(Q+1);
    REP(q,Q) {
        int type;
        cin >> type;
        if (type == 1 || type == 2) {
            int i,j;
            cin >> i >> j;
            --i; --j;
            queries.pb( mt(type,i,j) );
        }
        else if (type == 3) {
            int i;
            cin >> i;
            --i;
            queries.pb( mt(type,i,-999) );
        }
        else {
            int i;
            cin >> i;
            queries.pb( mt(type,i,-999) );
            ++keep[i];
        }
    }

    State cur;
    cur.rev = vector<bool>(N);
    cur.sum = 0;

    map<int,State> history;
    if (keep[0]) {
        history[0] = cur;
    }
    
    int q = 0;
    for (auto& query : queries) {
        q++;

        int type = get<0>(query);
        int i = get<1>(query);
        int j = get<2>(query);
        if (type == 1 || type == 2) {

            auto old_num = (cur.rev[i]) ? (M - SIZE(cur.s[i])) : SIZE(cur.s[i]);

            if (type == 1) {
                if (cur.rev[i] == 0)
                    cur.s[i].insert(j);
                else
                    cur.s[i].erase(j);
            }
            else {
                if (cur.rev[i] == 0)
                    cur.s[i].erase(j);
                else
                    cur.s[i].insert(j);
            }

            auto new_num = (cur.rev[i]) ? (M - SIZE(cur.s[i])) : SIZE(cur.s[i]);
            cur.sum = (cur.sum - old_num + new_num);
        }
        else if (type == 3) {
            auto old_num = (cur.rev[i]) ? (M - SIZE(cur.s[i])) : SIZE(cur.s[i]);

            cur.rev[i] = (cur.rev[i] == 0) ? 1 : 0;

            auto new_num = (cur.rev[i]) ? (M - SIZE(cur.s[i])) : SIZE(cur.s[i]);
            cur.sum = (cur.sum - old_num + new_num);
        }
        else {
            cur = history[i];

            // forget
            --keep[i];
            if (keep[i] == 0) {
                history.erase(i);
            }
        }
        cout << cur.sum << endl;

        if (keep[q]) {
            history[q] = cur;
        }

    }

    return 0;
}
