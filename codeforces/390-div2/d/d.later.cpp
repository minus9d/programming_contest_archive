// 参考：http://kmjp.hatenablog.jp/entry/2017/01/07/0930

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
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
    int N, K;
    cin >> N >> K;

    vector<int> L(N);
    vector<int> R(N);

    // 始点・終点の両方を保持
    map<int, vector<int>> E;

    REP(n,N) {
        cin >> L[n] >> R[n];
        E[L[n]].pb(n);
        E[R[n]].pb(n + 1000000);
    }

    // 終点のうち後ろにあるK個のレンジを保持
    // {レンジの終点、レンジのid}
    set<pair<int,int>> S;

    // 左側にある点からループ
    int mx = 0;
    int id = -1;
    vector<int> ans;
    for(auto r: E) {
        sort(ALL(r.second));
        for(auto e: r.second) {
            // 点は始点
            if (e < 1000000)  {
                S.insert({R[e],e});
                if (SIZE(S) > K) S.erase(S.begin());
                // この時点で終点の数がK個
                if (SIZE(S) == K) {
                    auto d = S.begin()->first - r.first + 1;
                    if (d > mx) {
                        mx = d;
                        // Sをそのまま記録するとTLEとなるので、
                        // 代わりにeを記録する
                        id = e;
                    }
                }
            }
            // 点は終点
            else {
                S.erase({R[e-1000000], e-1000000});
            }
        }
    }

    if (id == -1) {
        cout << 0 << endl;
        REP(k,K) {
            cout << (k == 0 ? "" : " ") << (k+1);
        }
        cout << endl;
        return 0;
    } 

    // 記録したidを元にもう一度正解を生成する
    for(auto r: E) {
        sort(ALL(r.second));
        for(auto e: r.second) {
            // 点は始点
            if (e < 1000000)  {
                S.insert({R[e],e});
                if (SIZE(S) > K) S.erase(S.begin());
                if (e == id) {
                    cout << mx << endl;
                    for(auto e: S) {
                        cout << e.second + 1 << " ";
                    }
                    cout << endl;
                    return 0;
                }
            }
            else {
                S.erase({R[e-1000000], e-1000000});
            }
        }
    }
             
    return 0;
}
