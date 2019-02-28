// 全然わからないので解説PDFを読む
//
// * すべての整数は1から初めて+1 or *10の操作で到達できる
// * +1すると桁和は1増え、*10すると桁和は変わらない
// までは理解できたのだが、mod Kする操作が理解できなかった
//
// 以下のように考えてなんとなく理解できた
//
// K = 7の場合を考える。
// もし7の倍数のいずれかが1, 10, 100, 1000, ... のどれかになれば答は最小の1になる。
// しかし、上記数列のmod 7を調べると1, 3, 2, 6, 4, 5, 1, ...の
// ループになりそうなことがわかる
// つまり残念ながら答が1になることはない。
//
// しかし、上記のループの中に"6"がある。これは1000に相当する。
// ここに+1すると1001で、mod 7は0になる。答は1にはなりえないので、
// 答は2である。
//
// 上の考察からもう少し飛躍させると、解答PDFのようなグラフになる。
//
// もし回答として桁和が最小になる数を答える必要がある場合は、
// グラフの0の辺をたどるたびに*10, 1の辺をたどるたびに+1すればよい


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
    int K;
    cin >> K;

    // 01-BFS
    deque<int> dq;
    vector<int> best(K, 1e9);
    vector<char> seen(K);
    dq.push_back(1);
    best[1] = 1;
    while (!dq.empty()) {
        int v = dq.front(); dq.pop_front();

        // *10に相当
        int v2 = (v * 10) % K;
        if (best[v2] > best[v]) {
            best[v2] = best[v];
            dq.push_front(v2);
        }

        // +1に相当
        int v3 = (v + 1) % K;
        if (best[v3] > best[v] + 1) {
            best[v3] = best[v] + 1;
            dq.push_back(v3);
        }
    }

    cout << best[0] << endl;
    return 0;
}
