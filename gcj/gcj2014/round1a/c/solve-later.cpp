// 参考：http://rsujskf.s602.xrea.com/?googlecodejam_2014_1a_c

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

// Gper[i][j]: BAD法により、a[i] = jとなる確率のN倍
double Gper[1200][1200];

// サイズnのアレーをBAD法で生成するのをt回シミュレート　確率をGper[i][j]に記録
void test3(int n, int t){
    int i, j, k, loop;
    vector<int> p(n);

    // per[i][j]: BAD法のシミュレート後、アレーのi番目の数字がjである回数をカウント
    static int per[1200][1200] = {};

    // BAD法をt回シミュレート
    rep(loop,t){
        rep(i,n) p[i] = i;
        rep(i,n){
            k = rand() % n; // bad
            swap(p[i], p[k]);
        }

        rep(i,n) per[i][p[i]]++;
    }

    rep(i,n) rep(j,n) Gper[i][j] = (double)per[i][j] / t * n;
  // rep(i,n){ rep(j,n) printf("%f ",(double)per[i][j]/t*n); puts(""); }
}

int main(){
    int i,j,k;
    int T, cnt = 0;
    int N, p[2000], sum;
    double res;
 
    test3(1000, 1000000);
  
    scanf("%d",&T);
    while(T--){
        fprintf(stderr,"rest %d\n",T);
        printf("Case #%d: ", ++cnt);

        scanf("%d",&N);
        rep(i,N) scanf("%d",p+i);
        res = 1;
        rep(i,N) res *= Gper[i][p[i]];
        if(res <= 1) puts("GOOD"); else puts("BAD");
    }

    return 0;
}
