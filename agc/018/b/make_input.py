#!/usr/bin/env python3

import random

N = 300
M = 300
print(N, M)
for n in range(N):
    nums = list(range(1, M + 1))
    random.shuffle(nums)
    print(*nums)
