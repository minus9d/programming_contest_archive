// ���pdf�̕��j�ɉ�������
// �Q�l�F http://agc005.contest.atcoder.jp/submissions/904878

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>
#include <climits>
using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

const int N = 1234567;

int pr[N]; // �����i�Ԗڂ̐��l���獶�ɒH��A�ŏ��ɂ�菬�������l������index
int ne[N]; // �����i�Ԗڂ̐��l����E�ɒH��A�ŏ��ɂ�菬�������l������index
int pos[N];  // ���lx�����鐔���index��ێ�

int main() {
    int N;
    cin >> N;
    FOR(i, 1, N + 1) {
        int a;
        cin >> a;
        pos[a] = i;
    }
    REP(i, N+2) {
        pr[i] = i - 1;
        ne[i] = i + 1;
    }

    long long ans = 0;
    for (int i = N; i >= 1; i--) {
        // j: ���li�����鐔���index
        int j = pos[i];
        // ���li * ���li���ŏ��l�ƂȂ�悤�ȕ����z��̐�
        ans += i * 1LL * (j - pr[j]) * (ne[j] - j);

        // �Ⴆ�Έȉ��̐���ŁA�� ���li = 4, j = 5�Ƃ���B
        //  ���� .. 3 7 8 4 9 2
        //   idx    2 3 4 5 6 7
        //  ���̂Ƃ��Apr[5] = 2, ne[5] = 7�B
        // ���l4���������I�������́A���l4�ɂƂ��Ă�ne, pr���g���ăe�[�u�����X�V�B
        // ���̏ꍇ�A���l3�ɂƂ��Ă�ne�́A���l4�ɂƂ��Ă�ne�Ɠ������Ȃ�B
        // �܂��A    ���l2�ɂƂ��Ă�pr�́A���l4�ɂƂ��Ă�ne�Ɠ������Ȃ�B
        // ���ŏ����� ne[2] = ne[7], pr[7] = pr[7]�ƂȂ�B

        pr[ne[j]] = pr[j];
        ne[pr[j]] = ne[j];
    }
    cout << ans << endl;
    return 0;
}

