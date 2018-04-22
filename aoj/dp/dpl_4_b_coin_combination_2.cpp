// ���: N���̃R�C������K����I��ŋ��z��[L,R]�͈̔͂ɂȂ�I�ѕ��̐������߂�
// ��@: 

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

map<ll, ll> make_map(vector<ll>& As) {
    map<ll, ll> ret;
    for(auto a: As) ++ret[a];
    return ret;
}

map<ll, ll> make_combination(map<ll, ll>& As, map<ll, ll>& Bs) {
    map<ll, ll> ret;
    for(auto a: As) {
        for(auto b: Bs) {
            auto val = a.first + b.first;
            auto cnt = a.second * b.second;
            ret[val] += cnt;
        }
    }
    return ret;
}

ll coin_combination_2(ll N, ll K, ll L, ll R,
                      vector<ll>& As) {
    // �O�����̑S��
    const auto N2 = N / 2;
    vector<vector<ll>> former(N2 + 1);
    REP(i, (1 << N2)) {
        ll sum = 0;
        int cnt = 0;
        REP(j, N2) {
            if (i & (1 << j)) {
                sum += As[j];
                cnt++;
            }
        }
        former[cnt].pb(sum);
    }

    // �㔼���̑S��
    vector<vector<ll>> latter(N - N2 + 1);
    REP(i, (1 << (N - N2))) {
        ll sum = 0;
        int cnt = 0;
        REP(j, (N - N2)) {
            if (i & (1 << j)) {
                sum += As[N2 + j];
                cnt++;
            }
        }
        latter[cnt].pb(sum);
    }

    REP(n, N2 + 1) sort(ALL(former[n]));
    REP(n, N - N2 + 1) sort(ALL(latter[n]));

    ll ans = 0;
    // �O������n�g���ꍇ
    REP(n, N2 + 1) {
        if (n + N - N2 < K) continue;
        if (n > K) break;

        ll tmp = 0;
        for (auto e: former[n]) {
            if (e > R) break;
            auto mn = max(0LL, L - e);
            auto mx = R - e;

            auto it1 = lower_bound(ALL(latter[K - n]), mn);
            auto it2 = lower_bound(ALL(latter[K - n]), mx + 1);
            ans += (it2 - it1);
            tmp += (it2 - it1);
        }
        // cout << "former " << n << ", latter " << (K - n) << ", " << tmp << "added" << endl;
    }
    return ans;
}

int main() {
    ll N, K, L, R;
    cin >> N >> K >> L >> R;
    vector<ll> As(N);
    REP(n, N) cin >> As[n];
    cout << coin_combination_2(N, K, L, R, As) << endl;

    return 0;
}
