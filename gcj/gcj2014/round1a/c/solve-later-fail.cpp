// BADの場合は、ある数字が同じ場所にとどまる確率が、GOODの場合と比べて違うのではないか…と考えて書いたコード。
// 確かに違うのは事実だが、それだけではGOODとBADを見分ける証拠としては弱いようでダメだった。

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <random>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair


void make_random_array(int array_size, int loop_num){
    std::mt19937 engine ;

    vector<int> arr(array_size);

    // good
    int same_num = 0;
    REP(loop, loop_num){
        REP(i, array_size) arr[i] = i;
        REP(i, array_size) {
            std::uniform_int_distribution<int> distribution( i, array_size - 1 ) ;
            int picked = distribution(engine);
            swap(arr[i], arr[ picked ]);
        }

        REP(i, array_size) {
            if (arr[i] == i) ++same_num;
        }
    }
    cout << same_num << endl;

    // bad
    same_num = 0;
    std::uniform_int_distribution<int> distribution2( 0, array_size - 1 ) ;
    REP(loop, loop_num){
        REP(i, array_size) arr[i] = i;
        REP(i, array_size) {
            swap(arr[i], arr[ distribution2(engine) ]);
        }

        REP(i, array_size) {
            if (arr[i] == i) ++same_num;
        }
    }
    cout << same_num << endl;
}


int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    make_random_array(1000, 1000000);


    for(int test = 0; test < TEST_NUM; ++test){
        int N;
        cin >> N;

        int cnt = 0;
        REP(n, N){
            int num;
            cin >> num;
            if (num == n) ++cnt;
        }


        cout << "Case #" << (test+1) << ": ";
        string ret = (cnt == 0) ? "BAD" : "GOOD";
        cout << ret << endl;
    }

    return 0;
}
