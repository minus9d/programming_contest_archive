// 参考：http://rsujskf.s602.xrea.com/?googlecodejam_2014_1a_b
// 使用していない変数などを整理済

#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
#include<string>
#include<utility>
#include<iostream>
#include<cmath>
using namespace std;

#define REP(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) REP(i,0,n)

#define INF 1000000000

int N;
int edge[1200][1200]; ///< エッジのリスト
int es[1200]; ///< 頂点が持つエッジの数

// now番目のノード以下、残せるノードの最大数を求める
// befは、i番目のノードの親。間違って親側に逆流することを防ぐ
int solve(int now, int bef){
    int i, j, k;

    // now番目のノードの子ノードのそれぞれが、何個のノードを残せるか
    vector<int> num;

    // now番目のノードが持つエッジでループ
    rep(k,es[now]){
        i = edge[now][k];
        if(i==bef) continue;
        num.push_back( solve(i, now) );
    }

    // now番目のノードの子の数が0個または1個の場合は、まったく子は残せないので1
    int ret = 1;

    // now番目のノードの子の数が2個以上の場合は、残せる子の数が多いもの上位2個を選ぶ
    if(num.size() >= 2){
        sort(num.rbegin(), num.rend());
        ret += num[0] + num[1];
    }

    return ret;
}

int main(){
    int i, j, k;
    int res, tmp;
    int T, cnt = 0;

    scanf("%d",&T);
    while(T--){
        fprintf(stderr,"rest %d\n",T);
        printf("Case #%d: ", ++cnt);

        scanf("%d",&N);
        rep(i,N) es[i] = 0;
        rep(i,N-1){
            scanf("%d%d",&j,&k);
            // 0 originに直す
            j--; k--;
            edge[j][es[j]++] = k;
            edge[k][es[k]++] = j;
        }

        // debug print
        // printf("\n");
        // rep(i, N){
        //     printf("es[%d] = %d\n", i, es[i]);
        //     rep(j, es[i]){
        //         printf("  edge ->%d\n", edge[i][j]);
        //     }
        // }

        res = INF;
        // 何番目を頂点にするかのループ
        // 一番良い結果を選ぶ
        rep(i,N){
            tmp = solve(i, -1);
            res = min(res, N-tmp);
        }

        printf("%d\n", res);
    }

    return 0;
}
