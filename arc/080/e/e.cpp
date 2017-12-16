#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

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

vector<int> Ps;
SegmentTreeWithIndex st_odd;
SegmentTreeWithIndex st_even;
priority_queue<tuple<int, int, int, int, int, int>> que;

tuple<int,int> find_min_pair(int a, int b) {
    int mn_val = -1;
    int mn_idx = -1;
    int mn2_val = -1;
    int mn2_idx = -1;

    if (a % 2 == 0) {
        tie(mn_val, mn_idx) = st_even.query(a, b);
        tie(mn2_val, mn2_idx) = st_odd.query(mn_idx + 1, b);
    }
    else {
        tie(mn_val, mn_idx) = st_odd.query(a, b);
        tie(mn2_val, mn2_idx) = st_even.query(mn_idx + 1, b);
    }
    //printf("%d %d %d %d\n", mn_val, mn_idx, mn2_val, mn2_idx);
	return mt(mn_idx, mn2_idx);
}

void push_que(int s, int t) {
	auto ret = find_min_pair(s, t);
	que.push(mt(-Ps[get<0>(ret)], -Ps[get<1>(ret)], s, t, get<0>(ret), get<1>(ret)));
}


int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

	Ps.resize(N);
	REP(n, N) {
		cin >> Ps[n];
	}

	st_odd.init(N);
    st_even.init(N);
    const int INF = 1e9;
    REP(n, N) {
        if (n % 2 == 0) {
            st_even.update(n, Ps[n]);
            st_odd.update(n, INF);
        }
        else {
            st_odd.update(n, Ps[n]);
            st_even.update(n, INF);
        }
    }

	push_que(0, N);

	vector<int> ans;
	while (!que.empty()) {
		auto ele = que.top(); que.pop();
		ans.pb(-get<0>(ele));
		ans.pb(-get<1>(ele));
		auto s = get<2>(ele);
		auto t = get<3>(ele);
		auto idx1 = get<4>(ele);
		auto idx2 = get<5>(ele);
		if (s != idx1) {
			push_que(s, idx1);
		}
		if (idx1 + 1 != idx2) {
			push_que(idx1 + 1, idx2);
		}
		if (idx2 + 1 != t) {
			push_que(idx2 + 1, t);
		}
	}
	REP(i, N) {
		if (i != 0) {
			cout << " ";
		}
		cout << ans[i];
	}
	cout << endl;

    return 0;
}
