// pとqのうちもっとも数値の大きいp_or_qを一つ選ぶ
// →p_or_qは一つのみ使う。p_or_qで領域を分割してそれぞれの小問題を解く
// という方針で解いたが、TLE & WA

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

class SegmentTreeSum
{
private:
    int m_n;
    vector<int> m_dat;

public:
    void init(int n) {
        m_n = 1;
        while (m_n < n) m_n *= 2;

        m_dat.resize(2 * m_n - 1, 0);
    }

    // k番目に値aを加算
    void update(int k, int a) {
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
    int query(int a, int b) {
        return queryInternal(a, b, 0, 0, m_n);
    }

private:
    int queryInternal(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            return 0;
        }
        if (a <= l && r <= b) return m_dat[k];
        else {
            int vl = queryInternal(a, b, k * 2 + 1, l, (l + r) / 2);
            int vr = queryInternal(a, b, k * 2 + 2, (l + r) / 2, r);
            return vl + vr;
        }
    }
};

// (最小値, 最小値をとるインデックス)のペアを返す
// 複数の値が同時に最小値を取る場合はどちらのインデックスが返るか保証がないので注意
class SegmentTreeWithIndex
{
private:
    int m_n;
    //(min, idx)のペア
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

int W, H;
vector<int> Ps;
vector<int> Qs;
SegmentTreeWithIndex pseg;
SegmentTreeWithIndex qseg;
SegmentTreeSum psegsum;
SegmentTreeSum qsegsum;

int offset = 100000009;

ll mysum(vector<int>& PorQ, int mn, int mx) {
    ll ans = 0;
    FOR(i, mn, mx) {
        ans += PorQ[i];
    }
    return ans;
}

ll func(int p_min, int p_max, int q_min, int q_max) {
    if (p_min == p_max && q_min == q_max) {
        return 0;
    }
    if (p_min == p_max) {
        return qsegsum.query(q_min, q_max);
    }
    if (q_min == q_max) {
        return psegsum.query(p_min, p_max);
    }

    auto max_p_data = pseg.query(p_min, p_max);
    auto max_q_data = qseg.query(q_min, q_max);
    auto max_p_idx = max_p_data.second;
    auto max_q_idx = max_q_data.second;

    auto max_p = Ps[max_p_idx];
    auto max_q = Qs[max_q_idx];

    if (max_p < max_q) {
        auto ans1 = func(p_min, p_max, q_min, max_q_idx);
        auto ans2 = func(p_min, p_max, max_q_idx + 1, q_max);
        return ans1 + ans2 + max_q;
    }
    else {
        auto ans1 = func(p_min, max_p_idx, q_min, q_max);
        auto ans2 = func(max_p_idx + 1, p_max, q_min, q_max);
        return ans1 + ans2 + max_p;
    }
}

int main(void) {
    cin >> W >> H;
    Ps.resize(W);
    Qs.resize(H);
    REP(w,W) cin >> Ps[w];
    REP(h,H) cin >> Qs[h];

    pseg.init(W);
    qseg.init(H);
    psegsum.init(W);
    qsegsum.init(H);
    REP(w,W) {
        pseg.update(w, offset - Ps[w]);
        psegsum.update(w, Ps[w]);
    }
    REP(h,H) {
        qseg.update(h, offset - Qs[h]);
        qsegsum.update(h, Qs[h]);
    }

    cout << func(0, W, 0, H) << endl;

    return 0;
}
