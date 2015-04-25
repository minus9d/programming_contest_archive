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

typedef pair<int,int> P;



ll dist2(P& a, P& b) {
    ll d1 = a.first - b.first;
    ll d2 = a.second - b.second;
    
    return (ll)d1 * d1 + d2 * d2;
}

double longest_dist(vector<P>& dots)
{
    auto size = SIZE(dots);
    ll mx = 0LL;
    REP(i, size) {
        REP(j, size) {
            ll tmp = dist2(dots[i], dots[j]);
            mx = max(mx, tmp);
        }
    }
    return sqrt(mx);
}

double pow2(double a)
{
	return a*a;
}

vector<P> candidate(vector<P>& dots)
{
    vector<int> xs;
    vector<int> ys;
    for(auto& dot : dots) {
        auto x = dot.first;
        auto y = dot.second;
        xs.pb(x);
        ys.pb(y);
    }

    auto x_mn = *min_element(ALL(xs));
    auto x_mx = *max_element(ALL(xs));
    auto y_mn = *min_element(ALL(ys));
    auto y_mx = *max_element(ALL(ys));

    // 長方形の中心
    auto x_center = (double)(x_mn + x_mx) / 2.0;
    auto y_center = (double)(y_mn + y_mx) / 2.0;

    // 長方形の中心からの距離が長い順にソート
    vector<pair<ll,P>> distances;
	for (auto& p : dots) {
		ll d = pow2(p.first - x_center) + pow2(p.second - y_center);
		distances.pb( mp(d, p) );
     }
    sort(ALL(distances));
	reverse(ALL(distances));

	// 長方形の中心からの距離が長いものをいくつか返す
	// いくつ返せばよいか不明、とりあえず多めに2500返す
    vector<P> ret;
    REP(i, min(2500, SIZE(dots))) {
        ret.pb( distances[i].second );
    }

    return ret;
}


int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    vector<P> A(N);
    vector<P> B(N);
    REP(n, N) {
        cin >> A[n].first >> A[n].second;
    }
    REP(n, N) {
        cin >> B[n].first >> B[n].second;
    }

    A = candidate(A);
    B = candidate(B);

    auto l1 = longest_dist(A);
    auto l2 = longest_dist(B);
    auto ratio = l2 / l1;

    printf("%.9lf\n", ratio);

    return 0;
}
