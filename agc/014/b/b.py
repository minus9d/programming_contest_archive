#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
N,M = map(int, input().split())

counter = np.zeros(N+1)
for m in range(M):
    a, b = map(int, input().split())
    counter[a] += 1
    counter[b] -= 1

cnt = 0
succ = True
for n in range(N+1):
    cnt += counter[n]
    if cnt % 2:
        succ = False
        break
if succ:
    print("YES")
else:
    print("NO")
