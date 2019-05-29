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

// 1次元累積和
template <typename T>
class CumSum1D
{
public:
    CumSum1D(){};
    ~CumSum1D(){};
    void init(vector<T>& arr) {
        m_cum = arr;
        m_N = arr.size();
        FOR(i, 1, m_N) m_cum[i] += m_cum[i - 1];
    }
    // get sum of [l, r]. 0-based.
    T getSum(int l, int r) {
        T ret = m_cum[r];
        if (l != 0) ret -= m_cum[l - 1];
        return ret;
    }
private:
    size_t m_N;
    vector<T> m_cum;
};

int main(void)
{
    cin.sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    vector<ll> Vs(N);
    REP(n, N) cin >> Vs[n];

    CumSum1D<ll> cum;
    cum.init(Vs);

    ll ans = 0;
    ll sum_of_all = cum.getSum(0, N - 1);

    if (K >= N) {
        ans = max(ans, sum_of_all);
    }
    
    REP(p1, N) {
        FOR(p2, p1, N) {
            int remained = p2 - p1 + 1;
            int taken = N - remained;
            if (taken > K) continue;

            ll score = sum_of_all - cum.getSum(p1, p2);

            //cout << "p1, p2 = " << p1 << "," << p2 << endl;
            //cout << "temp score = " << score << endl;

            vector<ll> gems;
            REP(p, p1) gems.pb(Vs[p]);
            FOR(p, p2 + 1, N) gems.pb(Vs[p]);
            //cout << "gems = "; for(auto e: gems) cout << e << " "; cout << endl;

            sort(ALL(gems));
            int i = 0;
            while(taken < K && i < SIZE(gems)) {
                if (gems[i] < 0) {
					score -= gems[i];
					++i;
                    ++taken;
                } else {
                    break;
                }
            }
            //cout << "final score = " << score << endl;

            ans = max(ans, score);
        }
    }
    cout << ans << endl;

    return 0;
}
