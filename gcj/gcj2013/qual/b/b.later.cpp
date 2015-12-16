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

void printCell(vector< vector<int> > &cell, int H, int W){
    cout << "-----" << endl;
    for(int h= 0; h < H; ++h){
        for(int w = 0; w < W; ++w){
            printf("%03d ", cell[h][w]);
        }
        cout << endl;
    }
    cout << "-----" << endl;
}


int main(void)
{
    int T;
    cin >> T;
    
    for(int t = 0; t < T; ++t){
        int H, W;
        cin >> H >> W;
        
        vector< vector<int> > cell(H, vector<int>(W));
        for(int h= 0; h < H; ++h){
            for(int w = 0; w < W; ++w){
                cin >> cell[h][w];
            }
        }
        //printCell(cell, H, W);

        vector< vector<int> > cell2(H, vector<int>(W));
        for(int h= 0; h < H; ++h){
            for(int w = 0; w < W; ++w){
                cell2[h][w] = 100;
            }
        }

        for(int h = 0; h < H; ++h){
            int highest = -1;
            for(int w = 0; w < W; ++w){
                highest = max(highest, cell[h][w]);
            }
            for(int w = 0; w < W; ++w){
                cell2[h][w] = min(highest, cell2[h][w]);
            }
        }

        for(int w = 0; w < W; ++w){
            int highest = -1;
            for(int h = 0; h < H; ++h){
                highest = max(highest, cell[h][w]);
            }
            for(int h = 0; h < H; ++h){
                cell2[h][w] = min(highest, cell2[h][w]);
            }
        }
        //printCell(cell2, H, W);

        string ans = "YES";
        for(int h= 0; h < H; ++h){
            for(int w = 0; w < W; ++w){
                if (cell[h][w] != cell2[h][w]){
                    ans = "NO";
                    break;
                }
            }
        }

        cout << "Case #" << (t+1) << ": " << ans << endl;
    }

    return 0;
}
