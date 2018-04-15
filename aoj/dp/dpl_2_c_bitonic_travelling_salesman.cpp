// 問題: x座標が必ず異なるN点が与えられる。
//      x座標が最小の点を始点、x座標が最大の点を折り返し点としてすべての点を通り一周する経路のうち
//      最短路を求める。
// 解法: http://marcodiiga.github.io/bitonic-tour をそのまま実装。
//       完全には理解できていない
// 参照: http://nyanp.hatenablog.com/entry/20121014/p1
//      https://en.wikipedia.org/wiki/Bitonic_tour
//      https://stackoverflow.com/questions/874982/how-to-compute-optimal-paths-for-traveling-salesman-bitonic-tour
//      http://marcodiiga.github.io/bitonic-tour

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

double bitonic_tour(int N, vector<pair<ll,ll>>& points) {

    sort(ALL(points));

    auto euclideanDistance = [&](int a, int b) {
        auto& pa = points[a];
        auto& pb = points[b];
        return hypot(pa.first - pb.first, pa.second - pb.second);
    };

    // [x][y]: 点xから、左側の0まで行き、右側に方向を変え、yで終わる最短のバイトニックパス。
    // x == yのときは始点と終点が一致する
    vector<vector<double>> bitonicDistances(N, vector<double>(N, -1));

    // 最初は点0のみが存在するところから始める
    bitonicDistances[0][0] = 0;

    // 点を1点ずつ増やしていく  これらは片道なので自明
    FOR(i, 1, N)
        bitonicDistances[0][i] =
        bitonicDistances[0][i - 1] + euclideanDistance(i - 1, i);

    FOR(i, 1, N) {
        FOR(j, i, N) {
            if (i == j || i == j - 1) {
                double mn = numeric_limits<double>::max();
                REP(k, i) {
                    mn = min(mn, bitonicDistances[k][i] + euclideanDistance(k, j));
                }
                bitonicDistances[i][j] = mn;
            }
            // 終点が右に伸びていくだけなので自明
            else {
                bitonicDistances[i][j] =
                    bitonicDistances[i][j - 1] + euclideanDistance(j - 1, j);
            }
            //cout << "bitonicDistances[i][j] = " << bitonicDistances[i][j] << endl;
        }
    }
    return bitonicDistances[N - 1][N - 1];
}


int main() {
    int N;
    cin >> N;

    vector<pair<ll, ll>> points(N);

    REP(n, N) {
        cin >> points[n].first >> points[n].second;
    }
    cout << std::fixed << std::setprecision(20) << bitonic_tour(N, points) << endl;

    return 0;
}
