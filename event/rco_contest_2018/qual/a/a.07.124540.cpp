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
#include <chrono>


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

class UnionFind
{
public:
    UnionFind() {};
    ~UnionFind() {};
    void init(int num_entries) {
        num_entries_ = num_entries;
        par_.resize(num_entries_);
        rank_.resize(num_entries_, 0);
        REP(i, num_entries_) par_[i] = i;
    }
    int find(int x) {
        if (par_[x] == x) return x;
        else return par_[x] = find(par_[x]);
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (rank_[x] < rank_[y]) par_[x] = y;
        else {
            par_[y] = x;
            if (rank_[x] == rank_[y]) rank_[x]++;
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
};

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

typedef vector<string> Board;
int N, K, H, W, T;
vector<Board> boards;
vector<pair<int, int>> starts;

int dw[4] = { 0, 0, -1, 1 };
int dh[4] = { -1, 1, 0, 0 };
char signs[4] = { 'U', 'D', 'L', 'R' };

pair<int, vector<char>> greedy(vector<int>& choice) {

    int ret_score = 0;
    vector<char> ret_move(T);

    vector<Board> boards2;
    vector<pair<int, int>> locs;
    vector<char> dead(K);

    REP(k, K) {
        auto c = choice[k];
        boards2.push_back(boards[c]);
        locs.push_back(starts[c]);
    }

    REP(t, T) {
        // もっともスコアが上がる位置に移動
        int best_score = -1e9;
        int best_d = 0;

        REP(d, 4) {
            int score_up = 0;
            REP(k, K) {
                auto& board = boards2[k];
                auto& loc = locs[k];
                if (dead[k]) continue;

                int h2 = loc.first + dh[d];
                int w2 = loc.second + dw[d];
                auto cell = board[h2][w2];
                if (cell == 'o') {
                    ++score_up;
                }
                else if (cell == 'x') {
                    score_up -= 10000;
                }
            }
            if (score_up > best_score) {
                best_d = d;
                best_score = score_up;
            }
        }

        // 実際に移動
        ret_move[t] = best_d;

        REP(k, K) {
            auto& board = boards2[k];
            auto& loc = locs[k];
            if (dead[k]) continue;

            int h2 = loc.first + dh[best_d];
            int w2 = loc.second + dw[best_d];
            auto& cell = board[h2][w2];
            if (cell == 'o') {
                cell = '@';
                ++ret_score;
                loc = mp(h2, w2);
            }
            else if (cell == '@') {
                loc = mp(h2, w2);
            }
            else if (cell == 'x') {
                dead[k] = 1;
            }
        }
    }

    return mp(ret_score, ret_move);
}

int calc_score(vector<int>& choice) {
    return 777;
}




bool seen(vector<int>& choice) {
    static set<vector<int>> used;
    static vector<int> tmp(K);
    REP(k, K) tmp[k] = choice[k];
    if (used.count(tmp)) return true;
    used.insert(tmp);
    return false;
}

int to_idx(int h, int w) {
    return h * W + w;
}

int main(void)
{
    srand(777);
    Timer timer;
    timer.start();

    cin.sync_with_stdio(false);
    cin >> N >> K >> H >> W >> T;
    boards.resize(N);
    starts.resize(N);

    REP(n, N) {
        boards[n].resize(H);


        REP(h, H) {
            string line;
            cin >> line;

            int cand = line.find('@');
            if (cand != string::npos) {
                starts[n] = mp(h, cand);
            }
            boards[n][h] = line;
        }
    }

    // スタートから到達できる数
    vector<pair<int, int>> maxes(N);
    REP(n, N) {
        auto& board = boards[n];
        UnionFind uf;
        uf.init(H * W);
        REP(h, H) {
            REP(w, W) {
                if (w != -1 && (board[h][w] == 'o' || board[h][w] == '@') && (board[h][w + 1] == 'o' || board[h][w + 1] == '@')) {
                    uf.unite(to_idx(h, w), to_idx(h, w + 1));
                }
                if (h != -1 && (board[h][w] == 'o' || board[h][w] == '@') && (board[h + 1][w] == 'o' || board[h + 1][w] == '@')) {
                    uf.unite(to_idx(h, w), to_idx(h + 1, w));
                }
            }
        }
        auto target = uf.find(to_idx(starts[n].first, starts[n].second));
        int score = 0;
        REP(h, H) {
            REP(w, W) {
                if (uf.find(to_idx(h, w)) == target) {
                    ++score;
                }
            }
        }
        maxes[n] = mp(score, n);
        //cerr << score << endl;
    }

    sort(ALL(maxes));

    // 盤面の選び方
    vector<int> choice;
    REP(i, 95) {
        choice.pb(maxes[i].second);
    }
    //REP(i, N) choice[i] = i;

    int best_score = -1;
    vector<int> best_choice;
    vector<char> best_move;

    int try_num = 0;
    while (timer.milli() < 3900) {
        ++try_num;
        random_shuffle(ALL(choice));

        if (seen(choice)) continue;


        //static vector<char> move(T);
        //REP(t, T) {
        //    move[t] = rand() % 4;
        //    //move[t] = 0;
        //}
        //auto score = calc_score(choice, move);

        auto score_and_move = greedy(choice);
        auto score = score_and_move.first;
        auto move = score_and_move.second;

        //cerr << "score: " << score << endl;
        if (score > best_score) {
            best_score = score;
            best_choice = choice;
            best_move = move;
        }
    }

    REP(k, K) {
        if (k != 0) cout << " ";
        cout << (best_choice[k]);
    }
    cout << endl;
    for (auto m : best_move) {
        cout << signs[m];
    }
    cout << endl;

    cerr << "try_num: " << try_num << endl;
    cerr << "best score:" << best_score << endl;

    return 0;
}
