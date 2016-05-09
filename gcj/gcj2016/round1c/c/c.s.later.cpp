// J, P, Sから1つずつ服を選んで組み合わせる。
// まったく同じ服の組み合わせは禁止。
// JとP, JとS, PとSとで同じ組み合わせが出現する回数はK回まで許容。
// 何日間異なる服装をできるかを答える。
//
// smallはbrute force。このコードだと遅すぎるので、問題のダウンロード前に前もって計算しておくなどの方法が考えられる。

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
#include <climits>
#include <complex>

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
#define mt make_tuple

int bitcount(int n) {
    int ans = 0;
    while (n) {
        if (n & 1) ++ans;
        n /= 2;
    }
    return ans;
}

int get_max(vector<int>& seen)
{
    int ret = 0;
    for (auto& e : seen) {
        ret = max(ret, e);
    }

    return ret;
}

void solve(void)
{
    int J, P, S, K;
    cin >> J >> P >> S >> K;

    vector<tuple<int, int, int>> combs;
    REP(j, J) {
        REP(p, P) {
            REP(s, S) {
                combs.push_back(mt(j, p, s));
            }
        }
    }

    int num = J * P * S;
    if (K >= 3) {
        cout << num << endl;
        for (auto& c : combs) {
            printf("%d %d %d\n", get<0>(c) + 1, get<1>(c) + 1, get<2>(c) + 1);
        }
    }
    else {
        int best_ans = 0;
        int best_comb = 0;

        REP(i, 1 << num) {
            if (i == 0) continue;
            int ans = bitcount(i);
            if (ans <= best_ans) continue;

            //map<pair<int, int>, int> seen1;
            //map<pair<int, int>, int> seen2;
            //map<pair<int, int>, int> seen3;

            vector<int> seen1(J*P);
            vector<int> seen2(J*S);
            vector<int> seen3(P*S);

            bool fail = false;
            REP(j, num) {
                if ((1 << j) & i) {
                    auto& c = combs[j];
                    seen1[get<0>(c) * P + get<1>(c)]++;
                    seen2[get<0>(c) * S + get<2>(c)]++;
                    seen3[get<1>(c) * S + get<2>(c)]++;

                    if (get_max(seen1) > K || get_max(seen2) > K || get_max(seen3) > K) {
                        fail = true;
                        break;
                    }
                }
            }

            if (fail) {
               continue;
            }

            best_ans = ans;
            best_comb = i;
        }

        cout << best_ans << endl;
        REP(j, num) {
            if ((1 << j) & best_comb) {
                auto& c = combs[j];
                printf("%d %d %d\n", get<0>(c) + 1, get<1>(c) + 1, get<2>(c) + 1);
            }
        }
    }
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": ";
        solve();
    }

    return 0;
}
