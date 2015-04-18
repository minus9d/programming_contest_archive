#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

int pow2Int(int n){
    return n * n;
}

int main(void)
{
    int N;
    cin >> N;
    for(int n = 0; n < N; ++n){
        vector<int> nums(3);
        for(int i = 0; i < 3; ++i){
            cin >> nums[i];
        }
        sort(nums.begin(), nums.end());
        cout << ((pow2Int(nums[0]) + pow2Int(nums[1]) == pow2Int(nums[2])) ? "YES" : "NO") << endl;
    }
    
    return 0;
}
