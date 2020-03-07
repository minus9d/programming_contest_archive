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

// 区間加算に対応しないBIT
// 1 originなので注意!!
class BitSimple
{
private:
    int m_n;
    vector<int> m_bit;
    
public:
    void init(int n) {
        m_n = n;
        m_bit.resize(n + 1);
    }

    // 要素1から要素iまでの和
    int sum(int i) {
        int s = 0;
        while (i > 0) {
            s += m_bit[i];
            i -= i & -i;
        }
        return s;
    }
    
    void add(int i, int x) {
        while (i <= m_n) {
            m_bit[i] += x;
            i += i & -i;
        }
    }
};

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    string S;
    cin >> N;
    cin >> S;

    vector<BitSimple> bits(26);
    for(auto& bit: bits) {
        bit.init(N + 10);
    }

    REP(i, N) {
        auto idx = S[i] - 'a';
        bits[idx].add(i + 1, 1);
    }

    int Q;
    cin >> Q;
    REP(q, Q) {
        int type;
        cin >> type;
        if (type == 1) {
            int i;
            char ch_after;
            cin >> i >> ch_after;
            char ch_before = S[i - 1];

            bits[ch_after - 'a'].add(i, 1);
            bits[ch_before - 'a'].add(i, -1);
            S[i - 1] = ch_after;  // 忘れていた
        }
        else {
            int l, r;
            cin >> l >> r;
            ll sum = 0;
            REP(ch_idx, 26) {
                auto tmp = bits[ch_idx].sum(r) - bits[ch_idx].sum(l - 1);
                sum += (tmp > 0);
            }
            cout << sum << endl;
        }
    }


    return 0;
}
