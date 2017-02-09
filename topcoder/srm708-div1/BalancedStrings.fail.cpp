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


#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;


int ALPHA = 26;
class BalancedStrings {
public:
    void add(vector <string>& res, int len, int& num) {
        int offset = 0;
        REP(n, min(ALPHA, num)) {
            string s;
            REP(i, len) {
                s += 'a' + ((offset + i) % ALPHA);
            }
            offset += 1;
            res.pb(s);
        }
        num -= ALPHA;
        num = max(0, num);
    }

    vector <string> findAny(int N) {
        vector <string> res;
        add(res, 1, N);
        add(res, 2, N);
        add(res, 4, N);
        add(res, 8, N);
        return res;
    }

  

};




// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
