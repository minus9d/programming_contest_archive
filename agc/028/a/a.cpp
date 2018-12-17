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

ll getGcdSimple(ll a, ll b)
{
    if (b == 0) return a;
    return getGcdSimple(b, a % b);
}

// 2数の最小公倍数
ll getLcmSimple(ll a, ll b)
{
    return a / getGcdSimple(a, b) * b;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, M;
    cin >> N >> M;
    string S, T;
    cin >> S;
    cin >> T;

    auto ans = getLcmSimple(N, M);
    auto n_step = ans / N;
    auto m_step = ans / M;

    ll i = 0;
    ll j = 0;
    bool ok = true;
    while (i < ans && j < ans) {
        if (i == j) {
            // cout << "i: " << i << endl;
            if (S[i/n_step] != T[j/m_step]) {
                ok = false;
                break;
            }
            i += n_step;
            j += m_step;
        }
        else if (i < j) i += n_step;
        else if (j < i) j += m_step;
    }
    if (ok) cout << ans << endl;
    else cout << -1 << endl;

    return 0;
}
