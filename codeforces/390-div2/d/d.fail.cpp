#include <iostream>
#include <sstream>
#include <string>
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

int main(void)
{
    cin.sync_with_stdio(false);
    int N, K;
    cin >> N >> K;

    vector<pair<int,int>> LR(N);
    REP(n,N) {
        cin >> LR[n].first >> LR[n].second;
    }

    // // <loc, id, +1(add)/-1(remove)>
    // set<tuple<int,int,int>> events;

    // key: <loc, +1(add)/-1(remove)>  value: list of id
    map<pair<int,int>, set<int>> events;
    REP(n,N) {
        auto& lr = LR[n];
        events[mp(lr.first, 1)].insert(n);
        events[mp(lr.second+1, -1)].insert(n);
    }

    int mx = 0;
    set<int> ans;
    
    set<int> exist_ids;
    // <id, <start_pos, friend_ids>>
    map<int, pair<int, set<int>>> infos;
    for(auto& event: events) {
        auto loc = event.first.first;
        auto flag = event.first.second;
        auto& ids = event.second;

        if (flag == 1) {
            for(auto id: ids) {
                exist_ids.insert(id);
            }
            if (SIZE(exist_ids) >= K) {
                for(auto id: ids) {
                    infos[id] = mp(loc, exist_ids);
                }
            }
        }
        else {
            for(auto id: ids) {
                exist_ids.erase(id);
            }
            vector<int> erase_list;
            for (auto& info : infos) {
                auto kept = info.second.second;
                for(auto id: ids) {
                    info.second.second.erase(id);
                }
                if (SIZE(info.second.second) < K || ids.count(info.first)) {
                    auto len = loc - info.second.first;
                    if (len > mx) {
                        mx = len;
                        ans = kept;
                    }
                    erase_list.pb(info.first);
                }
            }
            for(auto id: erase_list) infos.erase(id);
        }
    }

    cout << mx << endl;
    if (mx == 0) {
        REP(k,K) {
            if (k != 0) cout << " ";
            cout << (k+1);
        }
        cout << endl;
    }
    else {
        vector<int> ans_vec(ALL(ans));
        REP(k,K) {
            if (k != 0) cout << " ";
            cout << (ans_vec[k]+1);
        }
        cout << endl;
    }

    return 0;
}
