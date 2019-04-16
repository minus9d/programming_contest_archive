#include <algorithm>
#include <cassert>
#include <chrono>
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

int dh[] = {0, 0, 1, -1};
int dw[] = {1, -1, 0, 0};

int calc_score(vector<string>& pattern, vector<vector<int>>& cells, int H, int W) {
    int score = 0;
    REP(h, H) {
        REP(w, W) {
            score += (pattern[h][w] == '#') * cells[h][w];
        }
    }
    return score;
}

struct Timer {
    std::chrono::time_point<std::chrono::system_clock> m_start;
    void start() {
        m_start = std::chrono::system_clock::now();
    }
    ll milli() {
        auto now = std::chrono::system_clock::now();
        auto diff = now - m_start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    }
};

int main(void)
{
    cin.sync_with_stdio(false);
    
    Timer timer;
    timer.start();

    int H, W;
    cin >> H >> W;
    vector<vector<int>> cells(H, vector<int>(W));
    REP(h, H) REP(w, W) cin >> cells[h][w];

    vector<string> best_pattern;
    int best_score = -2;
    while(true) {
        vector<string> pattern(H);
        vector<char> line1(W, '.');
        string line2(ALL(line1));
        REP(h, H) pattern[h] = line2;
        int h = rand() % (min(H, 5));
        int w = rand() % (min(W, 5));
        pattern[h][w] = '#';

        int n = 1;
        int prev_n = 1;
        REP(rep, 1000) {
            REP(h, H) {
                REP(w, W) {
                    if (pattern[h][w] == '#') continue;
                    int adj = 0;
                    REP(d, 4) {
                        auto h2 = h + dh[d];
                        auto w2 = w + dw[d];
                        if (h2 < 0 || h2 >= H || w < 0 || w >= W) {
                            continue;
                        }
                        adj += pattern[h2][w2] == '#';
                    }
                    if (adj == 1) {
                        if (cells[h][w] >= 7) {
                            if (rand() % 100 < 99) {
                                pattern[h][w] = '#';
                                ++n;
                            }
                        }
                        else if (cells[h][w] >= 3) {
                            if (rand() % 100 < 60) {
                                pattern[h][w] = '#';
                                ++n;
                            }
                        }
                        else {
                            if (rand() % 100 < 5) {
                                pattern[h][w] = '#';
                                ++n;
                            }
                        }
                    }
                }
            }
            if (prev_n == n) {
                // cerr << rep << endl;
                break;
            }
            prev_n = n;
        }
        int score = calc_score(pattern, cells, H, W);
        if (score > best_score) {
            best_score = score;
            best_pattern = pattern;
        }
        if (timer.milli() > 2700) break;
    }

    cerr << best_score << endl;
    REP(h, H) {
        cout << best_pattern[h] << endl;
    }

    return 0;
}
