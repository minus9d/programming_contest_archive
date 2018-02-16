//
//  ....1222?????112..
//  a   bc        de   f
//
//  2で始まり1で終わる区間が、反転させる価値のある区間。
//  例えば↑でcからdの区間を反転させたとする。
//  このときの単調増加配列の最長サイズは以下の和になる
//    (i)aからbまでの区間に含まれる1の数
//    (ii)cからdまでの区間を反転させたときの、単調増加配列の最長サイズ
//    (iii)eからfまでの区間に含まれる2の数
//  (i)(ii)(iii)をすべての区間について事前に計算しておけば、
//  すべてのありうる反転をすべて試せる

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

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
    int N;
    cin >> N;
    vector<int> P(N);
    REP(n,N) cin >> P[n];
    vector<int> one_ends;
    vector<int> two_starts;

    vector<pair<int,int>> lists;
    for (auto p: P) {
        if (lists.empty()) {
            lists.pb(mp(p, 1));
        }
        else {
            auto prev = lists.back().first;
            if (prev == p) {
                ++lists.back().second;
            }
            else {
                lists.pb(mp(p, 1));
            }
        }
    }

    //for(auto l: lists) {
    //    cout << "(" << l.first << "," << l.second << ") ";
    //}
    //cout << endl;

    auto S = SIZE(lists);
    vector<vector<int>> ones(S, vector<int>(S));
    vector<vector<int>> twos(S, vector<int>(S));
    vector<vector<int>> two_to_one(S, vector<int>(S));
    REP(i, S) {
        FOR(j, i, S) {
            if (j == i) {
                if (lists[j].first == 1) {
                    ones[i][j] = lists[i].second;
                }
                else {
                    twos[i][j] = lists[i].second;
                }
                two_to_one[i][j] = lists[i].second;
            }
            else {
                if (lists[j].first == 1) {
                    ones[i][j] = lists[j].second + ones[i][j-1];
                    twos[i][j] = twos[i][j-1];
                    two_to_one[i][j] = two_to_one[i][j - 1] + lists[j].second;
                }
                else {
                    twos[i][j] = lists[j].second + twos[i][j-1];
                    ones[i][j] = ones[i][j-1];
                    two_to_one[i][j] = max(two_to_one[i][j - 1], twos[i][j]);
                }
            }
        }
    }

    //REP(i, S) {
    //    FOR(j, i, S) {
    //        cout << "[" << i << ", " << j << "] " << ones[i][j] << endl;
    //    }
    //}
    //cout << endl;
    //REP(i, S) {
    //    FOR(j, i, S) {
    //        cout << "[" << i << ", " << j << "] " << twos[i][j] << endl;
    //    }
    //}
    //cout << endl;


    auto ans = 0;
    //// no swap
    //auto ans = max(twos[0][S-1], ones[0][S-1]);
    //REP(n, S-2) {
    //    ans = max(ans, ones[0][n] + twos[n+1][S-1]);
    //}


    // REP(n, N-1) {
    //     if (P[n] == 1 && P[n+1] == 2) {
    //         two_starts.pb(n+1);
    //         one_ends.pb(n);
    //     }
    // }


    // swap from [i, j]
    REP(i, S) {
        FOR(j, i, S) {
            auto local_ans = 0;
            if (i > 0) local_ans += ones[0][i - 1];
            if (j < S - 1) local_ans += twos[j + 1][S - 1];
            local_ans += two_to_one[i][j];
            ans = max(ans, local_ans);
        }
    }

    cout << ans << endl;

    return 0;
}
