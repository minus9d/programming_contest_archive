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
    int N;
    cin >> N;
    int MOD = 1e9 + 7;

    vector<char> chars{'A', 'C', 'G', 'T'};
    map<string, int> m;
    REP(n, N) {
        if (n == 0) {
            m["A"] = 1;
            m["G"] = 1;
            m["C"] = 1;
            m["T"] = 1;
        } else {
            map<string, int> new_m;
            for(auto kv: m) {
                auto str = kv.first;
                auto num = kv.second;

                for (auto ch: chars) {
                    auto str2 = str + ch;

                    if (str2 == "AGC" || str2 == "GAC" || str2 == "ACG") {
                        continue;
                    }
                    if (str2 == "AGGC" || str2 == "ACGC" || str2 == "ATGC"
                        || str2 == "AGAC" || str2 == "AGTC") {
                        continue;
                    }

                    string str3;
                    if (SIZE(str2) == 4) {
                        FOR(i, 1, SIZE(str2)) str3 += str2[i];
                    } else {
                        str3 = str2;
                    }
                    
                    if (str3 == "AGC" || str3 == "GAC" || str3 == "ACG") {
                        continue;
                    }

                    new_m[str3] += num;
                    new_m[str3] %= MOD;
                }
            }
            m = new_m;
            // cout << "===" << endl;
            // for(auto kv: m) cout << kv.first << ": " << kv.second << endl;
        }
    }
    ll ans = 0;
    for(auto kv: m) {
        ans += kv.second;
        ans %= MOD;
    }
    cout << ans << endl;

    return 0;
}
