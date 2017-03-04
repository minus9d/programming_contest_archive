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
#define RALL(c) (c).rbegin(), (c).rend()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

class UnionFind
{
public:
    UnionFind() {};
    ~UnionFind() {};

    void Init(int num_entries) {
        num_entries_ = num_entries;
        par_.resize(num_entries_);
        rank_.resize(num_entries_, 0);
        for (int i = 0; i < num_entries_; ++i)
        {
            par_[i] = i;
        }
    }
    int Find(int x) {
        if (par_[x] == x)
        {
            return x;
        }
        else
        {
            return par_[x] = Find(par_[x]);
        }
    }
    void Unite(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;

        if (rank_[x] < rank_[y])
        {
            par_[x] = y;
        }
        else
        {
            par_[y] = x;
            if (rank_[x] == rank_[y])
            {
                rank_[x]++;
            }
        }
    }
    bool Same(int x, int y) {
        return Find(x) == Find(y);
    }

private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
};


int H, W, K;
vector<vector<int>> cells;
vector<vector<char>> used;
int dh[4] = { 0, 0, 1, -1 };
int dw[4] = { 1, -1, 0, 0 };


bool is_ok(int tl_h, int tl_w, int sz) {
    FOR(h, tl_h, tl_h + sz) {
        FOR(w, tl_w, tl_w + sz) {
            if (used[h][w]) return false;
        }
    }
    return true;
}

// pos: <h_idx, w_idx>
int get_score(pair<int, int>& pos) {
    return cells[pos.first][pos.second];
}

void set_used_flag(pair<int, int>& pos) {
    used[pos.first][pos.second] = 1;
}

char get_used_flag(pair<int, int>& pos) {
    return used[pos.first][pos.second];
}

bool still_connect(pair<int, pair<int, int>>& ans_cand, pair<int, pair<int, int>>& nei_cand, vector<pair<int, int>>& ans) {
    vector<pair<int, int>> ans2;
    for (auto& a : ans) {
        if (a == ans_cand.second) continue;
        ans2.pb(a);
    }
    ans2.pb(nei_cand.second);

    auto uf = UnionFind();
    uf.Init(8);
    REP(i, 7) {
        FOR(j, i + 1, 8) {
            auto p1 = ans2[i];
            auto p2 = ans2[j];
            if ((p1.first == p2.first && abs(p1.second - p2.second) == 1)
                || (p1.second == p2.second && abs(p1.first - p2.first) == 1))
            {
                uf.Unite(i, j);
            }
        }
    }

    FOR(j, 1, 8) {
        if (!uf.Same(0, j)) return false;
    }
    return true;
}

void refine(vector<pair<int, int>>& ans) {
    while(true) {
        vector<pair<int, pair<int, int>>> ans_score;
        for (auto a : ans) {
            ans_score.push_back(mp(get_score(a), a));
        }
        sort(ALL(ans));

        // 隣にあるブロックを列挙
        set<pair<int, int>> neigh;
        for (auto hw : ans) {
            REP(d, 4) {
                auto h2 = hw.first + dh[d];
                auto w2 = hw.second + dw[d];
                if (0 <= h2 && h2 <= H - 1 && 0 <= w2 && w2 <= W - 1 && !used[h2][w2]) {
                    neigh.insert(mp(h2, w2));
                }
            }
        }
        for (auto a : ans) {
            neigh.erase(a);
        }

        // 隣にあるブロックのスコア
        vector<pair<int, pair<int, int>>> nei_score;
        for (auto n : neigh) {
            nei_score.push_back(mp(get_score(n), n));
        }
        sort(RALL(nei_score));

        // 周囲の中で数値が大きいものの入れ替えを考える
        bool replaced = false;
        REP(i, SIZE(ans_score)) {
            REP(j, SIZE(nei_score)) {
                auto ans_cand = ans_score[i];
                auto nei_cand = nei_score[j];
                if (ans_cand.first < nei_cand.first && still_connect(ans_cand, nei_cand, ans)) {
                    ans.erase(std::remove(ALL(ans), ans_cand.second), ans.end());
                    ans.push_back(nei_cand.second);
                    replaced = true;
                    break;
                }
            }
            if (replaced) break;
        }
        if (!replaced) {
            break;
        }
    }

    // set used flag
    for (auto& a : ans) {
        set_used_flag(a);
    }

}


int main(void)
{
    cin.sync_with_stdio(false);
    cin >> H >> W >> K;
    cells.resize(H, vector<int>(W));
    used.resize(H, vector<char>(W));

    REP(h,H) {
        string s;
        cin >> s;
        REP(w,W) {
            cells[h][w] = s[w] - '0';
        }
    }

    // 3x3で数値が高いものを探す
    int sz = 3;
    vector<pair<ll, pair<int, int>>> ranking;
    REP(h, H-(sz-1)) {
        REP(w, W-(sz-1)) {
            ll score = 1;
            vector<int> nums;
            REP(j, sz) REP(i, sz) {
                nums.push_back(cells[h + j][w + i]);
            }
            sort(nums.rbegin(), nums.rend());
            REP(i, min(sz*sz, 8)) score *= nums[i];
            ranking.pb(mp(score, mp(h, w)));
        }
    }
    sort(ranking.rbegin(), ranking.rend());

    ll sum = 0;
    vector<vector<pair<int, int>>> answers;
    REP(i, SIZE(ranking)) {
    //REP(i, 10) {
        auto score = ranking[i].first;
        if (score == 0) break;
        auto tl_h = ranking[i].second.first;
        auto tl_w = ranking[i].second.second;
        //cout << "score:" << ranking[i].first << endl;
        sum += ranking[i].first;
        if (is_ok(tl_h, tl_w, sz)) {
            vector<pair<int, pair<int, int>>> nums;
            FOR(h, tl_h, tl_h + 3) {
                FOR(w, tl_w, tl_w + 3) {
                    if (cells[h][w] != 0) {
                        nums.push_back(mp(cells[h][w], mp(h, w)));
                    }
                }
            }
            sort(nums.rbegin(), nums.rend());

            vector<pair<int, int>> ans;
            REP(i, 8) {
                ans.pb(nums[i].second);
                if (used[nums[i].second.first][nums[i].second.second]) {
                    cout << "error!" << endl;
                    exit(1);
                }
            }

            refine(ans);

            answers.pb(ans);
        }
    }
    //cout << "sum:" << sum << endl;


    //// 3x3で区切っていく
    //int width = 3;
    //int height = 3;
    //int tl_w = 0;
    //int tl_h = 0;
    //while(tl_h + height <= H) {
    //    if (tl_w + width >= W) {
    //        tl_h += width;
    //        tl_w = 0;
    //        continue;
    //    }

    //    int nonzero = 0;
    //    vector<pair<int, pair<int, int>>> nums;
    //    FOR(h, tl_h, tl_h + height) {
    //        FOR(w, tl_w, tl_w + width) {
    //            if (cells[h][w] != 0) {
    //                nums.push_back(mp(cells[h][w], mp(h, w)));
    //                ++nonzero;
    //            }
    //        }
    //    }
    //    if (nonzero < 8) {
    //        tl_w += 1;
    //        continue;
    //    }
    //    else {
    //        tl_w += 3;

    //        // append
    //        sort(nums.rbegin(), nums.rend());
    //        vector<pair<int, int>> ans;
    //        REP(i, 8) {
    //            ans.pb(nums[i].second);
    //        }
    //        answers.pb(ans);
    //    }

    //}
    
    cout << SIZE(answers) << endl;
    for(auto& ans: answers) {
        for(auto& pos: ans) {
            printf("%d %d\n", pos.first+1, pos.second+1);
        }
    }

    return 0;
}
