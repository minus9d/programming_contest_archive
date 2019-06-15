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
    ll N;
    cin >> N;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];

    sort(ALL(As));
    CumSum1D<ll> from_min;
    from_min.init(As);

    reverse(ALL(As));
    CumSum1D<ll> from_max;
    from_max.init(As);
    
    ll best_ans = -1e10;
    ll best_i = -1;
    FOR(i, 1, N) { // plusになる個数
        ll ans1 = from_max.getSum(0, i - 1);
        ll ans2 = from_min.getSum(0, N - i - 1);
        ll ans = ans1 - ans2;
        if (ans > best_ans) {
            best_ans = ans;
            best_i = i;
        }
    }

    cout << best_ans << endl;
    vector<ll> plus;
    vector<ll> minus;
    REP(i, best_i) {
        plus.pb(As[i]);
    }
    reverse(ALL(As));
    REP(i, N - best_i) {
        minus.pb(As[i]);
    }
    
    ll cur = minus[0];
    auto plus_num = SIZE(plus);
    auto minus_num = SIZE(minus);
    REP(i, plus_num - 1) {
        cout << cur << " " << plus[i] << endl;
        cur = cur - plus[i];
    }
    cout << plus.back() << " " << cur << endl;
    cur = plus.back() - cur;

    FOR(i, 1, minus_num) {
        cout << cur << " " << minus[i] << endl;
        cur -= minus[i];
    }

    assert(cur == best_ans);

    return 0;
}
