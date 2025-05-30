#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <tuple>
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

int D, T;
vector<int> Cs(8);
vector<int> As(8);

int serve_pattern = 0;
bool can_serve(int target) {
    REP(i, 1<<8) {
        int s = 0;
        REP(j, 8) {
            if ((1 << j) & i) {
                s += As[j];
            }
        }
        if (s == target) {
            serve_pattern = i;
            return true;
        }
    }
    return false;
}

int count_bit(int pat) {
    int ans = 0;
    while(pat) {
        if (pat & 1) {
            ans += 1;
        }
        pat /= 2;
    }
    return ans;
}


int fill_idx = 0;
bool can_fill(void) {
    int min_diff = 1e9;
    bool ans = false;
    REP(i, 8) {
        int diff = Cs[i] - As[i];
        if (diff > 0) {
            ans = true;
            if (diff < min_diff) {
                fill_idx = i;
                min_diff = diff;
            }
        }
    }
    return ans;
}

int main(void)
{
    cin.sync_with_stdio(false);
    REP(time, 1000) {
        cin >> D >> T;
        REP(c, 8) cin >> Cs[c];
        REP(a, 8) cin >> As[a];

        // replace C
        auto sum_c = accumulate(ALL(Cs), 0);
        if (sum_c < 50) {
            auto smallest = min_element(ALL(Cs));
            auto idx = smallest - Cs.begin();
            cout << "change " << (idx + 1) << endl;
        }
        else if (can_serve(D)) {
            cout << "sell " << count_bit(serve_pattern);
            REP(j, 8) {
                if ((1 << j) & serve_pattern) {
                    cout << " " << (j + 1);
                }
            }
            cout << endl;
        }
        else if (can_fill()) {
            cout << "fill " << (fill_idx + 1) << endl;
        }
        else {
            cout << "pass" << endl;
        }
    }

    return 0;
}

