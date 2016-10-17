#include <iostream>

using namespace std;

int main(){
    string s;
    cin >> s;
    
    char cur = 'a';
    int ans = 0;
    for (auto ch: s) {
        int n1 = cur - ch;
        if (n1 < 0) n1 += 26;
        int n2 = ch - cur;
        if (n2 < 0) n2 += 26;
        ans += min(n1, n2);
        cur = ch;
    }
    cout << ans << endl;

    return 0;
}
