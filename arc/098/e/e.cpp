// 本番にて
//   最小値を固定して考えるところまでは思いついたが、その後どうしていいかわからなかった
// 本番後
//   解説を見る
//   最小値を固定し、与えられた数列を、その最小値未満の値が入らないように複数の部分列に分ける
//   ある部分列の長さをLとすると、その部分列中を小さい順に並べたときの小さい順からL-K+1個の値がとれうる
//   あとはこれをすべての部分列で求めて、マージし、最小な順にとっていけばよい

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

int main(void)
{
    cin.sync_with_stdio(false);
    int N, K, Q;
    cin >> N >> K >> Q;
    vector<int> As(N);
    set<int> seen;

    REP(n, N) {
        cin >> As[n];
        seen.insert(As[n]);
    }

    int ans = 1e9 + 10;
    vector<int> tmp;
    // 最小値を固定する
    for (auto mn : seen) {
        // 最小値未満の数が含まれないように部分列に分割する
        vector<vector<int>> nums;
        int sum = 0;
        for (auto a : As) {
            if (a < mn) {
                if (SIZE(tmp) >= K) {
                    nums.push_back(tmp);
                }
                tmp.clear();
            }
            else {
                tmp.push_back(a);
            }
        }

        if (SIZE(tmp) >= K) nums.push_back(tmp);
        tmp.clear();

        for (auto num : nums) {
            sum += (SIZE(num) - K + 1);
        }
        if (sum < Q) continue;

        vector<int> sorted;
        for (auto num : nums) {
            sort(ALL(num));
            auto len = SIZE(num);
            REP(i, len - K + 1) {
                sorted.push_back(num[i]);
            }
        }
        sort(ALL(sorted));
        auto mx = sorted[Q - 1];
        ans = min(ans, mx - mn);
    }
    cout << ans << endl;

    return 0;
}
