#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
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
    int N, K;
    cin >> N >> K;
    map<int, int> A;
    REP(n, N) {
        int tmp;
        cin >> tmp;
        ++A[tmp];
    }
    vector<int> histo;
    for(auto kv: A) {
        histo.pb(kv.second);
    }
    sort(ALL(histo));

    auto size = SIZE(histo);
    int i = 0;
    int ans = 0;
    while(size > K) {
        ans += histo[i];
        ++i;
        --size;
    }
    cout << ans << endl;
    return 0;
}
