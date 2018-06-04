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
    int A, B, N;
    cin >> A >> B >> N;
    string X;
    cin >> X;

    for (auto ch: X) {
        if (ch == 'S') {
            A = max(0, A - 1);
        }
        else if (ch == 'C') {
            B = max(0, B - 1);
        }
        else {
            if (A > B) {
                --A;
            }
            else if (B > A) {
                --B;
            }
            else if (A > 0) {
                --A;
            }
        }
    }
    cout << A << endl;
    cout << B << endl;

    return 0;
}
