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
import sys

def rev(x):
    return int(''.join(reversed(str(x))))

def min_cycle(x, y):
    x2, y2 = min(x, y), max(x, y)
    
    x3, y3 = x2, y2
    x3 = rev(x3)

    if x3 < y3: y3 -= x3
    else: x3 -= y3

    x4, y4 = min(x3, y3), max(x3, y3)

    return (x2, y2) == (x4, y4)


def simulate(x, y):
    orig_x = x
    orig_y = y
    cnt = 0
    for _ in range(500):
        if x * y == 0:
            break
        if x < y: x = rev(x)
        else: y = rev(y)
        if x < y: y = y - x
        else: x = x - y
        cnt += 1
    
    print("x, y, cnt, min_cycle: ", orig_x, orig_y, cnt, min_cycle(orig_x, orig_y))


cache = [[None for _ in range(1001)] for _ in range(1001)]

# for x in range(1, 1000):
#     for y in range(x, 1000):
#         if min_cycle(x, y):
#             cache[x][y] = True
#             print(x, y, " is min_cycle")

def check(n, m):
    n, m = min(n, m), max(n, m)
    if cache[n][m] is not None:
        return cache[n][m]

    history = set()
    res = None
    cnt = 0
    while True:
        if (n, m) in history:
            res = True
            break

        history.add((n, m))
        cnt += 1

        if n * m == 0:
            res = False
            break
        n = rev(n)
        n, m = min(n, m), max(n, m)
        m -= n
        n, m = min(n, m), max(n, m)

        if cache[n][m] is not None:
            res = cache[n][m]
            break
    for h in history:
        cache[h[0]][h[1]] = res

    return res


N, M = map(int, input().split())
ans = 0
for n in range(1, N+1):
    for m in range(1, M+1):
        ans += check(n, m)
print(ans)

