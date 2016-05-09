#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

typedef struct { int star2; int level; } dataB_t;

class compB{
public:
    bool operator()(const dataB_t& l, const dataB_t& r) const {
        return l.star2 < r.star2;
    }
};

int main(void)
{
    int T;
    cin >> T;

    for(int t = 0; t < T; ++t){
        int N;
        cin >> N;
        vector<int> as(N);
        vector<int> bs(N);
        vector<dataB_t> bSort(N);
        int ret = 0;
        for(int n = 0; n < N; ++n){
            int a, b;
            cin >> a >> b;
            as[n] = a;
            bs[n] = b;
            dataB_t bD;
            bD.star2 = b;
            bD.level = n;
            bSort[n] = bD;
        }

        sort(bSort.begin(), bSort.end(), compB());

        int bIdx = 0;
        int star = 0;
        vector<int> aUsed(N, 0);
        vector<int> bUsed(N, 0);
        bool isFail = false;
        while(bIdx < bSort.size()){
            dataB_t b = bSort[bIdx];
            if (star >= b.star2){
                if (aUsed[ b.level ]){
                    star++;
                }
                else{
                    star += 2;
                    aUsed[ b.level ] = 1;
                }
                bUsed[ b.level ] = 2;
                ++bIdx;
                ++ret;
            }
            else
            {
                int aIdx = -1;
                int maxNum = -1;
                for(int j = 0; j < as.size(); ++j){
                    if (as[j] <= star && !aUsed[j]){
                        if (maxNum < bs[j]){
                            aIdx = j;
                            maxNum = bs[j];
                        }
                    }
                }
                if (aIdx != -1){
                    aUsed[ aIdx ] = 2;
                    ++star;
                    ++ret;
                }
                else{
                    isFail = true;
                    break;
                }
            }
        }

        if (isFail){
            cout << "Case #" << (t+1) << ": " << "Too Bad" << endl;
        }
        else{
            cout << "Case #" << (t+1) << ": " << ret << endl;
        }
    }

    return 0;
}
