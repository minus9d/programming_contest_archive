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
#include <tuple>
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
    // (h, w)
    vector<pair<int,int>> locs;
    vector<pair<int,int>> goals;
};
State s;

string move_to_string(const pair<int,int>& p) {
    if (p == mp(0, 0)) return "-";
    else if (p == mp(1, 0)) return "D";
    else if (p == mp(-1, 0)) return "U";
    else if (p == mp(0, 1)) return "R";
    else if (p == mp(0, -1)) return "L";
    return "?";
}
int count_move_num(string s) {
    int num = 0;
    for(auto ch: s) num += ch != '-';
    return num;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int H, W, K, T;
    cin >> H >> W >> K >> T;

    s.locs.resize(K);
    s.goals.resize(K);

    vector<tuple<int,int,int,int>> ABCDs(K);
    REP(k, K) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        ABCDs[k] = mt(a, b, c, d);
        s.locs[k] = mp(a, b);
        s.goals[k] = mp(c, d);
    }

    vector<string> anses;
//    REP(t, T) {
    REP(t, 5000) {
        set<pair<int,int>> occupied;
        REP(k, K) {
            occupied.insert(s.locs[k]);
        }
        string ans;
        REP(k, K) {
            if (s.locs[k] == s.goals[k]) {
                ans += '-';
            }
            
            else {
                vector<pair<int,int>> poss_move;
                if (s.locs[k].first < s.goals[k].first) poss_move.pb(mp(1,0));
                if (s.locs[k].first > s.goals[k].first) poss_move.pb(mp(-1,0));
                if (s.locs[k].second < s.goals[k].second) poss_move.pb(mp(0,1));
                if (s.locs[k].second > s.goals[k].second) poss_move.pb(mp(0,-1));
                random_shuffle(ALL(poss_move));
                bool found = false;
                for (auto m : poss_move) {
                    auto new_loc = s.locs[k];
                    new_loc.first += m.first;
                    new_loc.second += m.second;
                    if (!occupied.count(new_loc)) {
                        occupied.insert(new_loc);
                        ans += move_to_string(m);
                        found = true;
                        s.locs[k] = new_loc;
                        break;
                    }
                }
                if (!found) ans += '-';
            }
        }

        auto move_num = count_move_num(ans);
        if (move_num < 10) {
            break;
        }
        anses.pb(ans);
    }
    
    cout << SIZE(anses) << endl;
    for(auto ans: anses) {
        cout << ans << endl;
    }

    return 0;
}

