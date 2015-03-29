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


int bubble_sort_rep_num(string s){
    int len = SIZE(s);
    int num = 0;
    REP(i, len-1){
        for(int j = len-1; j > i; --j){
            if (s[j] < s[j-1]) {
                swap(s[j], s[j-1]);
                ++num;
            }
        }
    }
    return num;
}

int main(void)
{
    int T;
    cin >> T;
    REP(t, T){
        string s;
        cin >> s;
        auto num = bubble_sort_rep_num(s);
        printf("%d\n",num % 2);
    }

    return 0;
}
