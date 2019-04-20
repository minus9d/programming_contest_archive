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
    size_t m_N;
    vector<T> m_cum;
};

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    string S;
    cin >> S;

    vector<int> w(N);
    vector<int> b(N);
    REP(n, N) {
        if (S[n] == '#') b[n] = 1;
        else w[n] = 1;
    }

    CumSum1D<int> W; W.init(w);
    CumSum1D<int> B; B.init(b);

    // for(auto e: W.m_cum) cout << e; cout << endl;
    // for(auto e: B.m_cum) cout << e; cout << endl;

    int ans = N * 2;
    REP(white_num, N + 1) {
        int t = 0;
        if (white_num != 0) t += (white_num - W.getSum(0, white_num - 1));
        int black_num = N - white_num;
        if (black_num != 0) t += (black_num - B.getSum(white_num, N - 1));
        // cout << "white_num, t = " << white_num << "," << t << endl;
        ans = min(ans, t);
    }
    cout << ans << endl;
    return 0;
}
