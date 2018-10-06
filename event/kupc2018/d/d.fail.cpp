// 実験用のコード
// ごく小さい数も通らず…

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

int simulate(int ans, int query) {
    return (ans % query) % 2;
}

vector<int> brute_force(int ans, int MAX) {
    vector<int> table(MAX+1); // 1: 答ではない

    vector<int> queries = {2, 3, 5, 7, 11, 
                           13, 17, 19, 23, 29,
                           31, 37, 41, 43, 47,
                           53, 59, 61, 67, 71,
                           73, 79, 83, 89, 97,
                           101, 103, 107, 109, 113
    REP(dummy, 30) {
        auto query = queries[dummy];
        auto ret = simulate(ans, query);
        FOR(j, 1, MAX+1) {
            if (((j % query) % 2) != ret) table[j] = 1;
        }
        // FOR(i, 1, MAX+1) cout << table[i] << " "; cout << endl;
    }
    vector<int> ret;
    FOR(i, 1, MAX+1) {
        if (table[i] == 0) {
            ret.push_back(i);
        }
    }
    return ret;
}

void test(){
    int MAX = 1e6;
    FOR(ans, 1, MAX+1) {
        auto ret = brute_force(ans, MAX);
        if (SIZE(ret) != 1) {
            cout << "error! ans = " << ans << endl;
            for(auto e: ret) cout << e << ","; cout << endl;
            return;
        }
    }
}

int main(void)
{
    cin.sync_with_stdio(false);

    test();


    return 0;
}
