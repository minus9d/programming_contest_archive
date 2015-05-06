#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <climits>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

class SegmentTreeMin
{
private:
    int m_n;
    vector<int> m_dat;
    
public:
    void init(int n) {
        m_n = 1;
        while  (m_n < n) m_n *= 2;

        m_dat.resize(2 * m_n - 1, INT_MAX);
    }

    void update(int k, int a) {
        k += m_n - 1;
        m_dat[k] = a;

        while (k > 0) {
            k = (k - 1) / 2;
            m_dat[k] = min(m_dat[k * 2 + 1], m_dat[k * 2 + 2]);
        }
    }

    // [a, b)の範囲で最小値を返す
    int query(int a, int b) {
        return queryInternal(a, b, 0, 0, m_n);
    }

private:
    int queryInternal(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return INT_MAX;
        if (a <= l && r <= b) return m_dat[k];
        else {
            int vl = queryInternal(a, b, k * 2 + 1, l, (l + r) / 2);
            int vr = queryInternal(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};

int main(){
    int N, Q;
    cin >> N >> Q;
    
    SegmentTreeMin st;
    st.init(N);
    
    REP(q, Q) {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 0) {
            st.update(x, y);
        }
        else {
            auto res = st.query(x, y+1);
            cout << res << endl;
        }
    }

    return 0;
}
