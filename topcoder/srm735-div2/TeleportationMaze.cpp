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

template <typename T>
class Dijkstra {
    struct edge { int to; T cost; };
    typedef pair<T, int> P; // <最短距離, 頂点番号>

private:
    int m_V;
    vector<vector<edge> > m_G;
public:
    const T INF = std::numeric_limits<T>::max();
    vector<int> m_prev_path; // 最短パスを辿るため

    Dijkstra(int V) : m_V(V) {
        m_G.resize(m_V);
    }

    // a -> bに片方向のエッジを張る
    void add_dir_edge(int a, int b, T cost) {
        m_G[a].push_back( edge{ b, cost } );
    }

    // a <-> bに両方向のエッジを張る
    void add_undir_edge(int a, int b, T cost) {
        add_dir_edge(a, b, cost);
        add_dir_edge(b, a, cost);
    }

    // 頂点sから各頂点までの距離を計算して返す
    vector<T> shortest_path(int s) {
        m_prev_path.clear(); m_prev_path.resize(m_V, -1);

        vector<T> d(m_V, INF);
        priority_queue<P, vector<P>, greater<P> > que;
        d[s] = 0;
        que.push(P(0, s));

        while(!que.empty()) {
            P p = que.top();
            que.pop();

            auto dist = p.first;
            auto v = p.second;
            if (d[v] < dist) continue;
            REP(i, m_G[v].size()) {
                edge e = m_G[v][i];
                if (d[e.to] > d[v] + e.cost) {
                    d[e.to] = d[v] + e.cost;
                    que.push(P(d[e.to], e.to));
                    m_prev_path[e.to] = v;
                }
            }
        }

        return d;
    }

    // shortest_path()が呼ばれた後に呼ばれることを期待する
    // s -> v1 -> v2 -> v3 -> t の場合、{s, v1, v2, v3, t} からなるvectorを返す
    vector<int> get_path(int t)
    {
        vector<int> path;
        for(; t != -1; t = m_prev_path[t]) path.push_back(t);
        reverse(ALL(path));
        return path;
    }
};

class TeleportationMaze {
    public:
    int H;
    int W;
    int V;

    int to_idx(int h, int w) {
        return h * W + w;
    }

    void get_next_w(vector<string>& a, int h, int w, int& next_w) {
        next_w = -1;
        FOR(w2, w+1, W) {
            if (a[h][w2] == '.') {
                next_w = w2;
                return;
            }
        }
    }
    void get_next_h(vector<string>& a, int h, int w, int& next_h) {
        next_h = -1;
        FOR(h2, h+1, H) {
            if (a[h2][w] == '.') {
                next_h = h2;
                return;
            }
        }
    }

    int pathLength(vector<string> a, int r1, int c1, int r2, int c2) {
        H = SIZE(a);
        W = SIZE(a[0]);
        V = H * W;

        Dijkstra<int> dij(V);
        REP(h, H) {
            REP(w, W) {
                if (w != W-1) {
                    if (a[h][w] == '#') continue;
                    if (a[h][w+1] == '.') {
                        dij.add_undir_edge(to_idx(h, w), to_idx(h, w+1), 1);
                    }
                    else {
                        int next_w;
                        get_next_w(a, h, w, next_w);
                        if (next_w != -1) {
                            dij.add_undir_edge(to_idx(h, w), to_idx(h, next_w), 2);
                        }
                    }
                }
                if (h != H-1) {
                    if (a[h][w] == '#') continue;
                    if (a[h+1][w] == '.') {
                        dij.add_undir_edge(to_idx(h, w), to_idx(h+1, w), 1);
                    }
                    else {
                        int next_h;
                        get_next_h(a, h, w, next_h);
                        if (next_h != -1) {
                            dij.add_undir_edge(to_idx(h, w), to_idx(next_h, w), 2);
                        }
                    }
                }
            }
        }

        auto start_idx = to_idx(r1, c1);
        auto goal_idx = to_idx(r2, c2);
        auto res = dij.shortest_path(start_idx);

        if (res[goal_idx] == dij.INF) return -1;
        else return res[goal_idx];
    }
};

// CUT begin
ifstream data("TeleportationMaze.sample");

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

bool do_test(vector<string> a, int r1, int c1, int r2, int c2, int __expected) {
    time_t startClock = clock();
    TeleportationMaze *instance = new TeleportationMaze();
    int __result = instance->pathLength(a, r1, c1, r2, c2);
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
        vector<string> a;
        from_stream(a);
        int r1;
        from_stream(r1);
        int c1;
        from_stream(c1);
        int r2;
        from_stream(r2);
        int c2;
        from_stream(c2);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, r1, c1, r2, c2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1530011325;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TeleportationMaze (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
