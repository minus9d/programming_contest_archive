#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
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
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

// vector<pair<char,int>> simplify(string s)
// {
//     s = s + 'z';
//     vector<pair<char,int>> ret;
//     int num = 0;
//     int m = 0;
//     for (auto ch : s) {
//         // cout << ch << ",";
//         // cout << "num,m = " << num << "," << m << endl;
//         if (ch != 'M') {
//             if (m != 0) {
//                 ret.pb( mp('M', m) );
//                 m = 0;
//             }
//             num += (ch == '+') ? 1 : -1;
//         }
//         if (ch != '+' || ch != '-') {
//             if (num != 0) {
//                 ret.pb( mp('N',num) );
//                 num = 0;
//             }
//             ++m;
//         }
//     }
//     return ret;
// }

int main(void)
{
    cin.sync_with_stdio(false);
    string s;
    cin >> s;
    int move_num = count(ALL(s), 'M');

    const int INF = 1e9;
    set<int> possible_pos;
    vector<vector<int>> mx(200001, vector<int>(2, -INF));
    int offset = 100000;
    possible_pos.insert(offset);

    // init
    bool flag = true;
    mx[offset][flag] = 0;

    for (auto e : s) {
        // cout << "========" << endl;

        flag = !flag;
        set<int> new_pos;

        // cout << "possible pos:";
        // for (auto p : possible_pos) cout << p << ",";
        // cout << endl;

        // cout << "ch: " << e << endl;
        for (auto p : possible_pos) {
            if (e == '+') {
                mx[p][flag] = mx[p][!flag] + (p - offset);
                new_pos.insert(p);
            }
            else if (e == '-') {
                mx[p][flag] = mx[p][!flag] - (p - offset);
                new_pos.insert(p);
            }
            else {
                // move right
                if (p + 1 - offset <= move_num / 2) {
                    new_pos.insert(p + 1);
                    mx[p + 1][flag]
                        = max(mx[p][!flag], 
                              mx[p + 1][flag]); 
                }
                // move left
                if (p - 1 - offset >= -move_num / 2) {
                    new_pos.insert(p - 1);
                    mx[p - 1][flag]
                        = max(mx[p][!flag], 
                              mx[p - 1][flag]); 
                }
            }
        }
        possible_pos = new_pos;


        // cout << "dp[0]: ";
        // for(int i = -2; i <= 2; ++i) {
        //     cout << mx[offset + i][0] << ",";
        // }
        // cout << endl;
        // cout << "dp[1]: ";
        // for(int i = -2; i <= 2; ++i) {
        //     cout << mx[offset + i][1] << ",";
        // }
        // cout << endl;

    }

    
    cout << mx[offset + 0][flag] << endl;

    return 0;
}
