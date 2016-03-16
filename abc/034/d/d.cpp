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

int main(void)
{
    cin.sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    vector<ll> ws(N);
    vector<ll> ps(N);
    vector<ll> saltsX100(N);

    ll mx = -1;
    ll mx_idx = -1;
    REP(n,N) {
        cin >> ws[n] >> ps[n];
        saltsX100[n] = ws[n] * ps[n];
        if (ps[n] > mx) {
            mx = ps[n];
            mx_idx = n;
        }
    }

    ll chosen = 1;
    vector<char> used(N);
    used[mx_idx] = 1;
    ll cur_salt_x100 = saltsX100[mx_idx];
    ll cur_water = ws[mx_idx];

    // 濃度が最大になるものを1つずつgreedyに選んでいく
    while(chosen < K) {
        ll i = -1;
        double best = -1;
        REP(n, N) {
            if (used[n]) continue;
            double con
                = (double)(cur_salt_x100 + saltsX100[n])
                / (cur_water + ws[n]);
            // cout << "  test " << n << ": " << con << endl;

            if (con > best) {
                best = con;
                i = n;
            }
        }
        
        used[i] = 1;
        cur_salt_x100 += saltsX100[i];
        cur_water += ws[i];

        // cout << i << " is chosen." << endl;
        // cout << "cur: " << (double)(cur_salt_x100 / cur_water) << endl;

        ++chosen;
    }

    printf("%.10lf\n", (double)cur_salt_x100 / cur_water);

    return 0;
}
