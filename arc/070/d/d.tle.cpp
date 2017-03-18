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

ll brute_force(const vector<ll>& As_orig, ll K) {
    ll N = SIZE(As_orig);
    // sort(ALL(As_orig));
    map<ll, set<ll>> possible_set;
    REP(i, 1 << N) {
        ll s = 0;
        REP(j, N) {
            if ((1 << j) & i) {
                s += As_orig[j];
            }
        }
        if (s >= K) {
            REP(j, N) {
                if ((1 << j) & i) {
                    possible_set[As_orig[j]].insert(s);
                }
            }
        }
    }
    int ans = 0;
    for(auto a: As_orig) {
        if (SIZE(possible_set[a]) == 0) ++ans;
        else {
            if (*possible_set[a].begin() - a >= K) {
                ++ans;
            }
        }
    }
    return ans;
}

ll solve(const vector<ll>& As_orig, ll K) {
    ll N = SIZE(As_orig);
    vector<ll> As;
    ll sum = 0;
    for(auto a : As_orig) {
        sum += a;
        // if (a < K) As.pb(a);
        As.pb(a);
    }
    sort(ALL(As));

    if (sum < K) {
        return N;
    }

    // K = 20, a = 7の場合
    // 和が20, 21, ..., 26のいずれかになるような集合が一つでも存在すれば
    // 7は不可欠
    int ans = 0;
    REP(i, SIZE(As)) {
        auto ai = As[i];
        if (ai >= K) break;
        set<ll> poss;
        poss.insert(0);
        REP(j, SIZE(As)) {
            auto aj = As[j];
            if (j == i) continue;
            vector<ll> add;
            for (auto p : poss) {
                // if (p + aj > 2 * K) break;
                if (p > 2 * K) break;
                else add.pb(p + aj);
            }
            for(auto ad: add) poss.insert(ad);
        }

        auto lb = lower_bound(ALL(poss), K-ai);
        // cout << "ai, lb = " << ai << "," << *lb << endl;
        if (lb != poss.end()  &&   *lb >= K) {
            ans += 1;
        }
    }
    return ans;
}

void check() {
    // check
    ll K = 20;
    ll N = 8;
    while(true) {
        vector<ll> As;
        REP(n, N) {
            As.pb( rand() % (K * 2) + 1 );
        }
        ll ans1 = solve(As, K);
        ll ans2 = brute_force(As, K);
        if (ans1 != ans2) {
            cout << "error!" << endl;
            cout << "ans1:" << ans1 << endl;
            cout << "ans2:" << ans2 << endl;
            for(auto a: As) {
                cout << a << " ";
            }
            cout << endl;
            break;
        }
    }
}
 
int main(void)
{
    cin.sync_with_stdio(false);
    ll N, K;
    cin >> N >> K;
    vector<ll> As_orig;
    REP(n,N) {
        ll a;
        cin >> a;
        As_orig.pb(a);
    }
    ll ans = solve(As_orig, K);
    cout << ans << endl;

    // check();
    
    return 0;
}

