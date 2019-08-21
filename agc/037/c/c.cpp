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

ll N;

int get_next_idx(int i) {
    if (i == N - 1) return 0;
    else return i + 1;
}
int get_prev_idx(int i) {
    if (i == 0) return N - 1;
    else return i - 1;
}

ll get_next(int i, vector<ll>& arr) {
    return arr[get_next_idx(i)];
}
ll get_prev(int i, vector<ll>& arr) {
    return arr[get_prev_idx(i)];
}

bool is_peak(int i, vector<ll>& arr) {
    ll p = get_prev(i, arr);
    ll n = get_next(i, arr);
    return (arr[i] >= p + n);
}

ll solve_fast(int N, vector<ll> As, vector<ll> Bs) {
    priority_queue<ll, vector<ll>> q;
    // queue<ll> q;
    
    REP(i, N) {
        if (is_peak(i, Bs)) q.push(i);
    }

    ll fail = 0;
    ll ans = 0; // !!!
    while(!q.empty()) {
        if (fail == N) break;

        ll i = q.top(); q.pop();

        ll p = get_prev(i, Bs);
        ll n = get_next(i, Bs);

        ll num = (Bs[i] - As[i]) / (p + n);
        if (num > 0) {
            ans += num;
            Bs[i] -= num * (p + n);

            fail = 0;
            auto in = get_next_idx(i);
            auto ip = get_prev_idx(i);
            if (is_peak(in, Bs)) q.push(in);
            if (is_peak(ip, Bs)) q.push(ip);
        } else {
            ++fail; 
       }
    }

    bool ok = true;
    REP(i, N) {
        if (As[i] != Bs[i]) {
            ok = false;
            break;
        }
    }
    if (ok) return ans;
    else return -1;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> N;
    vector<ll> As;
    vector<ll> Bs;
    As.resize(N);
    Bs.resize(N);
    REP(n, N) cin >> As[n];
    REP(n, N) cin >> Bs[n];

    cout << solve_fast(N, As, Bs) << endl;

    // while(1) {
    //     // N = rand() % 100 + 3;
    //     N = 3;
    //     vector<ll> As(N);
    //     vector<ll> Bs(N);
    //     REP(n, N) As[n] = (rand() % 10) + 1;
    //     Bs = As;

    //     vector<vector<ll>> hist;
    //     hist.pb(Bs);
     
    //     int rep = rand() % 40 + 1;
    //     REP(r, rep) {
    //         while(true) {
    //             int n = rand() % N;
    //             auto nxt = Bs[n] + get_prev(n, Bs) + get_next(n, Bs);
    //             if (nxt >= 1e9) continue;
    //             Bs[n] = nxt;
    //             break;
    //         }
    //         hist.pb(Bs);
    //     }

    //     if(rep != solve_fast(N, As, Bs)) {
    //         cout << "rep = " << rep << endl;
    //         cout << "N = " << N << endl;
    //         REP(n, N) cout << As[n] << " ";
    //         cout << endl;
    //         REP(n, N) cout << Bs[n] << " ";
    //         cout << endl;
    //         cout << "rep = " << rep << endl;
    //         cout << "mine = " << solve_fast(N, As, Bs) << endl;
    //         return 0;
    //     }
    // }
    

    return 0;
}
