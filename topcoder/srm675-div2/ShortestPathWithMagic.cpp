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


#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;


const int INF = 100000000;
using namespace std;
typedef struct {int to, cost; } edge;
typedef tuple<double, int, int> P; // minimum cost, vertex No, num of paths

using Shortest = vector<vector<double>>;
using Pathcosts = vector<vector< vector<int> >>;

class ShortestPathWithMagic {
public:


    double calccost(vector<int> costs, int newcost, int k) {
        double ret = 0;
        costs.pb(newcost);
        sort(ALL(costs));
        for(auto it = costs.rbegin();
            it != costs.rend();
            ++it) {
            if (k > 0) {
                ret += *it / 2.0;
                --k;
            }
            else {
                ret += *it;
            }
        }
        return ret;
    }

    bool shouldBeReplaced(vector<int>& costs1, vector<int> costs2, int cost) { 
        costs2.pb(cost);
        sort(ALL(costs1), greater<int>());
        sort(ALL(costs2), greater<int>());
        REP(i, SIZE(costs1)) {
            if (costs2[i] > costs1[i]) return true;
            else if (costs2[i] < costs1[i]) return false;
        }
        return false;
    }

    double getTime(vector <string> dist, int k) {
        int s = 0;
        int n = SIZE(dist);

        // contains shortest distance from capital
        // [vertex][num of paths]
        Shortest shortest(n + 5, vector<double>(n + 5,INF));
        shortest[s][0] = 0;

        Pathcosts pathcosts(n + 5, vector<vector<int>>(n + 5));

        // dijkstra
        priority_queue<P, vector<P>, greater<P> > que;
        que.push(P(0, s, 0));
        while(!que.empty()){
            P p = que.top();
            que.pop();

            auto cost = get<0>(p);
            auto v = get<1>(p);
            auto paths = get<2>(p);
            if (shortest[v][paths] < cost) {
                continue;
            }

            if (paths >= n - 1) continue;

            REP(v2, n) {
                if (v == v2) continue;
                double newcost = calccost(pathcosts[v][paths], dist[v][v2] - '0', k);

                if ( ((shortest[v2][paths + 1] == newcost) && shouldBeReplaced(pathcosts[v2][paths + 1], pathcosts[v][paths], dist[v][v2] - '0'))
                    || 
                     (shortest[v2][paths + 1] > newcost))
                {
                    shortest[v2][paths + 1] = newcost;
                    pathcosts[v2][paths + 1] = pathcosts[v][paths];
                    pathcosts[v2][paths + 1].pb(dist[v][v2] - '0');
                    que.push(P(shortest[v2][paths + 1], v2, paths + 1));
                }
            }
        }

        double result = 1e9;
        FOR(i,1,n) {
            result = min(result, shortest[1][i]);
        }

        return result;
    }

  
// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"094",
                                          "904",
                                          "440"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; double Arg2 = 4.5; verify_case(0, Arg2, getTime(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"094",
                                          "904",
                                          "440"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; double Arg2 = 4.0; verify_case(1, Arg2, getTime(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"094",
                                          "904",
                                          "440"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; double Arg2 = 4.0; verify_case(2, Arg2, getTime(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"094",
                                          "904",
                                          "440"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; double Arg2 = 8.0; verify_case(3, Arg2, getTime(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"076237",
                                          "708937",
                                          "680641",
                                          "296059",
                                          "334508",
                                          "771980"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; double Arg2 = 3.5; verify_case(4, Arg2, getTime(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"00",
                                          "00"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; double Arg2 = 0.0; verify_case(5, Arg2, getTime(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  ShortestPathWithMagic ___test;
  ___test.run_test(-1);
}
// END CUT HERE

