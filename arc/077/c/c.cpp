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
#include <stack>
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

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> As(N);
    deque<int> Bs;
    REP(n,N) cin >> As[n];
    bool flag = false;
    for(auto a: As) {
        if (flag) {
            Bs.push_front(a);
        }
        else {
            Bs.push_back(a);
        }
        flag = !flag;
    }

    if (flag) reverse(ALL(Bs));
    REP(i, N) {
        if (i != 0) cout << " " << Bs[i];
        else cout << Bs[i];
    }
    cout << endl;

    return 0;
}
