#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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

int too_slow(ll N, ll Q, vector<pair<ll, ll>>& LRs) {
    vector<int> shff(Q);
    REP(q, Q) shff[q] = q;
    int ans = 0;
    do {
        vector<char> seats(N + 1);
        int local_ans = -1;
        for(auto e: shff) {
            auto lr = LRs[e];
            int got = 0;
            FOR(i, lr.first, lr.second + 1) {
                if (seats[i] == 0) { ++got; }
                seats[i] = 1;
            }
            if (local_ans == -1) local_ans = got;
            else local_ans = min(local_ans, got);
        }
        ans = max(ans, local_ans);
    }while(next_permutation(ALL(shff)));
    return ans;
}

int slow_fail(ll N, ll Q, vector<pair<ll, ll>>& LRs) {
    vector<char> seats(N + 1);
    vector<char> used(Q);
    int ans = 1e9;
    REP(rep, Q) {
        int chosen_q = -1;
        int min_got = 1e9;
        REP(q, Q) {
            if (used[q]) continue;
            auto lr = LRs[q];
            int got = 0;
            FOR(i, lr.first, lr.second + 1) {
                if (seats[i] == 0) { ++got; }
            }
            if (got < min_got) {
                min_got = got;
                chosen_q = q;
            }
        }
        used[chosen_q] = 1;
        ans = min(ans, min_got);
        auto lr = LRs[chosen_q];
        FOR(i, lr.first, lr.second + 1) {
            seats[i] = 1;
        }
    }
    return ans;
}

int slow(ll N, ll Q, vector<pair<ll, ll>>& oldLRs) {

    // comqpress
    set<ll> coords;
    ll max_r = 0;
    for (auto lr: oldLRs) {
        coords.insert(lr.first);
        coords.insert(lr.second);
        coords.insert(lr.second + 1);
        //max_r = max(max_r, lr.second);
    }
    //coords.insert(max_r + 1);
    map<int,int> old2new;
    map<int,int> new2old;
    int n = 0;
    for(auto o: coords) {
        old2new[o] = n;
        new2old[n] = o;
        ++n;
    }
    //cout << "old2new:" << endl;
    //for(auto kv: old2new) cout << kv.first << " -> " << kv.second << endl;

    vector<pair<ll, ll>> newLRs;
    for(auto lr: oldLRs) {
        newLRs.pb({old2new[lr.first], old2new[lr.second]});
    }

    int len = SIZE(coords);
    vector<char> used(len);

    vector<int> seats_sum(len);
    map<int, set<int>> q_coord;
    REP(q, Q) {
        auto lr = newLRs[q];
        FOR(i, lr.first, lr.second + 1) {
            seats_sum[i] += 1;
            q_coord[i].insert(q);
        }
    }

    //for(auto kv: q_coord) {
    //    cout << "q " << kv.first << ":" << SIZE(kv.second) << endl;
    //}

    int ans = int(1e9);
    REP(rep, Q) {
        vector<int> scores(Q);
        //REP(q, Q) {
            REP(i, len - 1) {
                if (SIZE(q_coord[i]) == 1) {
                    auto q = *q_coord[i].begin();
                    scores[q] += new2old[i + 1] - new2old[i];
                }
            }
        //}
        //cout << "scores:" << endl;
        //REP(q, Q) cout << scores[q] << endl;

        int best_q = -1;
        int best_score = -1;
        REP(q, Q) {
            if (scores[q] > best_score) {
                best_score = scores[q];
                best_q = q;
            }
        }
        ans = min(ans, best_score);

        auto lr = newLRs[best_q];
        FOR(i, lr.first, lr.second + 1) {
            q_coord[i].erase(best_q);
        }
    }
    return ans;
}

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<pair<ll, ll>> LRs(Q);

    REP(q, Q) {
        cin >> LRs[q].first >> LRs[q].second;
    }
    // cout << too_slow(N, Q, LRs);
    cout << slow(N, Q, LRs);
}

int main(void)
{
     //while(1) {
     //    ll N = 10;
     //    ll Q = 3;
     //    vector<pair<ll, ll>> LRs(Q);
     //    REP(q, Q) {
     //        while(true) {
     //            ll l = (rand() % N) + 1;
     //            ll r = (rand() % N) + 1;
     //            if (l <= r) {
     //                LRs[q] = mp(l, r);
     //                break;
     //            }
     //        }
     //    }
     //    auto gt = too_slow(N, Q, LRs);
     //    auto mine = slow(N, Q, LRs);
     //    if (gt != mine) {
     //        cout << "error!" << endl;
     //        cout << N << " " << Q << endl;
     //        REP(q, Q) {
     //            cout << LRs[q].first << " " << LRs[q].second << endl;
     //        }
     //        cout << "gt = " << gt << endl;
     //        cout << "mine = " << mine << endl;
     //        return 0;
     //    } else {
     //        cout << "ok" << endl;
     //    }
     //}


    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
