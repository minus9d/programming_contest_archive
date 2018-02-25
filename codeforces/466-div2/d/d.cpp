#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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

vector<int> simulate(int N, vector<int>& A, int l, int r) {
    vector<int> B(N);

    FOR(i, 5, N-1) {
        if (A[i] > r && A[i-1] > r && A[i-2] > r && A[i-3] > r && A[i-4] > r &&
            B[i-1] == 1 && B[i-2] == 1 && B[i-3] == 1 && B[i-4] == 1) {
            B[i] = 1;
        }
        else if (A[i] < l && A[i-1] < l && A[i-2] < l && A[i-3] < l && A[i-4] < l &&
                 B[i-1] == 0 && B[i-2] == 0 && B[i-3] == 0 && B[i-4] == 0) {
            B[i] = 0;
        }
        else {
            B[i] = B[i-1];
        }
    }
    return B;
}

pair<int,int> solve(int N, vector<int>& A, vector<int>& B)
{
    int l = -1e9;
    int r = 1e9;
    int cnt0 = 0;
    int cnt1 = 0;
    REP(n, N) {
        auto b = B[n];
        if (b == 0) {
            if (cnt0 == 0 && cnt1 >= 4) {
                REP(i, 5) {
                    r = min(r, A[n - i] - 1);
                }
            }
            ++cnt0;
            cnt1 = 0;
        }
        else {
            if (cnt1 == 0 && cnt0 >= 4) {
                REP(i, 5) {
                    l = max(l, A[n - i] + 1);
                }
            }
            ++cnt1;
            cnt0 = 0;
        }
        // printf("cnt0, cnt1 = %d, %d\n", cnt0, cnt1);
    }

    return mp(l, r);
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> A(N);
    REP(n,N) cin >> A[n];
    string Bstr;
    cin >> Bstr;
    vector<int> B(N);
    REP(n,N) {
        B[n] = Bstr[n] - '0';
    }

    auto ans = solve(N, A, B);

    // auto B2 = simulate(N, A, ans.first, ans.second);
    // cout << " B2:" << endl;
    // cout << "B len:" << SIZE(B2) << endl;
    // for(auto b : B2) cout << (int)b << ",";
    // cout << endl;

    cout << ans.first << " " << ans.second << endl;

    return 0;
}
