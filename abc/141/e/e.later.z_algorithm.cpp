// 解答PDFの想定解通り、Z-Algorithmで解答

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
#include <cstdint>

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

// 文字列が与えられた時、各 i について「SとS[i:]の最長共通接頭辞の長さ」をO(|S|)で構築
// e.g.
//   aaabaaaab
//   921034210
// https://snuke.hatenablog.com/entry/2014/12/03/214243
template <typename T>
vector<int> z_algorithm(T& s) {
    auto len = SIZE(s);
    vector<int> ret(len);
    ret[0] = len;
    int i = 1, j = 0;
    while (i < len) {
        while (i + j < len && s[j] == s[i+j]) ++j;
        ret[i] = j;
        if (j == 0) {++i; continue;}
        int k = 1;
        while (i + k < len && k + ret[k] < j) {ret[i+k] = ret[k]; ++k;}
        i += k; j -= k;
    }    
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    string S;
    cin >> S;

    int ans = 0;
    REP(n, N) {
        string substr = S.substr(n);
        auto z = z_algorithm(substr);
        REP(i, SIZE(substr)) {
            ans = max(ans, min(z[i], i));
        }
    }
    cout << ans << endl;

    return 0;
}
