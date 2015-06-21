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

int main(void)
{
    string str;
    while(getline(cin, str)){
        istringstream sin(str);
        long long a, b;
        sin >> a >> b;
        a += b;
        int digit = 0;
        while(a){
            ++digit;
            a /= 10;
        }
        cout << digit << endl;
    }
    
    return 0;
}
