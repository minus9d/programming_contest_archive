// http://abc001.contest.atcoder.jp/submissions/107453

#include<stdio.h>
#include<algorithm>
using namespace std;
pair<int,int> event[60000];
 
int main(){
    int a,b;
    scanf("%d",&a,&b);
    for(int i=0;i<a;i++){
        int p,q;
        scanf("%d-%d",&p,&q);
        printf("p, q = %d, %d at 1\n", p, q);

        p=p/100*60+p%100;
        q=q/100*60+q%100;

        printf("p, q = %d, %d at 2\n", p, q);
        if(p%5)p-=p%5;
        if(q%5)q+=(5-q%5);

        // 1と2という数字のおかげで、ソートした時に開始時刻の方が先にくるようにできる
        event[2*i]=make_pair(p,1);
        event[2*i+1]=make_pair(q,2);

        printf("p, q = %d, %d at 3\n", p, q);
    }
    std::sort(event,event+a*2);


    int now=0; // 今何個の区間が重なっているかをカウントする
    int start=0;
    for(int i=0;i<a*2;i++){
        //printf("%d %d\n",event[i].first,event[i].second);

        // 開始時刻の場合
        if(event[i].second==1){
            // この区間から開始する
            if(now==0)start=event[i].first;
            now++;
        }
        // 終了時刻の場合
        else now--;

        // この区間で終わり
        if(now==0){
            printf("%02d%02d-%02d%02d\n",start/60,start%60,event[i].first/60,event[i].first%60);
        }
    }
}
