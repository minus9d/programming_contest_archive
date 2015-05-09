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
    int N;
    cin >> N;

    vector<ll> H(N);
    vector<ll> S(N);
    REP(n,N){
        cin >> H[n] >> S[n];
    }

    ll lo = *min_element(ALL(H));
    ll hi = (ll)1e15;

    while(lo<hi) {
        ll mid = (lo+hi)/2;
        
        vector<ll> time;
        REP(i,N){
            time.pb( (mid - H[i]) / S[i] );
        }
        sort(ALL(time));
        bool ok = true;
        REP(i,N){
            if (time[i] < i) {
                ok = false;
                break;
            }
        }

        if (ok) {
            hi = mid;
        }
        else {
            lo = mid + 1;
        }
    }
    
    cout << lo << endl;

    return 0;
}

