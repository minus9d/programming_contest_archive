#include <stdio.h>
#include <limits.h>

int main(void) {
    int i, j;
    int answer = 0;
    for (i = 1; i <= 20121224; ++i) {
      answer += i;
    }
    printf("%d\n", answer);
    return 0;
}
