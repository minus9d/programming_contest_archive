#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

struct P {
    int x;
    int y;
};

struct Pod {
    P pos;
    int vx;
    int vy;
    int angle;
    int nextCheckPointId;
};

void debug_print(Pod& p) {
}


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

vector<P> cps;

int pow2(int x) { return x*x; }

int dist(const P& p1, const P& p2) {
    return sqrt(pow2(p1.x - p2.x) + pow2(p1.y - p2.y));   
}

int decide_speed(const Pod& p)
{
    const auto& n_cp = cps[p.nextCheckPointId];
    // const auto& nn_cp = cps[(p.nextCheckPointId + 1) % cps.size()];

    auto d = dist(p.pos, n_cp);
    if (d > 2000) return 200;
    else return 80;
}

int main()
{
    int laps;
    cin >> laps; cin.ignore();

    int cp_num;
    cin >> cp_num; cin.ignore();

    cps.resize(cp_num);
    REP(i, cp_num) {
        cin >> cps[i].x >> cps[i].y;
        cin.ignore();
    }
    
    // game loop
    int cnt = 0;
    while (1) {
        vector<Pod> pods(2);
        REP(i,2) {
            cin >> pods[i].pos.x >> pods[i].pos.y
                >> pods[i].vx >> pods[i].vy
                >> pods[i].angle >> pods[i].nextCheckPointId;
            cin.ignore();
        }
        vector<Pod> opps(2);
        REP(i,2) {
            cin >> opps[i].pos.x >> opps[i].pos.y
                >> opps[i].vx >> opps[i].vy
                >> opps[i].angle >> opps[i].nextCheckPointId;
            cin.ignore();
        }

        debug_print(pods[0]);
        debug_print(pods[1]);

        auto speed0 = decide_speed(pods[0]);

        cout << cps[pods[0].nextCheckPointId].x << " "
             << cps[pods[0].nextCheckPointId].y << " "
             << speed0 << endl;
        cout << cps[pods[1].nextCheckPointId].x << " "
             << cps[pods[1].nextCheckPointId].y << " "
             << "110" << endl;
             
        fprintf(stderr, "\n"); 
        ++cnt;
    }
}

