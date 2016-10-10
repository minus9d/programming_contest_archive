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

priority_queue<int,vector<int>> q;
set<int> members;

// -1: fail
int try_half(int num) {
    int half = num / 2;

    if (half == 0) {
        return -1;
    }

    if (!members.count(half)) {
        return half;
    }
    else {
        return try_half(half);
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    REP(n,N){
        int num;
        cin >> num;
        q.push(num);
        members.insert(num);
    }
    
    while(1) {
        auto pop = *members.rbegin();
        auto after = try_half(pop);
        if (after == -1) break;
        else {
            members.erase(pop);
            members.insert(after);
        }
    }

    vector<int> ans(ALL(members));
    REP(i,SIZE(members)) {
        if (i == 0) cout << ans[i];
        else cout << " " << ans[i];
    }
    cout << endl;

    return 0;
}
