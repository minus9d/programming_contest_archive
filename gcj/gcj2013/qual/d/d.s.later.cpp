#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())
#define pb push_back
#define mp make_pair

struct data {
    vector<int> keys_i_have;
    ull opened_chests; // 1がopened
    vector<int> opened_order;
    bool operator<(const data& right) const {
        return opened_order.size() == right.opened_order.size() ?
            opened_order > right.opened_order :
            opened_order.size() > right.opened_order.size();
    }
};


void print_vector( vector<int> &v ) {
    for(int i = 0; i < v.size(); ++i){
        // cerr << v[i] << ", ";
    }
    // cerr << endl;
}

void print_data(data &d, int N){
    // cerr << "-----" << endl;
    // cerr << "keys: ";
    print_vector( d.keys_i_have );
    // cerr << "chests: ";
    for(int i = 0; i < N; ++i){
        // cerr << (bool)(d.opened_chests & (1 << i)) << ", ";
    }
    // cerr << endl;
    // cerr << "order: ";
    print_vector( d.opened_order );
    // cerr << "-----" << endl;
}

bool canOpen(int key, int c, vector<int> &needed_keys){
    return (key == needed_keys[c]);
}




vector<int> dfs(vector<int>& needed_keys,
                vector<vector<int> >& inside_keys,
                int N,
                map< ull, char >& seen,
                data& d
    )
{
    print_data(d, N);


    // all chests are opened
    // cerr << "order_size = " << d.opened_order.size() << ", N = " << N << endl;
    

    // 途中で同じ状態が出てきた場合→終了
    if (seen.count( d.opened_chests ) != 0){
        // cerr << "skip." << endl;
        return vector<int>();
    }
    seen[ d.opened_chests ] = 1;

    // キーがひとつもない場合→終了
    if (d.keys_i_have.size() == 0){
        // cerr << "no key. quit." << endl;
        return vector<int>();
    }
    
    // 開けられる棚を一つずつ開ける
    for(int c = 0; c < N; ++c){

        // まだ開けていない
        if (!(d.opened_chests & (1 << c))){

            // 棚を開けるのに必要な鍵
            int key = needed_keys[c];
                    
            // 手持ちの鍵であけることができるかどうか調べる
            int key_index = -1;
            for(int k = 0; k < d.keys_i_have.size(); ++k){
                if (d.keys_i_have[k] == key){
                    key_index = k;
                    break;
                }
            }

            //　もし開けることができるなら
            if ( key_index != -1 ){
                // cerr << "i can open chest %d." << endl;
                
                vector<int> keys_i_have_refresh = d.keys_i_have;
                keys_i_have_refresh.erase( keys_i_have_refresh.begin() + key_index );

                data next = d;
                next.keys_i_have = keys_i_have_refresh;
                
                // 棚が空いた
                next.opened_chests |= (1 << c);
                // 棚が空いたことにより鍵が増える
                for(int k2 = 0; k2 < inside_keys[c].size(); ++k2){
                    next.keys_i_have.push_back( inside_keys[c][k2] );
                }
                // 棚の順番を記録
                next.opened_order.push_back( c );


                // end?
                if (next.opened_order.size() == N){
                    // cerr << "done!" << endl;
                    vector<int> ret;
                    ret.push_back( c );
                    return ret;
                }
                else{
                    vector<int> dfs_ret = dfs(needed_keys,
                                              inside_keys,
                                              N,
                                              seen,
                                              next);
                    //// cerr << "dfs_ret = " << endl;
                    //print_vector( dfs_ret );
                    //// cerr << "d.opned_order = " << endl;
                    //print_vector( d.opened_order );

                
                    if (dfs_ret.size() != 0){
                        vector<int> ret;
                        ret.push_back(c);
                        ret.insert(ret.end(), dfs_ret.begin(), dfs_ret.end());
                        // cerr << "i can open the remain chests!" << endl;
                        return ret;
                    }
                    else{
                        // cerr << "i cannot open the remain chests.." << endl;
                    }
                }
            }
        }
    }
    return vector<int>();
}

int main(void)
{
    int T;
    cin >> T;

    for(int t = 0; t < T; ++t){
        int K, N;
        cin >> K >> N;
        vector<int> keys_i_have(K);
        for(int k = 0; k < K; ++k){
            cin >> keys_i_have[k];
            --keys_i_have[k];
        }
        vector<int> needed_keys(N);
        vector<vector<int> > inside_keys(N);
        for(int n = 0; n < N; ++n){
            cin >> needed_keys[n];
            --needed_keys[n];
            int inside_key_num;
            cin >> inside_key_num;
            inside_keys[n].resize(inside_key_num);
            for(int i = 0; i < inside_key_num; ++i){
                cin >> inside_keys[n][i];
                --inside_keys[n][i];
            }
        }

        
        // 状態は、持っている鍵と、あけた箱
        priority_queue<data> q;
        data ini;
        ini.keys_i_have = keys_i_have;
        ini.opened_chests = 0u;
        q.push(ini);
        map< ull, char > seen;

        vector<int>ans = dfs(needed_keys, inside_keys, N, seen, ini);

        if (!ans.size()){
            cout << "Case #" << (t+1) << ": IMPOSSIBLE" << endl;
        }
        else{
            cout << "Case #" << (t+1) << ": ";
            FOREACH(i, ans){
                cout << (*i+1) << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
