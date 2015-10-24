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

const int INF = 1e9;
class WF {

private:
    vector<vector<int>> m_d;
    int m_v;

public:

    void init(int v) {
        m_v = v;
        m_d.resize(v);
        REP(i, v) m_d[i].resize(v);
        REP(i,v) REP(j,v) {
            if (i == j) m_d[i][j] = 0;
            else m_d[i][j] = INF;
        }
    }

    void setOneDirCost(int s, int e, int cost) {
        m_d[s][e] = cost;
    }
    void setTwoDirCost(int v1, int v2, int cost) {
        setOneDirCost(v1, v2, cost);
        setOneDirCost(v2, v1, cost);
    }
    vector<vector<int>> run(){
        REP(k, m_v){
            REP(i, m_v){
                REP(j, m_v){
                    m_d[i][j] = min(m_d[i][j], m_d[i][k] + m_d[k][j]);
                }
            }
        }
        return m_d;
    }
};

string solve()
{
    int N;
    cin >> N;
    vector<vector<ll>> cells(N, vector<ll>(N));
    REP(n1,N) REP(n2,N) cin >> cells[n1][n2];

    REP(n,N) if (cells[n][n] != 0) return "NO";

    WF wf;
    wf.init(N);
    REP(n1,N) REP(n2,N) {
        auto cost = cells[n1][n2];
        if (cost != -1 && cost != 0) 
            wf.setOneDirCost(n1,n2,cost);
    }

    auto ret = wf.run();
    // REP(n1,N) {
    //     REP(n2,N) cout << ret[n1][n2];
    //     cout << endl;
    // }

    REP(n1,N) REP(n2,N) {
        if (n1 == n2) continue;
        auto d1 = cells[n1][n2];
        auto d2 = ret[n1][n2];
        if (d1 == -1) {
            if (d2 != INF) return "NO";
        }
        else if (d1 != d2) return "NO";
    }
    
    return "YES";
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    
    REP(t,T) {
        auto ret = solve();
        cout << ret << endl;
    }
    return 0;
}
