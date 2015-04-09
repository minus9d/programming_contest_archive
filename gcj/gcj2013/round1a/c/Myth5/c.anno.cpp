// original:
//   Myth5's solution to Google Code Jam 2013 Round 1A C. Good Luck
//   http://www.go-hero.net/jam/13/name/Myth5

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 12 + 5, maxk = 12 + 5;

int R, N, M, K;
long long p[maxk], jc[maxn];
char a[maxn];

// 問題
// 2からMまでの数字がかかれたカードの中から、等確率でN枚のカードを選ぶ
// 以下のことをK回繰り返す
//   - N枚のカードのそれぞれを0.5の確率で取り出したサブセットを作る
//   - サブセットに含まれるカードの数字の積を書き出す
// N, Mと数字の積から、N枚のカードの数字が何だったかを当てる

//              small  large
//        R      100   8000
//        N        3     12
//        M        5      8
//        K        7     12


// カードの選び方に関する構造体
// a: カードの選び方　(eg. [2, 2, 2, 3, 3, 4, 4])
// rep: このカードの選び方の確率を計算するときに使う値。(2の枚数)! * ... * (Mの枚数)!で計算される
//     直感的に、同じ数字のカードが多い = repの数が大きい = 確率低い
// P: サブセットの積と、その確率をテーブルで保持
// check(): 観測されたサブセットの積がp[]に格納されている時、Pr( サブセットの積 | カードの選び方 )を計算
struct Sol {
    string a;
    long long rep;
    map<long long, int> P;
    double check()
    {
        double ret = 1;
        for (int i = 1; i <= K; ++i) {
            map<long long, int>::iterator it = P.find(p[i]);
            if (it == P.end())
                return 0;
            ret *= it->second;
        }
        return ret / rep;
    }

    void print(){
        cout << "-----" << endl;
        cout << "a = " << a << endl;
        cout << "rep = " << rep << endl;
        cout << "P = " << endl;
        for(map<long long, int>::iterator it = P.begin();
            it != P.end();
            ++it){
            cout << "   key: " << it->first << ", val: " << it->second << endl;
        }
        cout << "-----" << endl;
    }
};
vector<Sol> v;

// すべてのカードの選び方をdfsで求める
void dfs(int i)
{
    if (i == N) {
        // あるカードの選び方が見つかった
        Sol t;
        t.a = string(a);
        //cout << a << endl;
        t.rep = 1;
        for (int j = 0, k = -1; j < N; ++j)
            if (a[j] != a[j + 1]) {
                t.rep *= jc[j - k];
                k = j;
            }

        // すべてのとりうるサブセットをシミュレーション
        for (int j = 0; j < (1 << N); ++j) {
            long long pro = 1;
            for (int k = 0; k < N; ++k)
                if (j & (1 << k))
                    pro *= a[k] - '0';
            ++t.P[pro];
        }
        v.push_back(t);

        
        // t.print();
        
    }else
        //cout << "i = " << i << endl;
        for (char j = i > 0 ? a[i - 1] : '2'; j <= '0' + M; ++j) {
            //cout << "  j = " << j << endl;
            a[i] = j;
            dfs(i + 1);
        }
}

int main()
{
    // freopen("c2.in", "r", stdin);
    // freopen("c2.out", "w", stdout);

    int t2;
    cin >> t2;
    for (int t1 = 1; t1 <= t2; ++t1) {
        printf("Case #%d:\n", t1);
        cin >> R >> N >> M >> K;
        jc[0] = 1;
        for (int i = 1; i <= N; ++i)
            jc[i] = jc[i - 1] * i;
        a[N] = '\0';
        dfs(0);
        while (R--) {
            for (int i = 1; i <= K; ++i)
                cin >> p[i];
            double ret = 0;
            int reti = 0;
            for (int i = 0; i < v.size(); ++i) {
                double t = v[i].check();
                if (t > ret) {
                    ret = t;
                    reti = i;
                }
            }
            cout << v[reti].a << endl;
        }
        printf("\n");
    }
    
    return 0;
}
