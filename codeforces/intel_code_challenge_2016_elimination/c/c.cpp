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
#include <iomanip>
#include <map>

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

class SegmentTreeSum
{
private:
    ll m_n;
    vector<ll> m_dat;
    
public:
    void init(ll n) {
        m_n = 1;
        while (m_n < n) m_n *= 2;

        m_dat.resize(2 * m_n - 1, 0);
    }

    // k番目に値aを加算
    void update(ll k, ll a) {
        k += m_n - 1;
        m_dat[k] += a;

        while (k > 0) {
            k = (k - 1) / 2;
            m_dat[k] = m_dat[k * 2 + 1] + m_dat[k * 2 + 2];
        }

        // cout << "m_n: " << m_n << endl;
        // cout << "m_data:";
        // REP(i, 2 * m_n - 1) cout << m_dat[i] << ",";
        // cout << endl;
    }

    // [a, b)の範囲で合計を返す
    ll query(ll a, ll b) {
        return queryInternal(a, b, 0, 0, m_n);
    }

private:
    ll queryInternal(ll a, ll b, ll k, ll l, ll r) {
        if (r <= a || b <= l) {
            return 0;
        }
        if (a <= l && r <= b) return m_dat[k];
        else {
            ll vl = queryInternal(a, b, k * 2 + 1, l, (l + r) / 2);
            ll vr = queryInternal(a, b, k * 2 + 2, (l + r) / 2, r);
            return vl + vr;
        }
    }
};


SegmentTreeSum stree;
int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    stree.init(N);
    REP(n,N) {
        ll num;
        cin >> num;
        stree.update(n, num);
    }
    

    // (begin, (end, sum))
    map<int, pair<int,ll>> segs;
    segs[0] = mp(N, stree.query(0,N));
    
    map<ll, int> seg_values;  // なぜかmultisetがない..
    seg_values[segs[0].second] += 1;

    REP(n, N) {
        int idx;
        cin >> idx;
        --idx;

        auto it = segs.upper_bound(idx);
        --it; // ???

        auto b = it->first;
        auto e = it->second.first;
        auto seg = it->second.second;

        --seg_values[seg];
        if (seg_values[seg] == 0) {
            seg_values.erase(seg);
        }

        if (b != idx) {
            auto new_v = stree.query(b, idx);
            segs[b] = mp(idx, new_v);
            ++seg_values[new_v];
        }
        if (e - idx > 1) {
            auto new_v = stree.query(idx + 1, e);
            segs[idx + 1] = mp(e, new_v);
            ++seg_values[new_v];
        }

        if (SIZE(seg_values))
            cout << seg_values.rbegin()->first << endl;
        else
            cout << 0 << endl;
    }

    return 0;
}
