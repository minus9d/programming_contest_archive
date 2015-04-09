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

ll get_paint(long long x, long long r){
    return 2 * x * x + x * (2 * r - 1);
}

int main(void)
{
    int T;
    cin >> T;

    for(int t_ = 0; t_ < T; ++t_){

        ll r, t;
        cin >> r >> t;

        ll lo = 1;
        ll hi = sqrt(t);
        ll ans;
        while(1) {
            printf("lo, hi = %lld, %lld\n", lo, hi);
            ll x = (lo + hi) / 2;
            ll paint1 = get_paint(x, r);
            ll paint2 = get_paint(x+1, r);
            printf("x, paint1, paint2, t = %lld, %lld, %lld, %lld\n", x, paint1, paint2, t);
            if (paint1 <= t && paint2 > t){
                ans = x;
                break;
            }

            if (paint1 > t){
                hi = x;
                continue;
            }
            if (paint2 <= t){
                lo = x;
                continue;
            }
        }

        cout << "Case #" << (t_+1) << ": " << ans << endl;
    }

    return 0;
}
