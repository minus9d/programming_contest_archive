// ���: H*W�̃^�C�����^������B�^�C�����Y�킩����Ă��邩�̂����ꂩ�B
//       �Y��ȃ^�C���݂̂łł���ő�̒����`�̍ő�l�����߂�
// ��@: http://algorithms.blog55.fc2.com/blog-entry-133.html
//       http://algorithms.blog55.fc2.com/blog-entry-132.html
//       �܂��e�v�f�ɂ��ď�Ɍ������� 1 �����A�����Ă��邩�������e�[�u�� T �����
//       ���ɁAT �̊e�s���q�X�g�O�����̓��͂ƌ��Ȃ��q�X�g�O�����̍ő咷���`�̖ʐς����߂�A���S���Y����K�p

#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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

int largest_square(const int H, const int W, const vector<vector<int>>& cells) {
    // ����Y��ȃ^�C�����A�����鐔
    // �ԕ��Ƃ��āA�E�[�͉��ꂽ�^�C����������̂Ƃ���
    vector<vector<int>> table(H, vector<int>(W+1));
    REP(w, W) {
        REP(h, H) {
            auto val = cells[h][w];
            if (val == 1) table[h][w] = 0;
            else {
                if (h == 0) table[h][w] = 1;
                else table[h][w] = table[h-1][w] + 1;
            }
        }
    }

    // REP(h, H) {
    //     REP(w, W+1) {
    //         cerr << table[h][w] << " ";
    //     }
    //     cerr << endl;
    // }

    int ans = 0;
    // �e�s���ƂɁA�q�X�g�O�����̍ő咷���`�̖ʐς����߂�A���S���Y����K�p
    REP(h, H) {
        // <�q�X�g�O�����̍���, index>
        stack<pair<int, int>> s;
        REP(w, W+1) {
            auto height = table[h][w];
            if (s.empty()) s.push(mp(height, w));
            else if (s.top().first < height) s.push(mp(height, w));
            else if (s.top().first > height) {
                int last_idx = w;
                while(!s.empty() && s.top().first > height) {
                    auto area = (w - s.top().second) * s.top().first;
                    ans = max(area, ans);
                    last_idx = s.top().second;
                    s.pop();
                }
                s.push(mp(height, last_idx));
            }
        }
    }
    return ans;
}


int main() {
    int H, W;
    cin >> H >> W;

    vector<vector<int>> cells(H, vector<int>(W));
    REP(h, H) {
        REP(w, W) {
            cin >> cells[h][w];
        }
    }

    cout << largest_square(H, W, cells) << endl;

    return 0;
}
