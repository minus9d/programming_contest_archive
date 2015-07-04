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
#define mt make_tuple

// ...  <- _ _ _ -> ...
// となっている場合、splitして
// ... <-  と  -> ... だけ考えればよい
//
// 端の ... <- 

struct Rabbit{int x; char dir;};

// 左側を向いているうさぎを、goalの位置まで動かす
// (goal) ...  <- .. <-
ll jump_left(int goal, vector<Rabbit>& seq) {
    ll ret = 0;
    for(auto& r : seq) {
        if (r.dir == 'R') continue;
        ret += abs(r.x - goal);
        ++goal;
    }
    return ret;
}

// 右側を向いているうさぎを、goalの位置まで動かす
// -> .. -> .. (goal)
ll jump_right(int goal, vector<Rabbit>& seq) {
    ll ret = 0;
    for(int i = seq.size()-1; i >= 0; --i) {
        auto& r = seq[i];
        if (r.dir == 'L') continue;
        ret += abs(r.x - goal);
        --goal;
    }
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N, L;
    cin >> N >> L;
    
    vector<Rabbit> rs(N);
    REP(n,N) {
        cin >> rs[n].x >> rs[n].dir;
        --rs[n].x;
    }
    
    // うさぎが内側に向かい合う部分ごとにsplitする
    vector<vector<Rabbit>> rss;
    char prev = 'z';
    vector<Rabbit> tmp;
    for (auto& r : rs) {
        if (prev == 'L' && r.dir == 'R') {
            rss.pb(tmp);
            prev = 'z';
            tmp.clear();
        }
        tmp.pb(r);
        prev = r.dir;
    }
    rss.pb(tmp);

    ll ret = 0;
    for(auto& seq : rss) {
        // for(auto & r : seq) cout << r.x <<",";
        // cout << endl;

        if (seq.front().dir == seq.back().dir) {
            // (i)うさぎがすべて左を向いている場合
            if (seq[0].dir == 'L') {
                ret += jump_left(0, seq);
            }
            // (ii)うさぎがすべて右を向いている場合
            else {
                ret += jump_right(L-1, seq);
            }
        }
        // (iii)うさぎが内側を向いている場合
        // -> ... -> ... <- ... <-
        else {
            // 
            int Lnum = 0;
            int Rnum = 0;
            for(auto& r : seq) {
                if (r.dir == 'L') ++Lnum;
                else ++Rnum;
            }
            // (iii)-1 右を向いているうさぎの方が多い場合
            //  -> .. -> .. -> ... (goal) <- ... <-
            if (Rnum > Lnum) {
                int goal = 0;
                for(auto& r : seq) {
                    if (r.dir == 'L') {
                        goal = r.x - 1;
                        break;
                    }
                }
                ret += jump_left(goal+1, seq);
                ret += jump_right(goal, seq);
            }
            // (iii)-2 (iii)-1の逆
            //  -> ..  -> (goal) .. <- ... <-  .. <-
            else {
                int goal = 0;
                for(auto& r : seq) {
                    if (r.dir == 'R') {
                        goal = r.x + 1;
                    }
                }
                ret += jump_left(goal, seq);
                ret += jump_right(goal-1, seq);
            }
        }
    }

    cout << ret << endl;

    return 0;
}
