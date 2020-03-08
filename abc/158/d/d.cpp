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

int main(void)
{
    cin.sync_with_stdio(false);
    string S;
    cin >> S;
    int Q;
    cin >> Q;

    string head;
    string tail;
    bool flip = false;
    REP(q, Q) {
        int type;
        cin >> type;
        if (type == 1) flip = !flip;
        else {
            int f;
            char c;
            cin >> f >> c;
            if (f == 1) {
                if (flip) tail += c;
                else head += c;
            } else {
                if (flip) head += c;
                else tail += c;
            }
        }
    }

    reverse(ALL(head));
    string ans = head + S + tail;
    if (flip) {
        reverse(ALL(ans));
    }
    cout << ans << endl;

    return 0;
}
