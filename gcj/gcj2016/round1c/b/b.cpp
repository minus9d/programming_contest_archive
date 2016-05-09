// �r��1����r��B�܂ł̃��[�g�����傤��M�ƂȂ�悤�ɃX���C�h�𒣂�

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>
#include <complex>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

void solve(void)
{
    ll B, M;
    cin >> B >> M;

    // x->y�̃X���C�h�͏��x < y�ƂȂ�悤�ɐݒu����Ɩ񑩂���
    // �i�X���C�h���������[�v������Ă͂����Ȃ����߂��̂悤�ɖ񑩂ł���j

    // ���ׂẴr���ԂɃX���C�h��ݒu�����Ƃ����l������max
    // ������傫��M�͎����ł��Ȃ�
    ll B2 = B-2;
    ll poss_mx = 1;
    while (B2) {
        poss_mx *= 2;
        --B2;
    }

    if (M > poss_mx) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    // ����ȊO�ł���Ή������邱�Ƃ��ۏ؂����
    cout << "POSSIBLE" << endl;

    // M <= B - 1�̏ꍇ�͎����ȉ�������
    // �Ⴆ��B = 5, M = 3�̏ꍇ�A
    // 1 -> 5
    // 1 -> 2 -> 5
    // 1 -> 2 -> 3 -> 5
    // ��3�ʂ�̃��[�g������悤�ɉ����o��
    if (M <= B - 1) {
        REP(b, B) {
            string s(B, '0');
            if (M > 0) {
                s[B - 1] = '1';
                --M;
            } 
            if (M > 0) {
                s[b + 1] = '1';
            }
            cout << s << endl;
        }
        return;
    }

    // M > B�̏ꍇ
    // �܂���{�Ƃ���B-1�ʂ�̃��[�g�͕K���m�ۂ�����̂Ƃ���B
    // �Ⴆ��B = 6�̏ꍇ�A�ȉ���5�ʂ�̃��[�g�͕K���m�ۂ���B
    //   1 -> 6
    //   1 -> 2 -> 6
    //   1 -> 2 -> 3 -> 6
    //   1 -> 2 -> 3 -> 4 -> 6
    //   1 -> 2 -> 3 -> 4 -> 5 -> 6
    //
    // ���ɁA�r��5����r��4, 3, ..., �r��1�̏��ɁA�ǉ��Œ���X���C�h��greedy�Ɍ��߂Ă����B
    // �ǉ��Œ���X���C�h�́A�Œ�2��������Ă���K�v������B
    // table[i]�ɂ́A�r��i���N�_�Ƃ��āA�r��6�ɂ��ǂ蒅�����[�g�̐���ۑ����Ă����B
    //
    // �܂��r��5�B�r��5���炳��ɒ����X���C�h�͑��݂��Ȃ��B
    // table[5] = 1�ƂȂ�B(5 -> 6�������݂��Ȃ�)
    //
    // ���Ƀr��4�B���l�ɁA�r��4���炳��ɒ����X���C�h�͑��݂��Ȃ��B
    // table[4] = 2�ƂȂ�B(4 -> 5 -> 6�ɉ�����4 -> 6���V���ɉ����)
    //
    // ���Ƀr��3�B�r��3���璣���\���̂���X���C�h�́A�r��5�ւ̃X���C�h�B
    // ����3 -> 5�ƃX���C�h�𒣂����ꍇ�Atable[3] = 1 + table[4] + table[5]�ƂȂ�
    // ����ɁA�r��1����r��6�܂ł��ǂ蒅�����[�g�̍ŏ����́Atable[3] + (3 - 1)�ƂȂ�B
    // ���̍ŏ������AM�𒴂��Ȃ���΁A���̃X���C�h�𒣂�B
    // M�𒴂���Ȃ�΁A�X���C�h�𒣂�Ȃ��B
    // �X���C�h�𒣂�Ȃ��ꍇ�Atable[3] = 1 + table[4]�ƂȂ�
    //
    // ���̃r��2���A�r��4, �r��5�ɃX���C�h�𒣂邩�ǂ�����greedy�Ɍ��߂�B�ȉ��J��Ԃ��B

    ll curr = 0;
    vector<ll> table(B + 1);
    vector<vector<int>> slides(B + 1, vector<int>(B + 1));

    // ��{�Œ���X���C�h
    FOR(b, 1, B) {
        slides[b][b + 1] = 1;
        slides[b][B] = 1;
    }

    B2 = B - 1;
    while (B2 >= 1) {
        ++curr;
        FOR(i, B2 + 2, B) {
            // �����r��B2����r��i�܂ŃX���C�h�𒣂����ꍇ�ɁA�r��1����r��B�܂ł��ǂ蒅�����[�g�̍ŏ�����curr2�Ɍv�Z
            ll curr2 = curr + table[i];
            curr2 += (B2 - 1);

            // ����curr2��M�𒴂��Ȃ��ꍇ�́A�r��B2����r��i�܂ŃX���C�h�𒣂邱�Ƃɂ���
            if (curr2 <= M) {
                slides[B2][i] = 1;
                curr += table[i];
            }
        }
        table[B2] = curr;
        --B2;
    }

    FOR(b1, 1, B + 1) {
        FOR(b2, 1, B + 1) {
            cout << slides[b1][b2];
        }
        cout << endl;
    }
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        cout << "Case #" << (test+1) << ": ";
        solve();
    }

    return 0;
}
