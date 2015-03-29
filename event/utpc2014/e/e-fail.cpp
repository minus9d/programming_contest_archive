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

struct Tree {
    // digit, money
    map<int, ll> digit_money;

    // digit, tree
    map<int, Tree> trees;
};

ll mnt_tree(Tree& t, int money){
    ll ret = 0;
    for (auto& p : t.digit_money){
        p.second += money;
        ret = max(p.second, ret);
    }
    for (auto& tree : t.trees){
        if (t.digit_money.count(tree.first)) {
            ret = max(ret, mnt_tree(tree.second, t.digit_money[tree.first]));
        }
        else {
            ret = max(ret, mnt_tree(tree.second, money));
        }
    }
    return ret;
}


ll insert_str(Tree& t, string a, ll money)
{
    if (SIZE(a) == 1){
        t.digit_money[a[0]] = money;

        // 子孫の点数増やす
        ll score_max = max(money, mnt_tree(t.trees[a[0]], money));
        return score_max;
    }
    else
    {
        string new_a = a.substr(1);
        return insert_str(t.trees[a[0]], new_a, money);
    }
}

int main(void)
{
    int N;
    cin >> N;

    ll mx = 0;
    Tree t;
    REP(n, N){
        string a;
        ll money;
        cin >> a >> money;

        reverse(ALL(a));

        ll score = insert_str(t, a, money);
        mx = max(score, mx);
        cout << mx << endl;
    }

    return 0;
}
