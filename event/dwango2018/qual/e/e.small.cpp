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


int N, Q;

int find_farthest(vector<set<int>>& edges, int start_v) {
    set<int> seen;
    set<int> cur;
    cur.insert(start_v);
    seen.insert(start_v);

    while(true) {
        set<int> next_set;
        for (auto v: cur) {
            for(auto v2: edges[v]) {
                if (!seen.count(v2)) {
                    next_set.insert(v2);
                    seen.insert(v2);
                }
            }
        }
        if (SIZE(next_set) == 0) return *cur.begin();
        cur = next_set;
    }
}

tuple<int, int> find_diameter(vector<set<int>>& edges, set<int>& Vs) {
    int v1 = *Vs.begin();
    auto v2 = find_farthest(edges, v1);
    auto v3 = find_farthest(edges, v2);
    return mt(v2, v3);
}

vector<int> get_distance(vector<set<int>>& edges, int start_v) {
    vector<int> ret(N);

    set<int> seen;
    set<int> cur;
    cur.insert(start_v);
    seen.insert(start_v);

    int dist = 0;
    while(true) {
        set<int> next_set;
        for (auto v: cur) {
            ret[v] = dist;
            for(auto v2: edges[v]) {
                if (!seen.count(v2)) {
                    next_set.insert(v2);
                    seen.insert(v2);
                }
            }
        }
        if (SIZE(next_set) == 0) break;
        ++dist;
        cur = next_set;
    }
    return ret;
}

void trim_edges(vector<set<int>>& edges, set<int>& Vs) {
    REP(n, N) {
        if (Vs.count(n)) {
            set<int> tmp;
            for(auto v2: edges[n]) {
                if (Vs.count(v2)) tmp.insert(v2);
            }
            edges[n] = tmp;
        }
        else {
            edges[n].clear();
        }
    }
}

void keep_same_distance(vector<set<int>>& edges, set<int>& Vs, int v1, int v2) {
    auto dist1 = get_distance(edges, v1);
    auto dist2 = get_distance(edges, v2);
    vector<set<int>> new_edges;
    set<int> new_Vs;
    for(auto v: Vs) {
        if (dist1[v] == dist2[v]) new_Vs.insert(v);
    }
    Vs = new_Vs;
    trim_edges(edges, Vs);
}

void keep_nearest(vector<set<int>>& edges, set<int>& Vs, int v1, int v2) {
    auto dist1 = get_distance(edges, v1);
    auto dist2 = get_distance(edges, v2);
    set<int> new_Vs;
    for(auto v: Vs) {
        if (dist1[v] < dist2[v]) new_Vs.insert(v);
    }
    Vs = new_Vs;
    trim_edges(edges, Vs);
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N >> Q;
    set<int> Vs;
    vector<set<int>> edges(N);
    REP(n, N) Vs.insert(n);
    REP(n, N-1) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        edges[a].insert(b);
        edges[b].insert(a);
    }

    // for debug
    //auto ret = get_distance(edges, 0);
    //REP(n, N) cout << ret[n] << "," ;
    //cout << endl;

    //keep_same_distance(edges, Vs, 1, 3);

    while(true) {
        int v1, v2;
        tie(v1, v2) = find_diameter(edges, Vs);
        cout << "? " << (v1 + 1) << " " << (v2 + 1) << endl;
        fflush(stdout);

        int ans;
        cin >> ans;

        if (ans == 0) {
            keep_same_distance(edges, Vs, v1, v2);
        }
        else if (ans == (v1 + 1)) {
            keep_nearest(edges, Vs, v1, v2);
        }
        else {
            keep_nearest(edges, Vs, v2, v1);
        }

        //cerr << "cur V: ";
        //for (auto v : Vs) cerr << v << " ";
        //cerr << endl;

        if (SIZE(Vs) == 1) {
            cout << "! " << (*Vs.begin() + 1) << endl;
            fflush(stdout);
            break;
        }
    }

    return 0;
}
