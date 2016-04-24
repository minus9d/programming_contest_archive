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

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    int num = 0;
    bool ok = true;
    REP(n,N) {
        string s;
        cin >> s;
        if (s == "A") {
            ++num;
        }
        else {
            if (num <= 0) {
                ok = false;
                break;
            }
            --num;
        }
    }
    if (num != 0) {
        ok = false;
    }

    cout << (ok ? "YES" : "NO") << endl;

    return 0;
}
