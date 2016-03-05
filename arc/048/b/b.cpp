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

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    vector<pair<int,int>> in(N);

    map<int,array<int,3>> table;
    REP(n,N) {
        int r, h;
        cin >> r >> h;
        --h;
        in[n] = mp(r,h);
        ++table[r][h];
    }

    map<int,int> below;
    map<int,int> upper;
    int num = 0;
    for (auto& e: table) {
        auto& r = e.first;
        below[r] = num;
        auto sum = e.second[0] + e.second[1] + e.second[2];
        num += sum;
        upper[r] = N - num;
    }

    for (auto& e: in) {
        auto rate = e.first;
        auto hand = e.second;

        auto win = below[rate] + table[rate][(hand + 1) % 3];
        auto lose = upper[rate] + table[rate][(hand + 2) % 3];
        auto draw = table[rate][hand] - 1;
        printf("%d %d %d\n", win, lose, draw);
    }
    

    return 0;
}
