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

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    const ll INF = 1e15;
    vector<vector<ll>> As(N, vector<ll>(N));
    REP(n1, N) {
        REP(n2, N) {
            cin >> As[n1][n2];
        }
    }

    vector<vector<ll>> Ds(N, vector<ll>(N, INF));
    REP(n, N) Ds[n][n] = 0;

    // 長さの小さい辺から張っていく

    // <dist, v1, v2>
    set<tuple<ll, int, int>> edges;
    REP(i, N-1) {
        FOR(j, i+1, N) {
            edges.insert(mt(As[i][j], i, j));
        }
    }

    ll ans = 0;
    bool ok = true;

    // 辿れる頂点を管理
    for(auto& e: edges) {
        auto d = get<0>(e);
        auto v1 = get<1>(e);
        auto v2 = get<2>(e);

        auto cur_dist = Ds[v1][v2];
        // 矛盾発生
        if (cur_dist < d) {
            ok = false;
            break;
        }
        else if (cur_dist > d) {
            Ds[v1][v2] = Ds[v2][v1] = d;
			// 関係するとこだけ更新
			REP(i, N-1) {
				FOR(j, i + 1, N) {
					auto d1 = Ds[i][j];
					auto d2 = Ds[i][v1] + d + Ds[v2][j];
					auto d3 = Ds[i][v2] + d + Ds[v1][j];
					Ds[i][j] = Ds[j][i] = min(min(d1, d2), d3);
				}
			}


            ans += d;
        }
        else if (cur_dist == d) {
            // do nothing
        }
    }

    if (ok) {
        cout << ans << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
