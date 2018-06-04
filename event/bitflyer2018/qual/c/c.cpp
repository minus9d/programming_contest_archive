// 本番中に解けた
//
// d(Xi, Xj) <= D かつ d(Xj, Xk) <= Dの数から、
// d(Xi, Xk) <= Dの数を引く

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

ll solve(ll N, ll D, vector<ll>& Xs) {
    vector<ll> withinD(N);
    REP(i, N) {
        auto it = upper_bound(ALL(Xs), Xs[i] + D);
        auto d = distance(Xs.begin() + i, it) - 1;
        withinD[i] = d;
        //cout << d << endl;
    }

    // d(i,j) <= D かつ d(j,k) <= Dを満たす(i,j,k)の組の数をans1とする
    queue<ll> q; // iから距離がD以下であるようなjの候補をqに入れる
    ll sum = 0; // 今 qに入っているjそれぞれについて、とりうるkの値の和をとったもの
    ll ans1 = 0;
    int j = 1;
    REP(i, N-2) {
        if (i != 0) {
            if (!q.empty()) {
                sum -= q.front();
                q.pop();
            }
        }

        j = max(j, i + 1);

        while(j < N - 1) {
            if (Xs[j] - Xs[i] <= D) {
                q.push(withinD[j]);
                sum += withinD[j];
                ++j;
            }
            else {
                break;
            }
        }
        ans1 += sum;
    }

    // d(i,k) <= D を満たす(i,j,k)の組の数をans2とする
    ll ans2 = 0;
    REP(i, N-2) {
        auto t = withinD[i];
        // e.g. t = 3のとき
        //      i o o o  の o からj, kを選ぶので、選び方は 3C2
        if (t >= 2) {
            ans2 += t * (t - 1) / 2;
        }
    }
    //cout << "ans1 = " << ans1 << ", ans2 = " << ans2 << endl;
    return ans1 - ans2;
}

int slow(ll N, ll D, vector<ll>& Xs) {
    int ans = 0;
    REP(i, N - 2) {
        FOR(j, i + 1, N - 1) {
            if (Xs[j] - Xs[i] > D) break;
            FOR(k, j + 1, N) {
                if (Xs[k] - Xs[j] <= D
                    && Xs[k] - Xs[i] > D) ++ans;
            }
        }
    }
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, D;
    cin >> N >> D;
    vector<ll> Xs(N);
    REP(n, N) cin >> Xs[n];
    cout << solve(N, D, Xs);
    return 0;

    // for debug
    {
        int N = 3;
        while(true) {
            REP(rep, 5) {
                int D = rand() % 10;
                vector<ll> Xs(N);
                int pos = 0;
                REP(n, N) {
                    Xs[n] = pos;
                    pos += (rand() % 10) + 1;
                }
                ll s = solve(N, D, Xs);
                ll gt = slow(N, D, Xs);
                if (s != gt) {
                    cout << N << " " << D << endl;
                    for(auto x: Xs) cout << x << " ";
                    cout << endl;
                    cout << "myans " << s << ", expected " << gt << endl;
                    exit(0);
                }
            }
            ++N;
        }
    }

    return 0;
}
