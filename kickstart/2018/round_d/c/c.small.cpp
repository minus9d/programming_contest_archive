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

int get_sum(vector<vector<int>>& intg, int r, int c) {
    if (r < 0 || c < 0) return 0;
    return intg[r][c];
}

ll getGCDSimple(ll a, ll b)
{
    if (b == 0) return a;
    return getGCDSimple(b, a % b);
}

void solve() {
    int R, C, W;
    cin >> R >> C >> W;
    vector<vector<char>> cells(R, vector<char>(C));
    REP(r, R) REP(c, C) cin >> cells[r][c];
    map<string, int> words;
    REP(w, W) {
        string s;
        cin >> s;
        words[s]++;
    }

    vector<vector<int>> intg(R, vector<int>(C));
    REP(r, R) {
        vector<int> tmp(C);
        REP(c, C) {
            auto cnt = words[string(1, cells[r][c])];
            tmp[c] = cnt;
            if (c != 0) tmp[c] += tmp[c-1];
        }
        if (r == 0) {
            REP(c, C) {
                intg[r][c] = tmp[c];
            }
        }
        else {
            REP(c, C) {
                intg[r][c] = tmp[c] + intg[r-1][c];
            }
        }
    }

    int best_nmr = 0;
    int best_dnm = 0;
    int best_cnt = 0;
    bool is_first = true;
    REP(r1, R) {
        FOR(r2, r1, R) {
            REP(c1, C) {
                FOR(c2, c1, C) {
                    int nmr
                        = get_sum(intg, r2, c2)
                        - get_sum(intg, r2, c1-1)
                        - get_sum(intg, r1-1, c2)
                        + get_sum(intg, r1-1, c1-1);
                    nmr *= 4;
                    int dnm = (r2 - r1 + 1) + (c2 - c1 + 1);
                    // cout << "nmr, dnm = " << nmr << ", " << dnm << endl;

                    // if (nmr == 0) continue;
                    if (is_first || (best_nmr * dnm < best_dnm * nmr)) { 
                        best_nmr = nmr;
                        best_dnm = dnm;
                        best_cnt = 1;
                        is_first = false;
                    }
                    else if (best_nmr * dnm == best_dnm * nmr) {
                        ++best_cnt;
                    }
                }
            }
        }
    }
    if (best_nmr == 0) {
        cout << "0/1 " << best_cnt;
    }
    else {
        auto gcd = getGCDSimple(best_nmr, best_dnm);
        auto n = best_nmr / gcd;
        auto d = best_dnm / gcd;
        cout << n << "/" << d << " " << best_cnt;
        
    }
    
    
}

int main(void)
{
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, T) {
        cout << "Case #" << (t+1) << ": ";
        solve();
        cout << endl;
    }
    return 0;
}
