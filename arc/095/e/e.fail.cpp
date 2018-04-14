// 本番では、必要条件を満たさない場合にNOを出力するプログラムを実装→100.txtのみWA
// テストケースの特定も考えたが完遂できなかった


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

bool is_sym(string s) {
    map<char, int> cnt;
    for(auto ch: s) {
        ++cnt[ch];
    }
    int odd_num = 0;
    for (auto e: cnt) {
        if (e.second % 2) ++odd_num;
    }
    return odd_num <= 1;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int H, W;
    cin >> H >> W;
    vector<string> cells(H);
    REP(h, H) cin >> cells[h];

    map<string, int> rows;
    for(auto s: cells) {
        sort(ALL(s));
        ++rows[s];
    }

    map<string, int> cols;
    REP(w, W) {
        string s = "";
        REP(h, H) {
            s += cells[h][w];
        }
        sort(ALL(s));
        ++cols[s];
    }

    int odd_r = 0;
    for(auto r: rows) {
        // cout << r.first << " " << r.second << endl;
        if (r.second % 2) ++odd_r;
    }
    // cout << endl;

    int odd_c = 0;
    for(auto c: cols) {
        // cout << c.first << " " << c.second << endl;
        if (c.second % 2) ++odd_c;
    }

    if (odd_r > 1 || odd_c > 1) {
        cout << "NO" << endl;
    }
    else {
        cout << "YES" << endl;
    }

    return 0;
}

