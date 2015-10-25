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

vector<ll> startLoc;
vector<ll> endLoc;

set<pair<ll, char>> manage;
vector<pair<ll, char>> manage2;

#define START -2
#define END +2


// [s,e] must be white
void addRange(ll s, ll e) {
    if (manage.count(mp(s-1,END))) {
        manage.erase(mp(s-1,END));
    }
    else {
		manage.insert(mp(s, START));
    }

    if (manage.count(mp(e+1,START))) {
        manage.erase(mp(e+1,START));
    }
    else {
		manage.insert(mp(e, END));
    }
	manage2 = vector<pair<ll, char>>(ALL(manage));
}

int findNearStartIdx(ll loc) {
	auto it = lower_bound(ALL(manage2), mp(loc, START), [](pair<ll, char> lhs, pair<ll, char> rhs) -> bool { return lhs.first < rhs.first; });
	int idx = it - manage2.begin();
	idx = max(0, idx - 2);
	if (idx % 2) ++idx;
	return idx;
}

// bool isBlack(ll loc) {
//     ll len = SIZE(startLoc);
//     REP(i,len) {
//         if (startLoc[i] <= loc && loc <= endLoc[i]) return true;
//     }
//     return false;
// }

ll findNextWhite(ll loc){
    ll nextWhiteLoc = loc;
    ll start = 0;

	int idx = findNearStartIdx(loc);

	ll len = SIZE(manage2);
	FOR(i, idx, len) {
		auto& e = manage2[i];
        if (e.second == START) {
            start = e.first;
        }
        else {
            ll end = e.first;
            if (start <= loc && loc <= end) {
                nextWhiteLoc = end + 1;
				break;
            }
			else if (start > loc) {
				break;
			}
        }
    }
    return nextWhiteLoc;
}

// -1 or idx
// loc must be white
ll findNextBlack(ll loc){
	int idx = findNearStartIdx(loc);

	ll len = SIZE(manage2);

	FOR(i, idx, len) {
		auto& e = manage2[i];
        if (e.second == START) {
			ll start = e.first;
            if (start > loc) return start;

        }
    }
    
    return -1;
}

bool isWhite(ll loc) {
    ll start = 0;
	int idx = findNearStartIdx(loc);

	ll len = SIZE(manage2);

	FOR(i, idx, len) {
		auto& e = manage2[i];
        if (e.second == START) {
            start = e.first;
        }
        else {
            ll end = e.first;
            if (start <= loc && loc <= end) {
                return false;
            }
			else {
				if (start > loc) break;
			}
        }
    }
    return true;
}

int main(void)
{
    int N;
    cin >> N;
    vector<ll> ans;
    REP(n,N) {
        ll s,c;
        cin >> s >> c;

        if (n==0) {
            auto e = s + c - 1;
            ans.pb(e);
            // starts.pb(s);
            // ends.pb(e);
            addRange(s,e);
        }
        else {
            ll loc = s;
            while (c > 0) {
                // もし白マスなら、次の黒マスまで塗る
                if (isWhite(loc)) {
                    ll nextBlack = findNextBlack(loc);
                    ll canFill = (nextBlack == -1) ? 1e15 : nextBlack - loc;
                    ll fill = min(canFill, c);
                    addRange(loc, loc + fill - 1);
                    c -= fill;
                    loc += fill - 1;
                }
                else {
                    ll nextWhite = findNextWhite(loc);
                    loc = nextWhite;
                }
            }
            ans.pb(loc);
        }
    }

    for(auto a : ans) cout << a << endl;

    return 0;
}
