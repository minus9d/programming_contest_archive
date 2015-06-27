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


class CanMove {
public:
    void init(int a) {
        move_s = a;
        move_t = a;
    }
    void add(int s, int t) {
        if (t < move_s || move_t < s) {
        }
        else {
            move_s = min(move_s, s);
            move_t = max(move_t, t);
        }

        // cout << "current move: " << move_s << " to " << move_t << endl;
    }
    bool cango(int a) {
        return move_s <= a && a <= move_t;
    }

private:
    int move_s;
    int move_t;
};


int main(void)
{
    cin.sync_with_stdio(false);
    int N, D, K;
    cin >> N >> D >> K;

    vector<int> Ls(D);
    vector<int> Rs(D);
    vector<int> Ss(K);
    vector<int> Ts(K);

    REP(d,D) {
        cin >> Ls[d] >> Rs[d];
    }
    REP(k,K) {
        cin >> Ss[k] >> Ts[k];
    }

    REP(k,K) {
        CanMove cm;
        cm.init(Ss[k]);
        REP(d,D){
            cm.add(Ls[d],Rs[d]);
            if (cm.cango(Ts[k])) {
                cout << (d+1) << endl;
                break;
            }
        }
    }
    
    return 0;
}
