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
class SegmentTreeMin
{
private:
    int m_n;
    vector<T> m_dat;
public:
    const T INF = std::numeric_limits<T>::max();
    SegmentTreeMin(int n) {
        m_n = 1;
        while  (m_n < n) m_n *= 2;
        m_dat.resize(2 * m_n - 1, INF);
    };
    void update(int k, T val) {
        k += m_n - 1;
        m_dat[k] = val;
        while (k > 0) {
            k = (k - 1) / 2;
            m_dat[k] = min(m_dat[k * 2 + 1], m_dat[k * 2 + 2]);
        }
    }
    // [a, b)の範囲で最小値を返す
    T query(int a, int b) {
        return queryInternal(a, b, 0, 0, m_n);
    }
private:
    T queryInternal(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return INF;
        if (a <= l && r <= b) return m_dat[k];
        else {
            T vl = queryInternal(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = queryInternal(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> Ps(N);
    vector<ll> Hs(N);
    vector<ll> Xs(K);
    vector<ll> Ys(K);
    vector<ll> As(4);
    vector<ll> Bs(4);
    vector<ll> Cs(4);
    vector<ll> Ms(4);
    cin >> Ps[0] >> Ps[1] >> As[0] >> Bs[0] >> Cs[0] >> Ms[0];
    cin >> Hs[0] >> Hs[1] >> As[1] >> Bs[1] >> Cs[1] >> Ms[1];
    cin >> Xs[0] >> Xs[1] >> As[2] >> Bs[2] >> Cs[2] >> Ms[2];
    cin >> Ys[0] >> Ys[1] >> As[3] >> Bs[3] >> Cs[3] >> Ms[3];
    FOR(i, 2, N) {
        Ps[i] = (As[0] * Ps[i-1] + Bs[0] * Ps[i-2] + Cs[0]) % Ms[0] + 1;
        Hs[i] = (As[1] * Hs[i-1] + Bs[1] * Hs[i-2] + Cs[1]) % Ms[1] + 1;
    }
    FOR(i, 2, K) {
        Xs[i] = (As[2] * Xs[i-1] + Bs[2] * Xs[i-2] + Cs[2]) % Ms[2] + 1;
        Ys[i] = (As[3] * Ys[i-1] + Bs[3] * Ys[i-2] + Cs[3]) % Ms[3] + 1;
    }

    // cout << endl;
    // REP(n, N) cout << Ps[n] << " "; cout << endl;
    // REP(n, N) cout << Hs[n] << " "; cout << endl;
    // REP(k, K) cout << Xs[k] << " "; cout << endl;
    // REP(k, K) cout << Ys[k] << " "; cout << endl;

    // large

    // compress coords
    set<int> seen;
    for(auto p: Ps) seen.insert(p);
    for(auto x: Xs) seen.insert(x);
    auto LEN = SIZE(seen);

    map<int, int> raw_to_comp;
    map<int, int> comp_to_raw;
    int comp = 0;
    for(auto raw: seen) {
        raw_to_comp[raw] = comp;
        comp_to_raw[comp] = raw;
        ++comp;
    }

    SegmentTreeMin<ll> st_right(LEN);
    SegmentTreeMin<ll> st_left(LEN);
    REP(i, LEN) {
        st_right.update(i, ll(1e18));
        st_left.update(i, ll(1e18));
    }

    // tower
    REP(n, N) {
        auto p_raw = Ps[n];
        auto h = Hs[n];
        auto p_comp = raw_to_comp[p_raw];
        st_right.update(p_comp, -(h - p_raw));
        st_left.update(p_comp, -(h - (ll(1e9) - p_raw)));
    }

    //cout << "st_right::";
    //REP(i, LEN) cout << st_right.query(i, i + 1) << " "; cout << endl;

    int ans = 0;
    REP(k, K) {
        auto x_raw = Xs[k];
        auto y = Ys[k];
        auto x_comp = raw_to_comp[x_raw];
        bool ok = false;

        auto right_balloon = y - x_raw;
        auto tallest_right_poll = -st_right.query(x_comp, LEN);
        if (tallest_right_poll >= right_balloon) ok = true;

        auto left_balloon = y - (ll(1e9) - x_raw);
        auto tallest_left_poll = -st_left.query(0, x_comp + 1);
        if (tallest_left_poll >= left_balloon) ok = true;

        ans += ok;
    }
    cout << ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
