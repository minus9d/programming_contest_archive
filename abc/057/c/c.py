#!/usr/bin/env python3

import math

N = int(input())
ans = 1e10
for i in range(1, int(math.sqrt(N)) + 1):
    j = N // i
    if N == i * j:
        ans = min(ans, max(len(str(i)), len(str(N // i))))
print(ans)
