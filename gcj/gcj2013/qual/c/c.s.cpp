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

    vector<int> mem(1001,0);
    for(ll i = 0; i < 100000000; ++i){
        ll n = i * i;
        if (n > 1000) break;
        if (isPalin(i) && isPalin(n)){
            mem[n] = 1;
//            cout << i << ": " << n << ": ";
//            cout << "palin";
//            cout << endl;
        }
    }
    
    for(int t = 0; t < T; ++t){
        int A, B;
        cin >> A >> B;

        int ret = 0;
        for(int i = A; i <= B; ++i){
            ret += mem[i];
        }

        cout << "Case #" << (t+1) << ": " << ret << endl;
    }

    return 0;
}
