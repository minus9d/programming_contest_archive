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

def to_int(X, base):
    ret = 0
    tmp = 1
    for ch in X[::-1]:
        ret += tmp * int(ch)
        tmp *= base
    return ret

def solve(X, M):
    # corner!
    # 何進数でもXになる
    if int(X) < 10:
        if int(X) <= M:
            return 1
        else:
            return 0

    d = int(max(X))

    if to_int(X, d + 1) > M:
        return 0

    lo = d + 1
    hi = M * 2
    while hi - lo > 1:
        mid = (lo + hi) // 2
        if to_int(X, mid) <= M:
            lo = mid
        else:
            hi = mid

    return lo - (d + 1) + 1

def slow(X, M):
    if int(X) < 10:
        if int(X) <= M:
            return 1
        else:
            return 0

    d = int(max(X))

    ans = 0
    n = d + 1
    while True:
        val = to_int(X, n)
        # print("X, n, val:", X, n, val)
        if val <= M:
            ans += 1
        else:
            break
        n += 1
    return ans

# for X in range(1, 1000):
#     print("X:", X)
#     for M in range(1, 1000):
#         # print("M:", M)
#         X = str(X)
#         mine = solve(X, M)
#         gt = slow(X, M)
#         if mine != gt:
#             print(X, M)
#             print(mine, gt)


X = input()
M = int(input())
print(solve(X, M))

            
