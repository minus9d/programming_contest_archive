// 解説PDFそのまま
//
// 2つの文字列について、その相対位置ごとに矛盾があるかないかを判定する
// 配列を用意するのがとても賢い

#include <iostream>
#include <string>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define M 2000

bool ab[100000],ac[100000],bc[100000];

bool match(char c1, char c2){
    return (c1 == '?' || c2 == '?' || c1 == c2);
}

int main(void){
    int i,j;

    string a,b,c;
    cin >> a >> b >> c;

    int A = a.length();
    int B = b.length();
    int C = c.length();

    constexpr int offset = 50000;

    // ab[i]: 文字列aに対して文字列bをi個分右に配置したときに
    //        矛盾が生じるなら1となる配列
    //        ただし、iが負の数になってもよいようoffset分下駄を履かせる
    REP(i,A) REP(j,B) if(!match(a[i], b[j])) ab[i-j+offset] = true;
    REP(i,A) REP(j,C) if(!match(a[i], c[j])) ac[i-j+offset] = true;
    REP(i,B) REP(j,C) if(!match(b[i], c[j])) bc[i-j+offset] = true;

    int ans = 3 * M;
    // 文字列aを基準として、bをi個右にずらす
    for(i=-2*M; i<=2*M; i++) { 
        // 文字列aを基準として、cをj個右にずらす
        for(j=-2*M; j<=2*M; j++) {
            // 矛盾がないなら配置できる
            if(!ab[i+offset] && !ac[j+offset] && !bc[j-i+offset]) {
                // 文字列a, b, cどれかの左端・右端をそれぞれ計算
                int L = min(0, min(i, j));
                int R = max(A, max(B + i, C + j));
                ans = min(ans, R - L);
            }
        }
    }

    cout << ans << endl;

    return 0;
}

