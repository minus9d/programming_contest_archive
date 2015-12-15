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

void solve(std::string nums) {
    set<string> seen;
    int len = SIZE(nums);

    string ret = nums;
    vector<char> fixed(len);

    fixed[0] = 1;
    fixed[len-1] = 1;
    
    FOR(i,1,len-1) {
        // 00 or 11
        if (nums[i] == nums[i-1] || nums[i] == nums[i+1]) {
            ret[i] = nums[i];
            fixed[i] = 1;
        }
    }

    vector<int> dist_to_fixed_left(len);
    vector<int> dist_to_fixed_right(len);
    int dist = 0;
    REP(i,len) {
        if (fixed[i]) dist = 0;
        else ++dist;
        dist_to_fixed_left[i] = dist;
    }
    for(int i = len-1; i >= 0; --i) {
        if (fixed[i]) dist = 0;
        else ++dist;
        dist_to_fixed_right[i] = dist;
        
    }

    REP(i,len) {
        if (fixed[i]) ret[i] = nums[i];
        else {
            if (dist_to_fixed_left[i] < dist_to_fixed_right[i]) {
                ret[i] = nums[i - dist_to_fixed_left[i]];
            }
            else {
                ret[i] = nums[i + dist_to_fixed_right[i]];
            }
        }
    }

    // continuous fix
    int longest = 0;
    int now = 0;
    REP(i,len) {
        if (fixed[i]) {
            now = 0;
        }
        else {
            ++now;
            longest = max(longest,now);
        }
    }
    cout << (longest + 1) / 2 << endl;

    REP(i,len) {
        if (i == 0) cout << ret[i];
        else cout << " " << ret[i];
    }
    cout << endl;
}

int main(void)
{
    // solve("01001010101011011001100001010101010101010101011101101011101010110");
    // solve("01010101010101010101010101010101010101010");  // all zero
    // solve("0101010101010101010101010101010101010101");  // all zero
    // string s = "";
    // REP(n,250000) s += "01";
    // solve(s);

    cin.sync_with_stdio(false);
    int N;
    cin >> N;

    string nums;
    REP(n,N) {
        char ch;
        cin >> ch;
        nums += ch;
    }

    solve(nums);

    return 0;
}
