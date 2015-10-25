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
    int N,M;
    cin >> N >> M;

    map<int,int> table;
    REP(n,N) {
        int a;
        cin >> a;
        ++table[a];
    }

    int need = (N + 2) / 2;
    for(auto& p: table) {
        if (p.second >= need) {
            cout << p.first << endl;
            return 0;
        }
    } 

    cout << "?" << endl;

    return 0;
}
