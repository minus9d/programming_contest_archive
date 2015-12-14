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
#define mt make_tuple

int main(void)
{
    cin.sync_with_stdio(false);
    int N,M;
    cin >> N >> M;
    vector<int> As(N);
    vector<int> Bs(N);
    vector<int> Cs(M);
    vector<int> Ds(M);

    REP(n,N) cin >> As[n] >> Bs[n];
    REP(m,M) cin >> Cs[m] >> Ds[m];

    int m = 0;
    int ret = 0;
    sort(ALL(Ds));
    sort(ALL(As));
    for(auto m_money: As) {
        if (m >= M) break;
        if (Ds[m] <= m_money) {
            ++ret;
            ++m;
        }
    }

    cout << ret << endl;

    return 0;
}
