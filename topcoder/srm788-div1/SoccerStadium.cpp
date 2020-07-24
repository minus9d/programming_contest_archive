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
#include <cstring>
#include <fstream>

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

using namespace std;

int dh[] = {0, 0, 1, -1};
int dw[] = {1, -1, 0, 0};

class UnionFind
{
public:
    UnionFind() {};
    ~UnionFind() {};
    void init(int num_entries) {
        num_entries_ = num_entries;
        par_.resize(num_entries_);
        rank_.resize(num_entries_, 0);
        member_num_.resize(num_entries_, 1);
        REP(i, num_entries_) {
            par_[i] = i;
        }
    }
    int find(int x) {
        if (par_[x] == x) return x;
        else return par_[x] = find(par_[x]);
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (rank_[x] < rank_[y]) {
            par_[x] = y;
            member_num_[y] += member_num_[x];
            member_num_[x] = 0;
        }
        else {
            par_[y] = x;
            member_num_[x] += member_num_[y];
            member_num_[y] = 0;
            if (rank_[x] == rank_[y]) rank_[x]++;
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) {
        return member_num_[this->find(x)];
    }
private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
    std::vector<int> member_num_;
};



class SoccerStadium {
    public:

    bool not_good(vector<string>& placement, int H, int W, int h, int w) {
        assert (placement[h][w] == '+');
        int num = 0;
        REP(d, 4) {
            auto h2 = h + dh[d];
            auto w2 = w + dw[d];
            num += (placement[h2][w2] != '.');
        }
        if (num == 1) return true;
        if (num == 3 || num == 4) return false;
        if ((placement[h + 1][w] == '.' && placement[h - 1][w] == '.')
            || (placement[h][w + 1] == '.' && placement[h][w - 1] == '.')) return false;
        else return true;
    }
    void remove(vector<string>& placement, int H, int W, int h, int w) {
        assert (placement[h][w] == '+');
        REP(d, 4) {
            auto h2 = h + dh[d];
            auto w2 = w + dw[d];
            placement[h2][w2] = '.';
        }
    }

    int maximumGames(int H_, int W_, vector<string> placement) {

        // (h, w)
        set<pair<int, int>> next;
        int H = H_ * 2 + 1;
        int W = W_ * 2 + 1;

        for(int h = 2; h < H - 2; h += 2) {
            for(int w = 2; w < W - 2; w += 2) {
                if (not_good(placement, H, W, h, w)) {
                    remove(placement, H, W, h, w);
                    
                    REP(d, 4) {
                        auto h2 = h + dh[d] * 2;
                        auto w2 = w + dw[d] * 2;
                        if (2 <= h2 && h2 <= H - 3 && 2 <= w2 && w2 <= W - 3) {
                            next.insert(mp(h2, w2));
                        }
                    }
                }
            }
        }

        while (!next.empty()) {
            set<pair<int, int>> next_next;
            for(auto n: next) {
                auto h = n.first;
                auto w = n.second;

                if (not_good(placement, H, W, h, w)) {
                    remove(placement, H, W, h, w);
                    REP(d, 4) {
                        auto h2 = h + dh[d] * 2;
                        auto w2 = w + dw[d] * 2;
                        if (2 <= h2 && h2 <= H - 3 && 2 <= w2 && w2 <= W - 3) {
                            next_next.insert(mp(h2, w2));
                        }
                    }
                }
            }
            next = next_next;
        }

        UnionFind uf;
        uf.init(H_ * W_);
        REP(h_, H_) {
            REP(w_, W_) {
                auto h = 2 * h_ + 1;
                auto w = 2 * w_ + 1;
                auto idx = h_ * W_ + w_;

                assert(placement[h][w] == '.');
                if (placement[h][w + 1] == '.') uf.unite(idx, idx + 1);
                if (placement[h + 1][w] == '.') uf.unite(idx, idx + W_);
            }
        }
        set<int> seen;
        REP(idx, H_* W_) seen.insert(uf.find(idx));
        return SIZE(seen);

    }
};

// CUT begin
ifstream data2("SoccerStadium.sample");

string next_line() {
    string s;
    getline(data2, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int H, int W, vector<string> placement, int __expected) {
    time_t startClock = clock();
    SoccerStadium *instance = new SoccerStadium();
    int __result = instance->maximumGames(H, W, placement);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        int H;
        from_stream(H);
        int W;
        from_stream(W);
        vector<string> placement;
        from_stream(placement);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(H, W, placement, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1595589795;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "SoccerStadium (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
