// 各aに対して、「かけたときにKの倍数となる最小の整数 need」を計算
// needの倍数である数がAのなかにいくつあるかを数える

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

map<long long, int> getFactorsMap(long long N){
    map<long long, int> ret;
    for (long long p=2; p*p <= N; p++) {
        while (N % p == 0) {
            N /= p;	
            ret[p]++;
        }
    }
    if (N != 1) ret[N]++;
    return ret;
}

int mypow(int a, int b) {
    int ret = 1;
    while (b > 0) {
        ret *= a;
        --b;
    }
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    vector<int> As(N);
    map<int, int> new_As;
    REP(n,N) cin >> As[n];

    auto k_factors = getFactorsMap(K);
    
    map<int, int> needs;
    set<int> needs_set;
    int dummy = 0;
    REP(i, N) {
        auto a = As[i];

        //auto a_factors = getFactorsMap(a);
        map<long long, int> a_factors;

        int new_a = 1;
        for (auto kv : k_factors) {
            auto k_f = kv.first;
            auto k_v = kv.second;
            int n = 1;
            while (k_v > 0) {
                n *= k_f;
                if (a % n != 0) {
                    n /= k_f;
                    break;
                }
                else {
                    a_factors[k_f] += 1;
                }
                --k_v;
            }
            new_a *= n;
        }
        new_As[new_a]++;

        //printf("a, new_a = %d, %d\n", a, new_a);

        //int n = 1;
        //for (auto kv: k_factors) {
        //    auto k_f = kv.first;
        //    auto k_v = kv.second;
        //    n *= mypow(k_f, k_v - a_factors[k_f]);
        //}
        needs[new_a] = K / new_a;
        needs_set.insert(K );
    }

    map<int, int> multiples;
    for (auto need : needs_set) {
        for (auto kv : new_As) {
            int a = kv.first;
            int a_count = kv.second;
            if (a % need == 0) {
                multiples[need] += a_count;
            }
        }
    }

    ll ans = 0;
    for (auto kv : new_As) {
        int a = kv.first;
        int a_count = kv.second;
        auto need = needs[a];
        auto cand_num = multiples[need];
        if (a % need == 0) {
            --cand_num;
        }
        ans += cand_num * a_count;
    }
    cout << (ans / 2) << endl;
    
    return 0;
}
