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

vector<ll> solve_slow(ll K, ll Q, vector<ll> &Ds, vector<tuple<ll, ll, ll>> &queries) {
    vector<ll> answers;
    for (auto &query : queries) {
        ll n, x, m;
        tie(n, x, m) = query;

        cout << "start" << endl;
        // vector<ll> A(n); // for debug
        vector<ll> A(1000);
        cout << "end" << endl;
        
        A[0] = x;
        FOR(i, 1, n) {
            A[i] = A[i - 1] + Ds[(i - 1) % K];
            if (i == 100) break; // for debug!!!
        }

        REP(j, min(n - 1, 20ll)) {
            cout << (A[j] % m) << ", ";
        }
        cout << endl;

        ll ans = 0;
        REP(j, n - 1) {
            ans += (A[j] % m) < (A[j+1] % m);
            if (j == 100) break; // for debug!!!
        }


        answers.pb(ans);
    }
    return answers;
}

vector<ll> solve_fast(ll K, ll Q, vector<ll> &Ds, vector<tuple<ll, ll, ll>> &queries) {

    auto cum = Ds;
    FOR(k, 1, K) cum[k] += cum[k-1];

    vector<ll> answers;
    for (auto &query : queries) {
        ll n, x, m;
        tie(n, x, m) = query;

        auto cum2 = cum;
        for(auto& e: cum2) e %= m;

        cout << endl;
        for(auto e: cum) cout << e << "," << endl;
        cout << endl;
        for(auto e: cum2) cout << e << "," << endl;
        cout << endl;

        cout << "start" << endl;
        // vector<ll> A(n); // for debug
        vector<ll> A(1000);
        cout << "end" << endl;
        
        A[0] = x;
        FOR(i, 1, n) {
            A[i] = A[i - 1] + Ds[(i - 1) % K];
            if (i == 100) break; // for debug!!!
        }

        REP(j, min(n - 1, 20ll)) {
            cout << (A[j] % m) << ", ";
        }
        cout << endl;

        ll ans = 0;
        REP(j, n - 1) {
            ans += (A[j] % m) < (A[j+1] % m);
            if (j == 100) break; // for debug!!!
        }


        answers.pb(ans);
    }
    return answers;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll K, Q;
    cin >> K >> Q;
    vector<ll> Ds(K);
    REP(k, K) cin >> Ds[k];
    vector<tuple<ll, ll, ll>> queries(Q);
    REP(q, Q) {
        ll n, x, m;
        cin >> n >> x >> m;
        queries[q] = mt(n, x, m);
    }
    // auto answers_slow = solve_slow(K, Q, Ds, queries);
    // for(auto ans: answers_slow) cout << ans << endl;

    auto answers_fast = solve_fast(K, Q, Ds, queries);
    for(auto ans: answers_fast) cout << ans << endl;

    return 0;
}
