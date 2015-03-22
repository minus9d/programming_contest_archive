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
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair


int main(void)
{
    int N;
    cin >> N;

    // 一方のみ固定
    int a = 1;
    int best_b = -1;
    int best_dist = -1;
    FOR(b, 2, N+1) {
        cout << "? " << a << " " << b << endl;
        int dist;
        cin >> dist;
        if (dist > best_dist) {
            best_b = b;
            best_dist = dist;
        }
    }

    // もう一方のみ固定
    int best_a = 1;
    FOR(a, 1, N+1){
        if (a == best_b) continue;
        cout << "? " << a << " " << best_b << endl;
        int dist;
        cin >> dist;
        if (dist > best_dist) {
            best_a = a;
            best_dist = dist;
        }
    }

    cout << "! " << best_dist << endl;

    return 0;
}
