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

vector<pair<ll, ll>> Cs;

void solve(ll X1, ll X2, bool& hasAns, vector<int>& group1, vector<int>& group2)
{
    ll cnt = 0;
    ll mx = 0;
    int idx = 0;
    bool ok = false;
    for(; idx < SIZE(Cs); ++idx) {
        auto c = Cs[idx].first;
        mx = c;
        ++cnt;
        group1.push_back(Cs[idx].second);
        if (mx * cnt >= X1) {
            ok = true;
            break;
        }
    }

    if (!ok) {
        hasAns = false;
        return;
    }

    ok = false;
    cnt = 0;
    ++idx;
    for (; idx < SIZE(Cs); ++idx) {
        auto c = Cs[idx].first;
        mx = c;
        ++cnt;
        group2.push_back(Cs[idx].second);
        if (mx * cnt >= X2) {
            hasAns = true;
            ok = true;
            break;
        }
    }

    if (!ok) {
        hasAns = false;
        return;
    }
}

void printAns(vector<int>& group1, vector<int>& group2) {
    cout << "Yes" << endl;
    cout << SIZE(group1) << " " << SIZE(group2) << endl;
    REP(i, SIZE(group1)) {
        cout << (i == 0 ? "" : " ");
        cout << (group1[i] + 1);
    }
    cout << endl;
    REP(i, SIZE(group2)) {
        cout << (i == 0 ? "" : " ");
        cout << (group2[i] + 1);
    }
    cout << endl;
}


int main(void)
{
    cin.sync_with_stdio(false);
    ll N, X1, X2;
    cin >> N >> X1 >> X2;

    Cs.resize(N);

    // <num, idx>
    REP(n, N) {
        ll c; cin >> c;
        Cs[n] = mp(c, n);
    }
    sort(ALL(Cs), greater<pair<ll, ll>>());

    bool hasAns = false;
    vector<int> group1;
    vector<int> group2;
    solve(X1, X2, hasAns, group1, group2);
    if (hasAns) {
        printAns(group1, group2);
        return 0;
    }

    group1.clear();
    group2.clear();

    solve(X2, X1, hasAns, group2, group1);
    if (hasAns) {
        printAns(group1, group2);
        return 0;
    }

    cout << "No" << endl;
    return 0;
}


