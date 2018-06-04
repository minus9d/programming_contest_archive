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

ll make_move(ll &pos, ll l, ll r) {
    ll move = 0;
    if (l <= pos && pos <= r) {
        // do nothing
    }
    else if (pos < l) {
        move += abs(pos - l);
        pos = l;
    }
    else if (pos > r) {
        move += abs(pos - r);
        pos = r;
    }
    return move;
}

ll solve(ll N, vector<pair<ll, ll>>& LRs) {
    map<pair<ll, ll>, int> remain;
    vector<tuple<ll, ll, ll>> Ls(N);
    vector<tuple<ll, ll, ll>> Rs(N);
    REP(i, N) {
        auto lr = LRs[i];
        auto l = lr.first;
        auto r = lr.second;
        ++remain[lr];
        Ls[i] = mt(-l, l, r);
        Rs[i] = mt(r, l, r);
    }
    sort(ALL(Ls));
    sort(ALL(Rs));

    ll pos = 0;
    ll move = 0;
    int l_idx = 0;
    int r_idx = 0;
    REP(i, N) {
        if (i % 2 == 0) {
            ll l = 0;
            ll r = 0;
            while (1) {
                auto nxt = Ls[l_idx];
                l = get<1>(nxt);
                r = get<2>(nxt);
                if (remain[mp(l, r)] != 0) {
                    break;
                }
                ++l_idx;
            }
            --remain[mp(l, r)];
            ++l_idx;
            move += make_move(pos, l, r);
        }
        else {
            ll l = 0;
            ll r = 0;
            while (1) {
                auto nxt = Rs[r_idx];
                l = get<1>(nxt);
                r = get<2>(nxt);
                if (remain[mp(l, r)] != 0) {
                    break;
                }
                ++r_idx;
            }
            --remain[mp(l, r)];
            ++r_idx;
            move += make_move(pos, l, r);

        }
    }
    move += abs(pos);
    return move;

    //vector<ll> Ls;
    //vector<ll> Rs;
    //for (auto lr : LRs) {
    //    auto l = lr.first;
    //    auto r = lr.second;
    //    if (l > 0) Ls.push_back(l);
    //    else if (r < 0) Rs.push_back(r);
    //}
    //sort(ALL(Ls));
    //sort(ALL(Rs));



    //int i = 0;
    //ll ans = 0;
    //int pos = 0;
    //int i_end = min(SIZE(Ls), SIZE(Rs));
    //REP(i, i_end) {
    //    ans += abs(Ls[i] - pos);
    //    pos = Ls[i];
    //    ans += abs(Rs[i] - pos);
    //    pos = Rs[i];
    //}
    //if (SIZE(Ls) > i_end) {
    //    ans += (Ls.back()) - pos)
    //}

}

ll slow(ll N, vector<pair<ll,ll>>& LRs) {
    vector<ll> shff(N);
    REP(n, N) shff[n] = n;
    ll ans = 0;
    vector<ll> best_shff;
    vector<ll> best_pos;

    do {
        ll pos = 0;
        ll move = 0;
        vector<ll> pos_hist;
        REP(n, N) {
            auto rng = LRs[shff[n]];
            if (rng.first <= pos && pos <= rng.second) {
                // do nothing
            }
            else if (pos < rng.first) {
                move += abs(pos - rng.first);
                pos = rng.first;
            }
            else if (pos > rng.second) {
                move += abs(pos - rng.second);
                pos = rng.second;
            }
            pos_hist.pb(pos);
        }
        move += abs(pos);
        if (move > ans) {
            ans = move;
            best_shff = shff;
            best_pos = pos_hist;
            cerr << "ans is update!";
            for(auto p: pos_hist) cerr << p << " ";
            cerr << endl;
        }
    } while(next_permutation(ALL(shff)));

    cerr << "best move:" << endl;
    REP(i, N) {
        auto rng = LRs[best_shff[i]];
        cerr << "  " << rng.first << ", " << rng.second << " (" << best_pos[i] << ")" <<  endl;
    }

    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N;
    cin >> N;
    vector<pair<ll,ll>> LRs(N);
    REP(n, N) cin >> LRs[n].first >> LRs[n].second;

    {
        while (true) {
            //N = 5 + rand() % 3;
            N = 2;
            vector<pair<ll, ll>> LRs(N);
            REP(n, N) {
                auto L = rand() % 10 - 5;
                auto R = L + (rand() % 10) + 1;
                LRs[n] = mp(L, R);

                //if (rand() % 2) {
                //    auto L = rand() % 10 - 30;
                //    auto R = L + (rand() % 10) + 1;
                //    LRs[n] = mp(L, R);
                //}
                //else {
                //    auto L = rand() % 10 + 30;
                //    auto R = L + (rand() % 10) + 1;
                //    LRs[n] = mp(L, R);
                //}
            }
            if (slow(N, LRs) != solve(N, LRs)) {
                cerr << "error! N = " << N << ", LRs = ";
                for (auto lr : LRs) cerr << "[" << lr.first << "," << lr.second << "],";
                cerr << endl;
                cerr << "expected " << slow(N, LRs) << ", myans " << solve(N, LRs) << endl;
            }
        }

    }



    cout << slow(N, LRs) << endl;

    return 0;
}
