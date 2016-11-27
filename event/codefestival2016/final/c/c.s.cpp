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

class UnionFind
{
public:
    UnionFind(){};
    ~UnionFind(){};

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

set<int> get_intersect(const set<int>& s1, const set<int>& s2) {
    set<int> intersect;
    set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),
                     std::inserter(intersect,intersect.begin()));
    return intersect;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N, M;
    cin >> N >> M;

    vector<vector<int>> speaker_to_langs(N);
    vector<char> seen_langs(M);

    UnionFind uf;
    uf.Init(M);

    
    REP(n,N) {
        int k;
        cin >> k;
        vector<int> langs(k);
        REP(k1,k) {
            int l;
            cin >> l; --l;
            langs[k1] = l;
            seen_langs[l] = 1;
        }
        speaker_to_langs[n] = langs;

        REP(i,k-1){
            FOR(j,i+1,k){
                uf.Unite(langs[i], langs[j]);
            }
        }
    }

    set<int> common_lang;
    for(auto lang : speaker_to_langs[0]){
        common_lang.insert( uf.Find(lang) );
    }
    FOR(n,1,N){
        auto& langs = speaker_to_langs[n];
        set<int> langs_set;
        for(auto lang : langs) {
            langs_set.insert( uf.Find(lang) );
        }
        common_lang = get_intersect(common_lang, langs_set);
    }

    if (SIZE(common_lang) > 0) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}
