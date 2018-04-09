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

void print_vec(vector<int>& V) {
    for (auto v: V) cout << v << " ";
    cout << endl;
}


int faster(vector<int>& V) {
    auto N = SIZE(V);
    vector<int> V1;
    vector<int> V2;
    REP(n, N) {
        if (n % 2) V2.pb(V[n]);
        else V1.pb(V[n]);
    }
    sort(ALL(V1));
    sort(ALL(V2));

    vector<int> sortedV;
    REP(n, N) {
        if (n % 2) sortedV.pb(V2[n / 2]);
        else sortedV.pb(V1[n / 2]);
    }

    REP(n, N-1) {
        if (sortedV[n] > sortedV[n+1]) {
            return n;
        }
    }
    return -1;
}

int brute_force(vector<int>& V) {
    auto N = SIZE(V);
    while (1) {
        bool swapped = false;
        REP(n, N-2) {
            if (V[n] > V[n+2]) {
                swap(V[n], V[n+2]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    REP(n, N-1) {
        if (V[n] > V[n+1]) {
            return n;
        }
    }
    return -1;
}

void solve() {
    int N;
    cin >> N;
    vector<int> V(N);
    REP(n, N) cin >> V[n];

    auto ret = faster(V);
    if (ret == -1) cout << "OK";
    else cout << ret;
}


int main(void)
{
    cin.sync_with_stdio(false);

    // // for debug
    // while (1) {
    //     int N = 20 + rand() % 2;
    //     vector<int> V(N);
    //     REP(n, N) V[n] = n;
    //     random_shuffle(ALL(V));
    //     assert(brute_force(V) == faster(V));
    //     cout << "ok ";
    // }

    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
