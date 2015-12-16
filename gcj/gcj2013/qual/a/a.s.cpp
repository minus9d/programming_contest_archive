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

const int SIZE = 4;


char readNext(int i, int j, char ch, vector<string> &cell){
    if (i < 0 || i >= SIZE || j < 0 || j >= SIZE){
            return 'z'; // fail
    }
    if (ch == cell[j][i] || cell[j][i] == 'T'){
        return ch;
    }
    else{
        return 'z';
    }
}

string getAns(vector<string> &cell){
    string ret;

    bool isFull = true;
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            if (cell[j][i] == '.') isFull = false;
        }
    }
        
    int di[] = {0, 1, 1, -1};
    int dj[] = {1, 0, 1, 1};
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            for(int d = 0; d < 4; ++d){
                char ch = cell[j][i];
                // printf("i, j, d = %d, %d, %d\n", i, j, d);
                for(int rep = 0; rep < SIZE; ++rep){
                    ch = readNext(i+di[d]*rep, j+dj[d]*rep, ch, cell);
                    // printf("  ch = %c\n", ch);
                }
                if (ch == 'X'){
                    return "X won";
                }
                else if (ch == 'O'){
                    return "O won";
                }
            }
        }
    }

    return isFull ? "Draw" : "Game has not completed";
}

int main(void)
{
    int T;
    cin >> T;

    
    for(int t = 0; t < T; ++t){
        vector<string> cell;
        for(int i = 0; i < SIZE; ++i){
            string str;
            cin >> str;
            cell.push_back(str);
        }
            
        cout << "Case #" << (t+1) << ": " << getAns(cell) << endl;
    }

    return 0;
}
