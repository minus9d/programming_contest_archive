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
#include <stack>
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

int N;

bool is_valid(vector<set<int>>& edges, vector<int>& perm)
{
    // 訪問済みの頂点を管理するスタック
    stack<int> s;
    bool fail = false;

    auto curr_v = perm[0];

    map<int, set<int>> seen; // 一度使った辺を記録

    FOR(i, 1, SIZE(perm))
    {
        auto next_v = perm[i];
        while(1) {

            // 今いる頂点から次の頂点へ行ける場合
            if (edges[curr_v].count( next_v ) && !seen[curr_v].count( next_v )){
                seen[curr_v].insert( next_v );
                s.push( curr_v );
                curr_v = next_v;
                break;
            }

            // 次の頂点へ行けない場合は、一つ戻ってリトライ
            if (s.empty()) {
                fail = true;
                break;
            }

            curr_v = s.top(); s.pop();
        }
    }

    return !fail;
}


int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        int N, M;
        cin >> N >> M;
        vector<string> strs(N);
        REP(n,N){
            cin >> strs[n];
        }

        vector< set<int> > edges(N);

        REP(m,M){
            int j, k;
            cin >> j >> k;
            --j; --k;
            edges[j].insert(k);
            edges[k].insert(j);
        }
        
        vector<int> perm(N);
        REP(i, N){
            perm[i] = i;
        }

        string ret = "";
        do {
            if (is_valid(edges, perm)){
                string str = "";
                REP(i, N){
                    str += strs[ perm[i] ];
                }

                if (ret == "") ret = str;
                else {
                    ret = min(ret, str);
                }
            }
        } while ( next_permutation(ALL(perm)) );

        cout << "Case #" << (test+1) << ": " << ret << endl;
    }

    return 0;
}
