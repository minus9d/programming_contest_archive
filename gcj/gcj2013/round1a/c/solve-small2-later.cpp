#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

void print_vec(vector<int> vec){
    FOREACH(e, vec){
        cout << *e << ", ";
    }
    cout << endl;
}


void make_all_draw_patterns(vector<vector<int> > &draw_patterns, int N, int M){
    
}

void make_all_draw_patterns_not_good(vector<vector<int> > &draw_patterns, int N, int M){
    FOR(i, 2, M+1){
        vector<int> arr(1, i);
        draw_patterns.push_back(arr);
    }

    FOR(n, 1, N){
        vector<vector<int> > draw_patterns_;
        FOR(i, 2, M+1){
            REP(j, SIZE(draw_patterns)){
                vector<int> arr = draw_patterns[j];
                arr.push_back(i);
                draw_patterns_.push_back(arr);
            }
        }
        draw_patterns = draw_patterns_;
    }
}

int main(void)
{
    int T;
    cin >> T;
    

    REP(t, T){

        // 2からMまでの数字がかかれたカードの中から、等確率でN枚のカードを選ぶ
        // 以下のことをK回繰り返す
        //   - N枚のカードのそれぞれを0.5の確率で取り出したサブセットを作る
        //   - サブセットに含まれるカードの数字の積を書き出す
        // N, Mと数字の積から、N枚のカードの数字が何だったかを当てる

        //         small  large
        int R; //   100   8000
        int N; //     3     12
        int M; //     5      8
        int K; //     7     12
        cin >> R >> N >> M >> K;

        


        // draw_patternsには、N枚のカードを選ぶすべての選び方が入る
        vector<vector<int> > draw_patterns;
        make_all_draw_patterns(draw_patterns, N, M);

        // for debug
        // FOREACH(arr, draw_patterns){
        //     FOREACH(e, *arr){
        //         cout << *e << ", ";
        //     }
        //     cout << endl;
        // }


        // P(N枚のカード|数字の積)が最大になるN枚のカードを当てる、という問題
        // ベイズの法則
        //   P(A|B) = P(B|A)P(A) / P(B)
        // を使うと、上記問題は
        // P(数字の積|N枚のカード)P(N枚のカード)が最大となるN枚のカードを当てる、
        // という問題になる


        // 桁dがC_d回でる確率
        

        

        // prob_list[ product ][ draw_pattern ] = 確率
        vector< map< vector<int>, double > > prob_list(M * M * M + 1);

        // 各カードの選び方のそれぞれに対して
        REP(j, SIZE(draw_patterns)){
            vector<int> draw = draw_patterns[j];
            sort(draw.begin(), draw.end());

            // サブセットの積と、その確率
            map<int, double> p;

            // initial
            p[1] = 0.5;
            p[draw[0]] = 0.5;
            
            FOR(mem, 1, SIZE(draw)){
                map<int, double> p_;
                int num = draw[mem];

                FOREACH(it, p){
                    int product = it->first;
                    double prob = it->second;

                    p_[ product ] += prob / 2.0;
                    p_[ product * num ] += prob / 2.0;
                }
                p = p_;
            }

            // record
            FOREACH(it, p){
                int product = it->first; // サブセットの積
                double prob = it->second; // その確率

                prob_list[ product ][draw] += prob;
                cout << "product, prob, draw = " << product << ", " << prob  << ", ";
                print_vec(draw);
                cout << endl;
            }
        }

        cout << "Case #" << (t+1) << ":" << endl;
        REP(r, R){
            map<vector<int>, int> counter;
            double best_prob = -0.1;
            vector<int> best_arr;
                
            // selected_cards, prob
            map< vector<int>, double > bin;

            // サブセットの積を計算する作業はK回行われる
            REP(kk, K){
                int product = 0; // 観測されたサブセットの積
                cin >> product;
                
                map< vector<int>, double > draw_pattern_to_prob = prob_list[ product ];

                FOREACH(it, draw_pattern_to_prob){
                    vector<int> arr = it->first;
                    double prob = it->second;

                    // 間違いでは？
                    //bin[ arr ] += prob;

                    // 直した
                    bin[ arr ] *= prob;

                    
                    counter[ arr ] += 1;
                }
            }

            FOREACH(it, bin){
                if (counter[it->first] != K){
                    continue;
                }
                    
                if (it->second > best_prob){
                    best_prob = it->second;
                    best_arr = it->first;
                }
            }

            REP(i, SIZE(best_arr)){
                cout << best_arr[i];
            }
            cout << endl;
        }
        


    }

    return 0;
}
