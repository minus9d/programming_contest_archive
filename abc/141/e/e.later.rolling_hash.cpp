// https://betrue12.hateblo.jp/entry/2019/09/16/013915
// を参考に、ローリングハッシュで解答

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
#include <cstdint>

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

// ローリングハッシュを生成するクラス
// string strに対してはSingleRollingHash<string>(str),
// vector<int> vに対してはSingleRollingHash<vector<int>>(v) などと使う
// ハッシュ値の衝突を避けるため、MultiRollingHashの使用を推奨
// https://betrue12.hateblo.jp/entry/2019/09/16/013915
template <typename T>
class SingleRollingHash{
private:
    vector<int64_t> m_hash;
    vector<int64_t> m_base_pow;
    int64_t m_base, m_mod;
    const int64_t DEFAULT_BASE = 1009, DEFAULT_MOD = 1e9+7;
    void initialize(T& S){
        m_hash.resize(SIZE(S) + 1);
        m_base_pow.resize(SIZE(S) + 1);
        m_hash[0] = 0;
        m_base_pow[0] = 1;
        FOR(i, 1, SIZE(S) + 1) {
            m_hash[i] = (m_hash[i - 1] * m_base + S[i - 1]) % m_mod;
            m_base_pow[i] = m_base_pow[i - 1] * m_base % m_mod;
        }
    }
public:
    SingleRollingHash(T& S, int64_t base_ = -1, int64_t mod_ = -1){
        m_base = base_ > 0 ? base_ : DEFAULT_BASE;
        m_mod = mod_ > 0 ? mod_ : DEFAULT_MOD;
        if(SIZE(S) > 0) initialize(S);
    }

    // 0-indexed, [a, b)
    int64_t between(int a, int b){
        return (m_mod + m_hash[b] - m_hash[a] * m_base_pow[b-a] % m_mod) % m_mod;
    }
 
};

using Hashed = vector<int64_t>;

// 複数のローリングハッシュを用いて頑健性向上
template <typename T>
class MultiRollingHash{
private:
    vector<SingleRollingHash<T>> m_rolling_hash_list;
public:
    MultiRollingHash(T& S) {
        m_rolling_hash_list.emplace_back(SingleRollingHash<T>(S, 1007, 1e9+7));
        m_rolling_hash_list.emplace_back(SingleRollingHash<T>(S, 2009, 1e9+9));
    }

    // 0-indexed, [a, b)
    Hashed between(int a, int b){
        Hashed ret;
        for(auto& rh: m_rolling_hash_list) {
            ret.emplace_back(rh.between(a, b));
        }
        return ret;
    }
};


struct Node {
    char ch;
    vector<Node> children;
    vector<int> indexes;
};

int main(void)
{
    cin.sync_with_stdio(false);
    int N;
    cin >> N;
    string S;
    cin >> S;

    MultiRollingHash<string> rh(S);
    int lo = 0;
    int hi = N;
    while (hi - lo > 1) {
        auto mid = (lo + hi) / 2;
        map<Hashed, int> substrs;

        bool ok = false;
        REP(i, N - mid + 1) {
            auto j = i + mid;

            auto hashed = rh.between(i, j);
            if (substrs.count(hashed)) {
                if (i - substrs[hashed] >= mid) {
                    // cout << "ok! mid, i = " << mid << " " << i << endl;
                    ok = true;
                    break;
                }
            } else {
                substrs[hashed] = i;
            }
        }

        if (ok) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << lo << endl;

    return 0;
}
