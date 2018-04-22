// ���: x���W���K���قȂ�N�_���^������B
//      x���W���ŏ��̓_���n�_�Ax���W���ő�̓_��܂�Ԃ��_�Ƃ��Ă��ׂĂ̓_��ʂ�������o�H�̂���
//      �ŒZ�H�����߂�B
// ��@: http://marcodiiga.github.io/bitonic-tour �����̂܂܎����B
//       ���S�ɂ͗����ł��Ă��Ȃ�
// �Q��: http://nyanp.hatenablog.com/entry/20121014/p1
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

    // [x][y]: �_x����A������0�܂ōs���A�E���ɕ�����ς��Ay�ŏI���ŒZ�̃o�C�g�j�b�N�p�X�B
    // x == y�̂Ƃ��͎n�_�ƏI�_����v����
    vector<vector<double>> bitonicDistances(N, vector<double>(N, -1));

    // �ŏ��͓_0�݂̂����݂���Ƃ��납��n�߂�
    bitonicDistances[0][0] = 0;

    // �_��1�_�����₵�Ă���  �����͕Г��Ȃ̂Ŏ���
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
            // �I�_���E�ɐL�тĂ��������Ȃ̂Ŏ���
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
