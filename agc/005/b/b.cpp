// 最小値の場所を探し、
// 「最小値を含む部分列」「最小値より前の部分列」「最小値より後ろの部分列」で分割統治して解いた
// 最小値の場所をすぐに出せるようにSegment Treeをあらかじめ構築しておかないとTLE
// より単純な解法をb.refine.cppに書いた

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
#include <climits>

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

class SegmentTree
{
private:
    int m_n;
    // min, idx
    vector<pair<int,int>> m_dat;
    
public:
    void init(int n) {
        m_n = 1;
        while  (m_n < n) m_n *= 2;

        m_dat.resize(2 * m_n - 1, mp(INT_MAX,-1));
    }

    void update(int k, int a) {
        int orig_k = k;
        k += m_n - 1;
        m_dat[k] = mp(a,orig_k);

        while (k > 0) {
            k = (k - 1) / 2;

            auto v1 = m_dat[k * 2 + 1].first;
            auto v2 = m_dat[k * 2 + 2].first;
            if (v1 < v2) {
                m_dat[k] = mp(v1, m_dat[k * 2 + 1].second);
            }
            else {
                m_dat[k] = mp(v2, m_dat[k * 2 + 2].second);
            }
        }

        // cout << "m_dat:" << endl;
        // for(auto d: m_dat) cout << "(" << d.first << "," << d.second << "),";
        // cout << endl;
    }

    // [a, b)の範囲で最小値を返す
    pair<int,int> query(int a, int b) {
        return queryInternal(a, b, 0, 0, m_n);
    }

private:
    pair<int,int> queryInternal(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return mp(INT_MAX,-1);
        if (a <= l && r <= b) return m_dat[k]; // ?
        else {
            auto vl = queryInternal(a, b, k * 2 + 1, l, (l + r) / 2);
            auto vr = queryInternal(a, b, k * 2 + 2, (l + r) / 2, r);
            return (vl.first < vr.first) ? vl : vr;
        }
    }
};

vector<ll> As;
SegmentTree stree;

ll calc_comb(ll num) {
    return num * (num + 1) / 2;
}

ll func(int b, int e) {
    if (e - b == 1) return As[b];
    else if (e - b == 0) return 0;

    // auto mn_it = min_element(As.begin() + b, As.begin() + e);
    // auto mn_idx = distance(As.begin(), mn_it);
    // auto mn = *mn_it;
    
    auto res = stree.query(b, e);
    auto mn = res.first;
    auto mn_idx = res.second;

    // cout << "b, e, mn, mn_idx = :" << b << "," << e << "," << mn << "," << mn_idx << endl;

    ll num = e - b;
    ll comb = calc_comb(num);
    ll comb1 = calc_comb(mn_idx - b);
    ll comb2 = calc_comb(e - mn_idx - 1);
    ll comb3 = comb - comb1 - comb2;
    

    ll ans = comb3 * mn + func(b, mn_idx) + func(mn_idx + 1, e);
    // cout << "b, e = " << b << "," << e << ". ans = " << ans << "."
    //      << "comb(1,2,3) = " << comb1 << "," << comb2 << "," << comb3 << endl;
    
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    As.resize(N);
    REP(n,N) cin >> As[n];

    stree.init(N);
    REP(n,N) stree.update(n,As[n]);

    ll ans = func(0, N);
    cout << ans << endl;

    return 0;
}
