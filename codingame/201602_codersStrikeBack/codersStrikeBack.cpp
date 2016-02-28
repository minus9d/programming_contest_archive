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
    int x;
    int y;
    int vx;
    int vy;
    int angle;
    int nextCheckPointId;
};


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int laps;
    cin >> laps; cin.ignore();

    int cp_num;
    cin >> cp_num; cin.ignore();

    vector<P> cps(cp_num);
    REP(i, cp_num) {
        cin >> cps[i].x >> cps[i].y;
        cin.ignore();
    }

    // game loop
    while (1) {
        vector<Pod> pods(2);
        REP(i,2) {
            cin >> pods[i].x >> pods[i].y
                >> pods[i].vx >> pods[i].vy
                >> pods[i].angle >> pods[i].nextCheckPointId;
            cin.ignore();
        }
        vector<Pod> opps(2);
        REP(i,2) {
            cin >> opps[i].x >> opps[i].y
                >> opps[i].vx >> opps[i].vy
                >> opps[i].angle >> opps[i].nextCheckPointId;
            cin.ignore();
        }

        cout << cps[pods[0].nextCheckPointId].x << " "
             << cps[pods[0].nextCheckPointId].y << " "
             << "100" << endl;
        cout << cps[pods[1].nextCheckPointId].x << " "
             << cps[pods[1].nextCheckPointId].y << " "
             << "100" << endl;
    }
}
