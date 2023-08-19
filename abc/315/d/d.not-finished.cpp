#include <algorithm>
#include <array>
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
typedef long long ll;
#define REP(i,n) for(ll i = 0; i < (ll)(n); ++i)
#define FOR(i,a,b) for(ll i = (a); i < (ll)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

// 多重vector
// e.g. auto vec = make_v<ll>(2, 3, 4);
template <typename T>
vector<T> make_v(size_t a) { return vector<T>(a); }
template <typename T, typename... Ts>
auto make_v(size_t a, Ts... ts)
{
    return vector<decltype(make_v<T>(ts...))>(a, make_v<T>(ts...));
}

// 多重vectorのfill その1
// 組み込み型の多重vectorに使う
// e.g. fill_v(vec, 777);
template <typename T, typename V>
typename enable_if<is_class<T>::value == 0>::type
fill_v(T &t, const V &v) { t = v; }
template <typename T, typename V>
typename enable_if<is_class<T>::value != 0>::type
fill_v(T &t, const V &v)
{
    for (auto &e : t)
        fill_v(e, v);
}

// 多重vectorのfill その2
// 非組み込み型の多重vectorに使う
// e.g. fill_v2<mint>(vec, 777);
template <typename T, typename U, typename... V>
typename enable_if<is_same<T, U>::value != 0>::type
fill_v2(U &u, const V... v) { u = U(v...); }
template <typename T, typename U, typename... V>
typename enable_if<is_same<T, U>::value == 0>::type
fill_v2(U &u, const V... v)
{
    for (auto &e : u)
        fill_v2<T>(e, v...);
}

template<class T> inline bool chmin(T& a, T b) {
    if (a > b) {
        a = b; return true;
    }
    return false;
}
template<class T> inline bool chmax(T& a, T b) {
    if (a < b) {
        a = b; return true;
    }
    return false;
}
template<int MOD> struct Fp {
    ll val;
    constexpr Fp(ll v = 0) noexcept : val(v % MOD) {
        if (val < 0) val += MOD;
    }
    constexpr int getmod() { return MOD; }
    constexpr Fp operator - () const noexcept {
        return val ? MOD - val : 0;
    }
    constexpr Fp operator + (const Fp& r) const noexcept { return Fp(*this) += r; }
    constexpr Fp operator - (const Fp& r) const noexcept { return Fp(*this) -= r; }
    constexpr Fp operator * (const Fp& r) const noexcept { return Fp(*this) *= r; }
    constexpr Fp operator / (const Fp& r) const noexcept { return Fp(*this) /= r; }
    constexpr Fp& operator += (const Fp& r) noexcept {
        val += r.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    constexpr Fp& operator -= (const Fp& r) noexcept {
        val -= r.val;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr Fp& operator *= (const Fp& r) noexcept {
        val = val * r.val % MOD;
        return *this;
    }
    constexpr Fp& operator /= (const Fp& r) noexcept {
        ll a = r.val, b = MOD, u = 1, v = 0;
        while (b) {
            ll t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        val = val * u % MOD;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr bool operator == (const Fp& r) const noexcept {
        return this->val == r.val;
    }
    constexpr bool operator != (const Fp& r) const noexcept {
        return this->val != r.val;
    }
    friend constexpr ostream& operator << (ostream &os, const Fp<MOD>& x) noexcept {
        return os << x.val;
    }
    friend constexpr Fp<MOD> modpow(const Fp<MOD> &a, ll n) noexcept {
        if (n == 0) return 1;
        auto t = modpow(a, n / 2);
        t = t * t;
        if (n & 1) t = t * a;
        return t;
    }
};
constexpr ll MOD = 1e9 + 7;
using mint = Fp<MOD>;

#define pb push_back
#define mp make_pair
#define mt make_tuple


bool judge_delete(map<char, set<int>>& line) {
    if (SIZE(line) == 1) {
        // その文字を持つのが2箇所以上あるか
        auto ch_num = SIZE(line.begin()->second);
        if (ch_num > 1) {
            return true;
        }
    }
    return false;
}

void erase_if(map<char, set<int>>& obj, char ch, int idx) {
    if (!obj.count(ch)) return;
    if (!obj[ch].count(idx)) return;
    obj[ch].erase(idx);
    if (SIZE(obj[ch]) == 0) obj.erase(ch);
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int H, W;
    cin >> H >> W;
    vector<string> cells(H);
    REP(h, H) cin >> cells[h];

    auto ans = cells;

    vector<multiset<char>> rows(H);
    vector<multiset<char>> columns(W);

    vector<map<char, set<int>>> rows2(H);
    vector<map<char, set<int>>> columns2(W);

    vector<map<char, vector<int>>> row_char2idx(H);
    vector<map<char, vector<int>>> column_char2idx(W);

    REP(h, H) {
        REP(w, W) {
            char ch = cells[h][w];
            rows[h].insert(ch);
            columns[w].insert(ch);

            rows2[h][ch].insert(w);
            columns2[w][ch].insert(h);

            row_char2idx[h][ch].pb(w);
            column_char2idx[w][ch].pb(h);
        }
    }

    // 消すべき行・列を探す
    // 0: row, 1: column
    vector<pair<int, ll>> tobedeleted;
    REP(h, H) {
        if (judge_delete(rows2[h])) tobedeleted.pb({0, h});
    }
    REP(w, W) {
        if (judge_delete(columns2[w])) tobedeleted.pb({1, w});
    }

    while(SIZE(tobedeleted) > 0) {
        vector<pair<int, ll>> next;

        // 確認すべき可能性のある行・列にチェック
        set<int> rows_cand;
        set<int> columns_cand;

        for(auto [r_or_c, idx]: tobedeleted) {
            if (r_or_c == 0) {
                // rows[idx] 行を消す
                cout << "delete rows[" << idx << "]" << endl;
                auto h = idx;
                if (SIZE(rows2[h]) == 0) continue;

                // 残っている文字は一種類のはず
                auto ch = rows2[h].begin()->first;
                cout << "h, ch = " << h << "," << ch << endl;
                for(auto w: rows2[h].begin()->second) {
                    // (h, w) にある文字を消す
                    ans[h][w] = '.';
                    columns_cand.insert(w);
                    rows2[h].clear();
                    erase_if(columns2[w], ch, h);
                }
            } else if (r_or_c == 1) {
                cout << "delete columns[" << idx << "]" << endl;

                auto w = idx;
                if (SIZE(columns2[w]) == 0) continue;

                // 残っている文字は一種類のはず
                auto ch = columns2[w].begin()->first;
                cout << "w, ch = " << w << "," << ch << endl;
                for(auto h: columns2[w].begin()->second) {
                    // (h, w) にある文字を消す
                    ans[h][w] = '.';
                    rows_cand.insert(w);
                    columns2.clear();
                    rows2[h][ch].erase(w);
                    erase_if(rows2[h], ch, w);
                }
            }
        }
        
        



        cout << "-----" << endl;

        tobedeleted = next;
    }
    

    

    return 0;
}
