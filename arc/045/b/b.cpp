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

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;

    vector<int> table(N+1);
    vector<int> S(M);
    vector<int> T(M);
    REP(m,M) {
        int s, t;
        cin >> s >> t;
        --s;
        --t;
        ++table[s];
        --table[t+1];
        S[m] = s;
        T[m] = t;

    }

    // REP(i,N) {
    //     cout << table[i] << ",";
    // }
    // cout << endl;

    FOR(i,1,N) {
        table[i] += table[i-1];
    }

    SegmentTree st;
    st.init(N);
    REP(i,N) {
        st.update(i, table[i]);
    }

    // REP(i,N) {
    //     cout << table[i] << ",";
    // }
    // cout << endl;

    vector<int> ok;
    REP(m,M) {
        auto mn = st.query(S[m], T[m]+1);
        if (mn > 1) {
            ok.pb(m+1);
        }
    }
    cout << SIZE(ok) << endl;
    for(auto e : ok) cout << e << endl;

    return 0;
}
