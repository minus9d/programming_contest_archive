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
#include <cstring>
#include <fstream>

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

using namespace std;


struct edge { ll u, v, cost; };

class UnionFind
{
public:
    UnionFind(){};
    ~UnionFind(){};

    void Init(int num_entries) {
        num_entries_ = num_entries;
        par_.resize(num_entries_);
        rank_.resize(num_entries_, 0);
        for (int i = 0; i < num_entries_; ++i)
        {
            par_[i] = i;
        }
    }
    int Find(int x) {
        if (par_[x] == x)
        {
            return x;
        }
        else
        {
            return par_[x] = Find(par_[x]);
        }
    }

    void Unite(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;

        if (rank_[x] < rank_[y])
        {
            par_[x] = y;
        }
        else
        {
            par_[y] = x;
            if (rank_[x] == rank_[y])
            {
                rank_[x]++;
            }
        }
    }
    bool Same(int x, int y) {
        return Find(x) == Find(y);
    }

private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
};



class Kruskal {

private:

// costが小さい順にソート
static bool comp(const edge& e1, const edge& e2) {
    return e1.cost < e2.cost;
}

public:

// クラスカル法で最小全域木を求める
static pair<ll, set<pair<int, int>>>  kruskal(vector<edge>& edges, int V)
{
    sort(ALL(edges), comp);
    UnionFind uf;
    uf.Init(V);

    ll res = 0;
    set<pair<int, int>> used_edges;

    ll E = edges.size();
    REP(i, E) {
        edge e = edges[i];
        if (!uf.Same(e.u, e.v)) {
            uf.Unite(e.u, e.v);
            res += e.cost;
            used_edges.insert({e.u, e.v});
        }
    }
    return mp(res, used_edges);
}

};



class RailwayMaster {
    public:
    int maxProfit(int N, int M, int K, vector<int> a, vector<int> b, vector<int> v) {
        ll value_sum = accumulate(ALL(v), 0LL);

        vector<edge> edges;
        REP(m, M) {
            edges.pb({a[m], b[m], v[m]});
        }
        auto res = Kruskal::kruskal(edges, N);
        auto remain_value = get<0>(res);
        auto used_edges = get<1>(res);

        auto remain_num = SIZE(used_edges);
        auto removed_num = M - remain_num;

        if (removed_num <= K) {
            return value_sum - remain_value;
        }

        vector<ll> others;
        REP(m, M) {
            if (! used_edges.count(mp(a[m], b[m]))) {
                others.pb(v[m]);
            }
        }
        sort(ALL(others));
        reverse(ALL(others));
        ll ans = 0;
        REP(k, K) {
            ans += others[k];
        }
        return ans;
    }
};

// CUT begin
ifstream data("RailwayMaster.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int N, int M, int K, vector<int> a, vector<int> b, vector<int> v, int __expected) {
    time_t startClock = clock();
    RailwayMaster *instance = new RailwayMaster();
    int __result = instance->maxProfit(N, M, K, a, b, v);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        int N;
        from_stream(N);
        int M;
        from_stream(M);
        int K;
        from_stream(K);
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        vector<int> v;
        from_stream(v);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, K, a, b, v, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1595588714;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "RailwayMaster (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
