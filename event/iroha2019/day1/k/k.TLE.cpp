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

const ll MOD = int(1e9) + 7;

int get_len(ll a) {
    int ans = 0;
    while (a >= 10) {
        ans++;
        a /= 10;
    }
    return ans + 1;
}

ll mypow(ll base, ll n) {
    ll ret = 1;
    REP(i, n) {
        ret *= base;
        ret %= MOD;
    }
    return ret;
}

int main() {
    ll N;
    cin >> N;
    
    vector<ll> Ms(N);
    vector<vector<ll>> As_list(N);

    REP(n, N) {
        cin >> Ms[n];
        As_list[n].resize(Ms[n]);
        REP(i, Ms[n]) {
            ll a;
            cin >> a;
            As_list[n][i] = a;
        }
    }
    // for(auto m: Ms) cout << m << ","; cout << endl;
    // for(auto As: As_list) {
    //     cout << "  "; for(auto a: As) cout << a << ","; cout << endl;
    // }

    reverse(ALL(Ms));
    reverse(ALL(As_list));

    map<ll, ll> digit2sum;
    map<ll, ll> digit2comb;

    REP(i, N) {
        auto M = Ms[i];
        auto As = As_list[i];
        
        if (i == 0) {
            for(auto a: As) {
                auto len = get_len(a);
                digit2sum[len] += a;
                digit2comb[len] += 1;
            }
        } else {
            map<ll, ll> nextd2s;
            map<ll, ll> nextd2c;
            for(auto a: As) {
                for (auto kv: digit2sum) {
                    auto d = kv.first;
                    auto s = kv.second;
                    auto new_d = get_len(a) + d;

                    auto tmp = a * mypow(10, d);
                    tmp %= MOD;
                    tmp *= digit2comb[d];
                    tmp %= MOD;
                    tmp += s;
                    tmp %= MOD;

                    auto new_s = tmp;
                    // cout << "d, s, a, new_d, new_s, comb = "
                    //      << d << " "
                    //      << s << " "
                    //      << a << " "
                    //      << new_d << " "
                    //      << new_s << " "
                    //      << digit2comb[d] << endl;
                    nextd2s[new_d] += new_s;
                    nextd2s[new_d] %= MOD;
                    nextd2c[new_d] += digit2comb[d];
                    nextd2c[new_d] %= MOD;
                }
            }
            digit2sum = nextd2s;
            digit2comb = nextd2c;
        }
    }
    
    // cout << " ==== " << endl;
    // for(auto kv: digit2sum) {
    //     cout << kv.first << ":" << kv.second << endl;
    // }

    ll ans = 0;
    for (auto kv: digit2sum) {
        auto digit = kv.first;
        auto s = kv.second;
        ans += s;
        ans %= MOD;
    }
    cout << ans << endl;
    
    return 0;
}
