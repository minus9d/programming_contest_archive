#include <stdio.h>


const int MAX = 3000;
long long mem[MAX][MAX];
bool visit[MAX][MAX];

int rabbit(int x, int y) {
  if (visit[x][y]) return mem[x][y];
  
    if (x <= 0) {
        return 1;
    } else if (y <= 0) {
        return 2;
    } else {
      int ret = (rabbit(x + 1, y - 2) + rabbit(x - 1, y - 1) + rabbit(x - 3, y + 2)) % 20121224;
      mem[x][y] = ret;
      visit[x][y] = true;
      return ret;
    }
}

int main(void) {
    int xs[10] = { 314, 159, 265, 358, 979, 323, 846, 264, 338, 327, };
    int ys[10] = { 288, 419, 716, 939, 937, 510, 582,  97, 494, 459, };
    int i;
    for (i = 0; i < 10; ++i) {
        printf("%d\n", rabbit(xs[i], ys[i]));
    }
    return 0;
}
