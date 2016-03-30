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

bool isV(char ch){
    if (ch == 'a'
        || ch == 'e'
        || ch == 'i'
        || ch == 'o'
        || ch == 'u'){
        return true;
    }
    else{
        return false;
    }
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        string str;
        int N;
        int len;

        cin >> str;
        cin >> N;
        len = str.size();

        // 子音が連続N回以上続いているindexを保持
        vector<int> table;
        int succ = 0;
        REP(i,len) {
            if (!isV(str[i])) {
                ++succ;
                if (succ >= N) table.pb(i);
            }
            else {
                succ = 0;
            }
        }

        // i文字目からスタートする文字列に関して
        // サイズNの文字列を延ばしていって、最初に条件を満たす場所を二分部探索で見つける
        // それ以降どれだけ文字列を延ばしても条件を満たす
        ll ans = 0;
        REP(i, len) {
            auto cand = lower_bound(ALL(table), i + N - 1);
            // cout << "i, cand = " <<  i << "," <<  *cand << endl;
            if (cand == table.end()) continue;
            ll local_ans = len - *cand;
            // cout << "local_ans:" << local_ans << endl;
            ans += local_ans;
        }

        cout << "Case #" << (test+1) << ": " << ans << endl;
    }

    return 0;
}
