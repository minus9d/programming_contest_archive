#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

void debug_links(map< int, set<int> > &links)
{
    for ( auto l : links ) {
        printf(" %d: ", l.first);
        for ( auto dest : l.second ){
            printf(" %d, ", dest);
        }
        printf("\n");
    }
}

map< pair<int, map< int, set<int> > >, int > seen;



//bool isok(vector< pair<int, int> > &pairs)
bool isok(map< int, set<int> > &links, int remain)
{
    if (seen.count( mp(remain, links) ) ) return seen[ mp(remain, links) ];
    
    // debug_links(links);
    
    if (links.size() == 0) return true;
    if (links.size() == 1){
        if (links.begin()->second.size() == 0)
            return true;
        else
            return false;
    }
    if (links.size() % 2 == 0) return false;

    map<int, int> cnt;
    for ( auto l : links ) {
        cnt[l.second.size()]++;
    }

    if ( cnt[1] == (remain + 1) / 2
         && cnt[2] == 1
         && cnt[3] == (remain + 1) / 2 - 2)
    {
        return true;
    }

    return false;
}

// void print_pairs(vector< pair<int, int> > &pairs)
// {
//     printf("pair: \n");
//     for ( auto p : pairs) {
//         printf("  %d <-> %d\n", p.first, p.second);
//     }
// }

int solve(map< int, set<int> > &links, int N, int remain)
//int solve(vector< pair<int, int> > &pairs, int N)
{
    // if (pairs.size() >= 4){
    //     printf("=======\n");
    // }

    // print_pairs(pairs);
    
    if (isok(links, remain)) {
        return 0;
    }

    int mn = 1000;
    FOR(i, 1, N+1) {

        // delete i
        map< int, set<int> > new_links;
        for ( auto l : links ) {
            if (l.first == i) continue;
            new_links[l.first] = set<int>();
            for ( auto z : l.second ) {
                if (z == i) continue;
                new_links[l.first].insert( z );
            }
        }

        if (new_links.size() == links.size()) continue;

        int tmp = solve(new_links, N, remain-1) + 1;
        
        mn = min(mn, tmp);
    }

    return mn;
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        int N;
        cin >> N;
        map< int, set<int> > links;
        vector< pair<int, int> > pairs;
        REP(n, N-1){
            int i, j;
            cin >> i >> j;
            links[i].insert(j);
            links[j].insert(i);
            pairs.pb( mp(i,j) );
        }

        int ret = solve(links, N, N);
        
        // REP(i, (1<<N)){
        //     map< int, set<int> > links_cp = links;
        //     REP(j, N){
        //         if (i & (1 << j)){
        //             delete_link(links_cp, j);
                    
        //         }
        //     }
        // }

        cout << "Case #" << (test+1) << ": " << ret << endl;
    }

    return 0;
}
