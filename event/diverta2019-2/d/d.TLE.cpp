// 本番中に書いてTLEになったコード
//
// A->B, B->Aを別々に考える。
//
// (1)A->Bに行くとき、
//    Aにて金に何グラム変えるか、銀に何グラム変えるかを全探索して、
//    Bでのドングリの数を最大化。
//
// (2)B->Aも同様。
//
// (1)は計算できるが、(1)の結果どんぐりの数が最大5000*5000になったことが
// 影響して、落ちたように思う

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




tuple<ll, ll, ll> solve(ll Ga, ll Sa, ll Ba,
                        ll Gb, ll Sb, ll Bb,
                        ll N) { 
    ll best = 0;
    tuple<ll, ll, ll> ret;

    ll l_max = (N / Ga) + 1;
    ll m_max = (N / Sa) + 1;
    if (Ga >= Gb) l_max = 1;
    if (Sa >= Sb) m_max = 1;

    REP(l, l_max) {
        ll remain = N - Ga * l;
        if (remain < 0) break;
        ll score = l * Gb;

        REP(m, m_max) {
            ll remain2 = remain - Sa * m;
            if (remain2 < 0) break;
            ll score2 = score + m * Sb;

            ll n = 0;
            if (Bb > Ba) {
                n = remain2 / Ba;
                auto remain3 = remain2 - (n * Ba);
                score2 += n * Bb + remain3;
            } else {
                n = 0;
                score2 += remain2;
            }
            
            if (score2 > best) {
                best = score2;
                ret = mt(l, m, n);
            }
        }
    }
    return ret;
}

int main(void)
{
    cin.sync_with_stdio(false);
    ll N;
    cin >> N;
    ll Ga, Sa, Ba;
    ll Gb, Sb, Bb;
    cin >> Ga >> Sa >> Ba;
    cin >> Gb >> Sb >> Bb;

    ll l, m, n;
    tie(l, m, n) = solve(Ga, Sa, Ba, Gb, Sb, Bb, N);
    cerr << l << "," << m << "," << n << endl;

    ll remain = N - (Ga * l + Sa * m + Ba * n);

    ll N2 = remain + (Gb * l + Sb * m + Bb * n);

    tie(l, m, n) = solve(Gb, Sb, Bb, Ga, Sa, Ba, N2);
    cerr << l << "," << m << "," << n << endl;

    ll remain2 = N2 - (Gb * l + Sb * m + Bb * n);
    ll N3 = remain2 + (Ga * l + Sa * m + Ba * n);
    cout << N3 << endl;

    return 0;
}
