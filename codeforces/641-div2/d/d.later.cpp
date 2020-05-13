// 解説を見て実装
// Kより小さいのを0, Kを1, Kより大きいのを2としてよい
// 1が最低一つあり、かつ、距離1または距離2に1以上があれば"yes"

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())
#define pb push_back
#define mp make_pair
#define mt make_tuple

string solve(int N, int K, vector<int>& As) {
    // Kが1個もなければno
    if (find(ALL(As), K) == As.end()) {
        return "no";
    }

    // 以下では少なくとも1個のKがあるとしてよい

    // 配列の長さ1
    if (N == 1) {
        return "yes";
    }

    // 以下では配列の長さが2以上としてよい

    // 隣り合う数同士にK以上があるならyes
    REP(i, N - 1) {
        if (As[i] >= K && As[i + 1] >= K) {
            return "yes";
        }
    }
    // 1個離れた位置にK以上があるならyes
    REP(i, N - 2) {
        if (As[i] >= K && As[i + 2] >= K) {
            return "yes";
        }
    }

    return "no";
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T; cin >> T;
    REP(t, T) {
        int N; int K;
        cin >> N >> K;
        vector<int> As(N);
        REP(n, N) cin >> As[n];
        cout << solve(N, K, As) << endl;
    }

    return 0;
}
