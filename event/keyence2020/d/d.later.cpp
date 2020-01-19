// 終了3分後に自力AC
//
// すべてのカードは、左から奇数番目位置か偶数番目位置かのみによって
// 表か裏かが確定することに着目
// 左から奇数番目に来るカードと偶数番目に来るカードを決め打つと、
//   - 広義単調増加列が作れるかどうかが判定できる。
//   - swap回数は転倒数により求められる。

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

// bool is_sorted(const vector<int>&sorted) {
//     int prev = -1e9;
//     for(auto s: sorted) {
//         if (s < prev) return false;
//         prev = s;
//     }
//     return true;
// }

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<pair<int,int>> ABs(N);
    REP(n, N) {
        cin >> ABs[n].first;
    }
    REP(n, N) {
        cin >> ABs[n].second;
    }

    // // 実際にシャッフルしてみる
    // vector<int> shff2(N);
    // REP(n, N) shff2[n] = n;
    // do {
    //     vector<int> sorted;
    //     REP(i, N) {
    //         auto s = shff2[i];
    //         if ((s % 2) == (i % 2)) {
    //             sorted.pb(ABs[s].first);
    //         } else {
    //             sorted.pb(ABs[s].second);
    //         }
    //     }
    //     // for(auto s: shff2) cout << s << " "; cout << endl;
    //     // cout << "  "; for(auto s: sorted) cout << s << " "; cout << endl;
    //     // if (is_sorted(sorted)) cout << "  " << "sorted!" << endl;

    // }while(next_permutation(ALL(shff2)));

    // N枚のカードのうち、
    // 左から1番目, 3番目, 5番目, ...に位置するカードを1,
    // 左から2番目, 4番目, 6番目, ...に位置するカードを0とする
    vector<int> shff(N);
    REP(i, (N + 1) / 2) shff[i] = 1;
    sort(ALL(shff));

    ll ans = 1e18;

    // 左から1番目, 3番目, ... に位置するカードの数字
    vector<int> set1((N + 1) / 2);
    // 左から2番目, 4番目, ... に位置するカードの数字
    vector<int> set2(N - SIZE(set1));
    // 左から1番目, 2番目, ... に位置するカードの数字
    vector<int> target(N);
    do {
        int set1_idx = 0;
        int set2_idx = 0;
        REP(i, N) {
            auto e = shff[i];
            if (e == 1) {
                if (i % 2 == 0) {
                    set1[set1_idx++] = ABs[i].first;
                    target[i] = ABs[i].first;
                } else {
                    set1[set1_idx++] = ABs[i].second;
                    target[i] = ABs[i].second;
                }
            } else {
                if (i % 2 == 0) {
                    set2[set2_idx++] = ABs[i].second;
                    target[i] = ABs[i].second;
                } else {
                    set2[set2_idx++] = ABs[i].first;
                    target[i] = ABs[i].first;
                }
            }
        }

        // cerr << "set:" << endl;
        // cerr << "  "; for(auto s: shff) cout << int(s) <<" "; cout << endl;
        // cerr << "  "; for(auto s: set1) cout << s <<" "; cout << endl;
        // cerr << "  "; for(auto s: set2) cout << s <<" "; cout << endl;

        // 解条件を満たすかチェック
        // set1, set2それぞれをソートしたものが増加列になっていればOK
        bool ok = true;
        int prev = -1;
        set1_idx = 0;
        set2_idx = 0;
        auto sorted_set1 = set1;
        auto sorted_set2 = set2;
        sort(ALL(sorted_set1));
        sort(ALL(sorted_set2));
        REP(i, N) {
            int curr = 0;
            if (i % 2 == 0) curr = sorted_set1[set1_idx++];
            else curr = sorted_set2[set2_idx++];
            if (curr < prev) {
                ok = false;
                break;
            } else {
                prev = curr;
            }
        }
        if (!ok) continue;

        // ここに来たなら増加列を作れることは確定
        // ソートが必要な回数は、転倒数により求められる
        int i = 0;
        // ソートしたあとの各カードが、もとの何番目のカードだったかを示す配列
        vector<int> arr(N);
        vector<int> seen(N);
        // sorted_set1のそれぞれについて、
        // もとの配列の何番目だったかを愚直に探索
        for(auto s: sorted_set1) {
            REP(n, N) {
                if (seen[n]) continue;
                if (shff[n] == 1 && target[n] == s) {
                    seen[n] = 1;
                    arr[i] = n;
                    i += 2;
                }
            }            
        }
        // sorted_set2のそれぞれについて、
        // もとの配列の何番目だったかを愚直に探索
        i = 1;
        for(auto s: sorted_set2) {
            REP(n, N) {
                if (seen[n]) continue;
                if (shff[n] == 0 && target[n] == s) {
                    seen[n] = 1;
                    arr[i] = n;
                    i += 2;
                }
            }            
        }
        // cout << "arr: "; for(auto a: arr) cout << a << " "; cout << endl;
        // 転倒数を愚直に計算
        ll num = 0;
        REP(i, N - 1) {
            FOR(j, i + 1, N) {
                num += arr[j] < arr[i];
            }
        }

        ans = min(ans, num);

    } while(next_permutation(ALL(shff)));

    if (ans == 1e18) cout << -1 << endl;
    else cout << ans << endl;

    return 0;
}
