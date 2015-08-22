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
#include <complex>
#include <cstdlib>
#include <cstring>

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

int count(vector<int>& a) {
    auto N = SIZE(a);
    int cnt = 0;
    REP(i, N-1) {
        auto v1 = a[i];
        FOR(j, i+1, N) {
            cnt += v1 > a[j];
        }
    }
    return cnt;
}

int main()
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    vector<int> As(N);
    vector<int> Bs(N);

    REP(n,N) cin >> As[n];
    REP(n,N) cin >> Bs[n];
    
    map<int,int> table;
    map<int,int> table_rev;
    REP(n,N) {
        table[ As[n] ] = n;
        table_rev[ n ] = As[n];
    }

    vector<int> conv(N);
    REP(n,N) {
        conv[n] = table[ Bs[n] ];
    }

    auto c = count(conv);
    vector<int> ans;
    if (c % 2) {
        cout << -1 << endl;
        return 0;
    }
    else {
        // cout << "c = " << c << endl;
        c /= 2;

        int mx = N - 1;
        int full = 0;
        int remain = 0;
        while(c > 0) {
            if (c > mx) {
                ++full;
                c -= mx;
                --mx;
            }
            else {
                remain = c;
                c = 0;
            }
        }
        // cout << "full =" << full << endl;
        // cout << "remain =" << remain << endl;
        int init = full + 2;
        int done = 0;
        while(remain) {
            ans.pb( init );
            --remain;
            ++done;
            ++init;
        }
        // cout << "now ans size = " << SIZE(ans) << endl;

        ans.pb(full+1);
        ++done;
        while(done < N - full) {
            ans.pb(init);
            ++init;
            ++done;
        }
        // cout << "now ans size = " << SIZE(ans) << endl;
        while(full > 0) {
            ans.pb(full);
            --full;
        }
        // cout << "now ans size = " << SIZE(ans) << endl;
    }

    REP(n,N) {
        cout << table_rev[ans[n]];
        if (n == N-1)
            cout << endl;
        else
            cout << " ";
    }
    
    return 0;
}
