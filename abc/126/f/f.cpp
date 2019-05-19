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

// nのk乗を計算
ll pow2(ll n, ll k) {
    ll ret = 1;
    REP(i, k) ret *= n;
    return ret;
}

// 配列shffが与えられたとき問題文にある条件Kを満たしているか調べる
// 満たしているならKを返す 満たしていないなら-1を返す
int check_k(const vector<int>& shff, int num_kind) {

	vector<int> all_xor;
	REP(n, num_kind) {
		bool is_first = true;
		int xor_res = 0;
		for (auto s : shff) {
			if (s == n) {
				if (is_first) {
					is_first = false;
				}
				else {
					break;
				}
			}
			else if (!is_first) {
				xor_res ^= s;
			}
		}
		all_xor.pb(xor_res);
	}

	if (*min_element(ALL(all_xor)) ==
		*max_element(ALL(all_xor))) {
		return *min_element(ALL(all_xor));
	} else {
		return -1;
	}
}

// 性質を調べるための実験用コード
void experiment(int M) {
    vector<int> shff;
    auto num_kind = pow2(2, M);
    REP(m, num_kind) {
        shff.pb(m);
        shff.pb(m);
    }

	set<int> seen;

    do {
		auto K = check_k(shff, num_kind);
		if (seen.count(K)) continue;
		seen.insert(K);

        cout << "K = " << K << endl;
        for(auto s: shff) cout << s << " ";
        cout << endl;
    } while(next_permutation(ALL(shff)));
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll M, K;
    cin >> M >> K;

    if (M == 0) {
        if (K == 0) {
            cout << "0 0" << endl;
        } else {
            cout << -1 << endl;
        }
    }
    else if (M == 1) {
        if (K == 0) {
            cout << "0 0 1 1" << endl;
        } else {
            cout << -1 << endl;
        }
    }
    else {
        auto mx = pow2(2, M);
        if (K >= mx) {
            cout << -1 << endl;
        } else {
            vector<int> ans;
            if (K == 0) {
                REP(i, mx) {
                    ans.pb(i);
                    ans.pb(i);
                }
            } else {
                REP(k, K) ans.pb(k);
                for(int k = K; k >= 0; --k) ans.pb(k);
                FOR(k, K + 1, mx) ans.pb(k);
                ans.pb(K);
                for(int k = mx - 1; k >= K + 1; --k) ans.pb(k);
            }
            REP(k, SIZE(ans)) {
                if (k == 0) cout << ans[k];
                else cout << " " << ans[k];
            }
            cout << endl;
        }
    }
    
    return 0;
}
