// ダブリングで解く
// ダブリングのコードは http://satanic0258.hatenablog.com/entry/2017/02/23/222647 を参考とした

#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define pb push_back
#define mp make_pair
#define mt make_tuple

// floor(log2(N))を求める  N>=2とする
ll calc_log2(ll N) {
    ll ans = 1;
    ll v = 2;
    while(v < N) {
        v *= 2;
        ans += 1;
    }
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, K;
    cin >> N >> K;
    vector<int> As(N);
    REP(n, N) {
        int a;
        cin >> a; --a;
        As[n] = a;
    }

    // K: 何個先まで見る必要があるか
    ll LOG = calc_log2(K);

    // next[k][i]で、i番目の要素の「2^k個次の要素」を指す
    // (なお、i番目の要素に対して「2^k個次の要素」が存在しないとき、
    //  next[k][i]が指し示す要素番号を-1とします)
    std::vector<std::vector<int>> next(LOG + 1, std::vector<int>(N)); 

    // next[0]を計算
    for (int i = 0; i < N; ++i){
        next[0][i] = As[i];
    }

    // nextを計算
    for (int k = 0; k < LOG; ++k){
        for (int i = 0; i < N; ++i){
            if (next[k][i] == -1) {
                // 2^k個次に要素が無い時、当然2^(k+1)個次にも要素はありません
                next[k + 1][i] = -1;
            }
            else {
                // 「2^k個次の要素」の2^k個次の要素は、2^(k+1)個次の要素です
                next[k + 1][i] = next[k][next[k][i]];
            }
        }
    }

    // ----ここまで準備----

    // p番目の要素の「K個次の要素」を求めることを考えます
    int p = 0;
    for (int k = LOG - 1; k >= 0; --k){
        if (p == -1) {
            // pがすでに存在しない要素を指していたら、
            // それ以降で存在する要素を指すことはないためループを抜けます
            break;
        }
        if ((K >> k) & 1) {
            // Qを二進展開した際、k番目のビットが立っていたら、
            // pの位置を2^kだけ次にずらします
            p = next[k][p];
        }
    }

    cout << p + 1 << endl;

    return 0;
}
