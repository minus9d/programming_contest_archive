#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
template<class T> inline bool chmin(T& a, T b) {
    if (a > b) {
        a = b; return true;
    }
    return false;
}

int replace(int N, char S[]) {
    // bit "1101" を, "IJ?C" とみなす
    int ans = 1e9;
    char ijpc[] = "IJPC";
    REP(mask, 1 << 4) {
        int idx = 0;
        bool succ = false;
        int bitcount = 0;
        REP(i, N) {
            char ch = (mask & (1 << idx)) ? ijpc[idx] : '?';
            bitcount += (ch == S[i]);
            if (ch == '?') {
                ++idx;
            }
            else {
                if (ch == S[i]) {
                    ++idx;
                }
            }
            if (idx == 4) {
                succ = true;
                break;
            }
        }
        if (succ) chmin(ans, 4 - bitcount);
    }
    return ans;
}

// using namespace std;
// #include <iostream>
// int main() {
//   cout << replace(4, "IJPC") << endl;
//   cout << replace(8, "IAMJAPLJ") << endl;
//   cout << replace(28, "IOIERJAPANPROGRAMMINGCONTEST") << endl;
// }