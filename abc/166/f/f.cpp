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
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())
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

vector<int> find_dup(pair<int, int> q1,
                        pair<int, int> q2) {
    map<int, int> counter;
    counter[q1.first]++;
    counter[q1.second]++;
    counter[q2.first]++;
    counter[q2.second]++;
    int dup = -1;
    for(auto kv: counter) {
        if (kv.second == 2) {
            dup = kv.first;
        }
    }

    if (q1.first == dup) {
        return vector<int>{dup, q1.second};
    } else if (q1.second == dup) {
        return vector<int>{dup, q1.first};
    }
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, A, B, C;
    cin >> N >> A >> B >> C;
    vector<ll> arr{A, B, C};

    vector<pair<int, int>> Qs(N);
    REP(n, N) {
        string q; cin >> q;
        if (q == "AB") Qs[n] = {0, 1};
        else if (q == "AC") Qs[n] = {0, 2};
        else if (q == "BC") Qs[n] = {1, 2};
    }

    // // 今の命令と同じ命令が、自分含めて何個続くか
    // vector<int> seq(N);
    // // 今の命令が続いたあと、最初に来る違う命令はなにか
    // vector<pair<int, int>> next_order(N);
    // for(int n = N - 1; n >= 0; --n) {
        
    // }

    vector<int> ans;
    bool fail = false;
    REP(n, N) {
        auto s = Qs[n];
        auto idx1 = s.first;
        auto idx2 = s.second;

        if (arr[idx1] == 0 && arr[idx2] == 0) {
            fail = true;
            break;
        }

        // if (arr[idx1] == 0 && arr[idx2] != 0) {
        //     ans.pb(idx1);
        //     arr[idx1]++;
        //     arr[idx2]--;
        // }
        // else if (arr[idx1] != 0 && arr[idx2] == 0) {
        //     ans.pb(idx2);
        //     arr[idx2]++;
        //     arr[idx1]--;
        // }

        // 2択
        if (arr[idx1] == 1 && arr[idx2] == 1) {
            // 同じ命令が何回続くか？
            int seq = 1;
            // その先にある命令
            pair<int, int> next_q;

            int m = n + 1;
            for(; m < N; ++m) {
                if (Qs[n] == Qs[m]) ++seq;
                else break;
            }
            if (m != N) {
                next_q = Qs[m];
            } else {
                next_q = mp(-1, -1);
            }

            // 偶数回の場合はきにしなくてよい
            if (seq % 2 == 0) {
                cerr << "even" << endl;
                REP(i, seq / 2) {
                    ans.pb(idx1);
                    ans.pb(idx2);
                }
                n = m - 1;
            }
            // 最後の場合もきにしなくてよい
            else if (next_q == mp(-1, -1)) {
                cerr << "dont care" << endl;
                vector<int> tmp{idx1, idx2};
                REP(i, seq) {
                    ans.pb(tmp[i % 2]);
                }
                break;
            }
            else {
                auto order = find_dup(Qs[n], Qs[m]);
                REP(i, seq) {
                    ans.pb(order[i % 2]);
                }
                arr[order[0]]++;
                arr[order[1]]--;
                n = m - 1;
            // ...

            }
        }
        else {
            // 多い方から移す
            if (arr[idx1] < arr[idx2]) {
                ans.pb(idx1);
                arr[idx1]++;
                arr[idx2]--;
            }
            else {
                ans.pb(idx2);
                arr[idx2]++;
                arr[idx1]--;
            }
        }
    }

    if (fail) {
        cout << "No" << endl;
    }
    else {
        cout << "Yes" << endl;
        for (auto a: ans) {
            if (a == 0) cout << "A" << endl;
            if (a == 1) cout << "B" << endl;
            if (a == 2) cout << "C" << endl;
        }
    }


    return 0;
}
