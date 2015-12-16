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


bool isPalin(ll n){
    string str;
    while(n){
        int t = n % 10;
        str += ('0' + t);
        n /= 10;
    }
    string rev = str;
    reverse(rev.begin(), rev.end());
    return (str == rev) ? true : false;
}

int main(void)
{
    int T;
    cin >> T;

    vector<ll> mem;
    for(ll i = 0; i < 1e8; ++i){
        ll n = i * i;
        if (n > 1e14+3) break;
        if (isPalin(i) && isPalin(n)){
            mem.push_back(n);
            cout << i << ": " << n << ": ";
            cout << "palin";
            cout << endl;
        }
    }

    return 0;
    
    for(int t = 0; t < T; ++t){
        ll A, B;
        cin >> A >> B;

        int ret = 0;
        for(int m = 0; m < mem.size(); ++m){
            //printf("A, mem[m], B = %
            if (A <= mem[m] && mem[m] <= B){
                ++ret;
            }
        }

        cout << "Case #" << (t+1) << ": " << ret << endl;
    }

    return 0;
}
