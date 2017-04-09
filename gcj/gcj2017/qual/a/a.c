#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void flip(char *S, int idx, int K) {
    for(int j = idx; j < idx + K; ++j) {
        S[j] = (S[j] == '+') ? '-' : '+';
    }
    return;
}

const int MAX = 1010;
void solve() {
    char S[MAX];
    int K;
    scanf("%s %d", S, &K);
    int len = strlen(S);

    int ans = 0;
    for(int i = 0; i < len - K + 1; ++i) {
        if (S[i] == '-') {
            ans += 1;
            flip(S, i, K);
        }
    }

    if (strchr(S, '-') != 0) {
        printf("IMPOSSIBLE\n");
    } else {
        printf("%d\n", ans);
    }
}
        
int main() {
    int T;
    scanf("%d", &T);
    int t = 0;
    for(t = 0; t < T; ++t) {
        printf("Case #%d: ", t + 1);
        solve();
    }
    return 0;
}
