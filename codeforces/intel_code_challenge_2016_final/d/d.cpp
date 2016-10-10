// まず'a'だけ使って条件をカバーできるか調べる。
// カバーできる場合はなるべく最小の数の'a'だけ使うよう調整して終了。
// カバーできない場合は'a'を全部使うことが確定。
// 次に'b'を使って上と同じことを繰り返し。   

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


int M;

bool cover(const string str, vector<char>& used, char smallest) {
    int len = SIZE(str);
    int life = M;
    REP(i,len) {
        if (used[i] || str[i] == smallest) life = M;
        else life -= 1;
        if (life == 0) return false;
    }

    auto covered = used;
    //REP(i,len) {
    //    if (used[i]) {
    //        FOR(m,1,M) {
    //            if(covered[i-m]) break;
    //            if (i-m < 0) break;
    //            covered[i-m] = 1;
    //        }
    //        FOR(m,1,M) {
    //            if(covered[i+m]) break;
    //            if (i+m >= len) break;
    //            covered[i+m] = 1;
    //        }
    //    }
    //}

    life = M;
    int candidate = -1;
    REP(i,len) {
        if (covered[i]) {
            life = M;
        }
        else if (str[i] == smallest) {
            if (life == 1) {
                used[i] = smallest;
                life = M;
            }
            else {
                candidate = i;
                --life;
            }
        }
        else {
            --life;
            if (life == 0) {
                used[candidate] = smallest;
                i = candidate;
                life = M;
            }
        }
    }
    return true;
}

int main(void)
{
    cin.sync_with_stdio(false);
    cin >> M;
    string str;
    cin >> str;

    vector<char> used(SIZE(str), 0);
    char smallest = 'a';
    while(true) {
        if (cover(str, used, smallest)) {
            break;
        }
        else {
            REP(i,SIZE(str)) {
                if (str[i] == smallest) {
                    used[i] = smallest;
                }
            }
            smallest += 1;
        }
    }
    vector<char> ans;
    REP(i,SIZE(str)) {
        if (used[i]) ans.push_back(used[i]);
    }
    sort(ALL(ans));
    for(auto ch: ans) cout << ch;
    cout << endl;

    return 0;
}
