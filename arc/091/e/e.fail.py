#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
import heapq 
from itertools import *
import math
import random
import re
import string

 
N, A, B = map(int, input().split())
arr = list(range(1, N+1))
if A + B == N + 1:
    ans = arr[:A-1] + list(reversed(arr[A-1:]))
    print(*ans)
elif A + B > N + 1:
    print(-1)
else:
    ans2 = list(reversed(arr[-B:]))

    # [1 .. N - B] を使って 条件A-1, Bを満たす
    remain_num = N - B
    block_num = (remain_num + B - 1) // B
    if A > block_num + 1:
        print(-1)
    else:
        # remain_num を A-1個のブロックに分ける
        base = remain_num // (A - 1)
        extra = remain_num - base * (A - 1)
        ans = []
        for _ in range(A-1):
            if extra:
                len = base + 1
                extra -= 1
            else:
                len = base

            ans += list(reversed(arr[:len]))
            arr = arr[len:]
        ans += ans2
        print(*ans)

# sys.exit(0)



# for N in range(1, 10):
#     print("=={}==".format(N))
#     items = list(range(1, N+1))
#     seen = {}
#     for balls in permutations(items, N):
#         n1 = lis(balls)
#         n2 = lis(list(reversed(balls)))
#         if (n1,n2) not in seen:
#             seen[(n1,n2)] = balls
#     for k in sorted(seen):
#         if sum(k) == N + 1:
#             print(" ", k, seen[k])
#         else:
#             print("*", k, seen[k])


