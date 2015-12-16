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

bool canReachToEdge(vector< vector<int> > &cell, int h, int w, int H, int W){

    bool canReach = true;
    int val = cell[h][w];
    for(int dh = 0; dh < H; ++dh){
        if (val != cell[dh][w]){
            canReach = false;
            break;
        }
    }
    if (canReach) return true;

    canReach = true;
    for(int dw = 0; dw < W; ++dw){
        if (val != cell[h][dw]){
            canReach = false;
            break;
        }
    }
    if (canReach) return true;

    return false;
}

string solve(vector< vector<int> > &cell, int H, int W){
    string ans;
    while(1){
        int mn = 1000;
        int mx = -1;
        for(int h= 0; h < H; ++h){
            for(int w = 0; w < W; ++w){
                mn = min(mn, cell[h][w]);
                mx = max(mx, cell[h][w]);
            }
        }
        // printf("----\n mn, mx = %d, %d\n", mn, mx);
        if (mn == mx){
            return "YES";
        }
        for(int h= 0; h < H; ++h){
            for(int w = 0; w < W; ++w){
                int val = cell[h][w];
                if (val == mn){
                    bool flag = canReachToEdge(cell, h, w, H, W);
                    // printf("  h, w = %d, %d  flag = %d\n", h, w, flag);
                    if (!flag){
                        return "NO";
                    }
                }
            }
        }
        for(int h= 0; h < H; ++h){
            for(int w = 0; w < W; ++w){
                if (cell[h][w] == mn){
                    ++cell[h][w];
                }
            }
        }
    }
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

        cout << "Case #" << (t+1) << ": " << solve(cell, H, W) << endl;
    }

    return 0;
}
