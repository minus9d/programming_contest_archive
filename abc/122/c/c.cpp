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
    void printSum() {
        for(auto e: m_cum) cout << e << " "; cout << endl;
    }

private:
    size_t m_N;
    vector<T> m_cum;
};

int main(void)
{
    cin.sync_with_stdio(false);
    int N, Q;
    string S;
    cin >> N >> Q;
    cin >> S;

    vector<int> acs(N);
    REP(n, N - 1) {
        if (S[n] == 'A' && S[n + 1] == 'C') {
            acs[n]++;
        }
    }
    CumSum1D<int> ac_sums;
    ac_sums.init(acs);
    // for(auto e: acs) cout << e << " "; cout << endl;
    // ac_sums.printSum();
        
    REP(q, Q) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        int ans = ac_sums.getSum(l, r - 1);
        cout << ans << endl;
    }
    return 0;
}
